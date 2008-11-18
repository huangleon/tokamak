#pragma once
//////////////////////////////////////////////////////////////////
//文件： MilkShape3DMesh.h
//描述： MilkShape3D的读取，并且经过扩展，支持多个动作
//		与原版MilkShape3D的改进在于：
//		1.支持预计算包围盒，省掉Framemove里的开销
//		2.旋转信息由四元数来代替，替换原来只是使用四元数来插值的方法
//		3.支持可以根据需要，关掉法线的变换。在不需要光照的地方省掉法线的变换来提高效率。
//		4.将原来友骨架促使顶点变化转化为顶点变化，增加cpu的cache命中率,并且便于将动作文件进行分离
//		5. 支持动作切换时的平滑过渡功能
//		6.在进行纹理读取时禁掉三线性过滤，关掉mipmap,能节省一部分内存
//		7.为了便于加速读取，可以存储为新格式
//历史：
//		赵磊				创建
//		
////////////////////////////////////////////////////////////////
#include "IAnimatedMeshMS3D.h"
#include "IReadFile.h"
#include "IFileSystem.h"
#include "irrArray.h"
#include "irrString.h"
#include "irrMap.h"
#include "SMesh.h"
#include "SMeshBuffer.h"
#include "quaternion.h"
#include "IrrlichtDevice.h"
namespace irr
{
namespace scene
{
namespace sklani
{
	class CResMngr;
	class CRes : public IUnknown
	{
		friend class CResMngr;
	public:
		CRes();
		virtual ~CRes();
	public:
		bool operator < (const CRes& other) const
		{
			return m_strName < other.m_strName;
		}
		void SetResName(const core::stringc &strName)
		{
			m_strName = strName;
		}
		const core::stringc &GetResName()
		{
			return m_strName;
		}
	protected:
		core::stringc m_strName;
		CResMngr *m_pResMngr;
	};
	class CResMngr
	{
	public:
		bool RegisterRes(const core::stringc &strName,CRes *pRes);
		void RemoveRes(const core::stringc &strName);
		CRes *QueryRes(const core::stringc &strName);
		void Clear();
	protected:
		typedef core::map<core::stringc,CRes *> MAP_NAME2RES;
		 MAP_NAME2RES m_mapRes;
	};

	class CAction_ : public IUnknown
	{
		friend class CSkeletonAni;
	public:
		CAction_();
		virtual ~CAction_();

	public:
		void SetSize(s32 iJointNum,s32 iFrameNum);
		int GetFrameNum()
		{
			return m_iFrameNum;
		}
	
	public:
		//半开区间
		struct SSubActionInfo
		{
			int m_iFrameStart;
			int m_iFrameEnd;
		
		};
		bool AddAction(CAction_ *pAction,SSubActionInfo &info);
		bool AddAction(const core::stringc &strActionName,SSubActionInfo &info,IrrlichtDevice *Device);
		bool SplitToSubAction(core::array<SSubActionInfo> &arrayInfo,core::array<CAction_ *> &arrayRet);
		bool ImportActionFromFile(io::IReadFile *pFile);
		bool ImportActionFromFile(const core::stringc &strName,irr::IrrlichtDevice *Device);
		bool Export(io::IWriteFile *pWriteFile);
		bool Import(io::IReadFile *pReadFile);
	public:
		struct SKeyframe
		{
			core::vector3df m_vTrans;
			core::quaternion m_qRotate;
		};

		const SKeyframe &GetJointKeyframe(s32 iJointIndex,s32 iFrameNum) const
		{
			return *(m_pKeyframe + m_iJointNum * iFrameNum +  iJointIndex); 
		}
		SKeyframe &GetJointKeyframe(s32 iJointIndex,s32 iFrameNum) 
		{
			return *(m_pKeyframe + m_iJointNum * iFrameNum +  iJointIndex); 
		}		
		SKeyframe *GetKeyframe(s32 iFrameNum) const
		{
			return m_pKeyframe + m_iJointNum * iFrameNum;
		}
		bool GetKeyframeIndex(f32 fTime,s32 &iFrameIndex0,s32 &iFrameIndex1,f32 &fScale,bool bLoop) const;
		
	private:
		f32 *m_pKeyframeTime;
		SKeyframe *m_pKeyframe;
		s32 m_iJointNum;
		s32 m_iFrameNum;
		f32 m_fFramePerSecond;
	};

	class CActionMngr : public CResMngr
	{
	public:
		static CActionMngr *GetInstance();
	};
	inline CActionMngr *ActionMngr()
	{
		return CActionMngr::GetInstance();
	}
	struct SJoint
	{			
		s32 iFrameIndex;
		core::quaternion Rotation; //改为旋转四元数
		core::vector3df Translation;				
		core::matrix4 AbsoluteTransformationAnimated; //最终旋转矩阵
		core::matrix4 RelativeTransformation;
		s32 Parent; //父节点			

	};
	class CSkeletonAni;
	struct SJointInfo
	{
		core::stringc strName;
		core::matrix4 RelativeTransformation;
		core::matrix4 AbsoluteTransformation;
		u16 wParentIndex;
		core::vector3df Trans;
		core::quaternion Rotate;
	};
	class CSkeleton : public CRes
	{
		friend class CSkeletonAni;
	public:
		CSkeleton();
		~CSkeleton();
		void operator = (const CSkeleton &skl);
	public:
		//根据一个节点名字得到骨骼节点
		int GetJointIndex(const core::stringc &NameFind) const;

		const SJointInfo &GetJointInfo(int iIndex)
		{
			return m_vecJointInfo[iIndex];		
		}
		core::array<SJointInfo> &GetJointInfoVector()
		{
			return m_vecJointInfo;
		}
		
	protected:		
		core::array< SJointInfo > m_vecJointInfo; //在这里存储了当前变换的结果
	public:
		CSkeleton *m_pResSkeleton;
	public:
		bool Export(io::IWriteFile *pWriteFile);
		bool Import(io::IReadFile *pReadFile);

	};

	class CSkeletonMngr : public CResMngr
	{
	public:

		static CSkeletonMngr *GetInstance();
	};


	inline CSkeletonMngr *SkeletonMngr()
	{
		return CSkeletonMngr::GetInstance();
	}


	class CSkinRes : public CRes
	{
		friend class CSkeletonAni;
	public:
		virtual ~CSkinRes();
	public:
		struct SGroup 
		{ 
			core::stringc Name; 
			core::array<u16> VertexIds; 
			u16 MaterialIdx; 
		};
		struct SBufferInfo
		{
			video::SMaterial Material;
			s8 Texture[128];
			u16 IndexStart;
			u16 IndexCount;	
		};
		
		struct SSkinVertex : public video::S3DVertex
		{
			u16 BoneId;
		};
	public:
		bool Export(io::IWriteFile *pFile);
		bool Import(io::IReadFile *pFile,video::IVideoDriver* driver);
	public:
		core::array<SBufferInfo> &GetBufferInfos()
		{
			return Buffers;
		}
		core::array<u16> &GetIndexBuffer()
		{
			return Indices;
		}
		core::aabbox3d<f32> GetBoundingBox()
		{
			return BoundingBox;
		}
		s32 GetVertexCount() const
		{
			return Vertices.size();
		}
		core::array<SSkinVertex> &GetVertexVector()
		{
			return Vertices;
		}
	protected:
		
		core::array<SSkinVertex> Vertices;
		core::array<u16> Indices; 
		core::aabbox3d<f32> BoundingBox;

	public:
		SBufferInfo *GetBufferFromMaterial(const video::SMaterial &mat);
		



	
	private:
		core::array<SBufferInfo> Buffers;

	};

	class CSkinResMngr : public CResMngr
	{
	public:
		static CSkinResMngr *GetInstance();

	};
	inline CSkinResMngr *SkinResMngr()
	{
		return CSkinResMngr::GetInstance();
	}
	class CSkin 
	{
		friend class CSkeletonAni;
	public:
		CSkin();
		~CSkin();
	public:
		bool SetSkinRes(CSkinRes *);
	public:
		struct CMeshBuffer : public IMeshBuffer
		{
		public:
			CMeshBuffer();

		public:
			//! returns the material of this meshbuffer 
			virtual const video::SMaterial& getMaterial() const
			{
				return m_Material;
			}

			//! returns the material of this meshbuffer 
			virtual video::SMaterial& getMaterial()
			{
				return m_Material;
			}

			//! returns pointer to vertices 
			virtual const void* getVertices() const;

			//! returns pointer to vertices 
			virtual void* getVertices();

			//! returns amount of vertices 
			virtual u32 getVertexCount() const;

			//! returns pointer to Indices 
			virtual const u16* getIndices() const;

			//! returns pointer to Indices 
			virtual u16* getIndices();

			//! returns amount of indices 
			virtual u32 getIndexCount() const;

			//! returns an axis aligned bounding box 
			virtual const core::aabbox3d<f32>& getBoundingBox() const;

			//! set user axis aligned bounding box
			virtual void setBoundingBox( const core::aabbox3df& box);

			//! returns which type of vertex data is stored. 
			virtual video::E_VERTEX_TYPE getVertexType() const;

			//! returns the byte size (stride, pitch) of the vertex
			virtual u32 getVertexPitch() const;
		public:
			CSkin *m_pSkin;
			video::SMaterial m_Material;
			u16 *m_Indices;
			u16 m_IndexCount;

		};
	protected:
		CSkinRes *m_pSkinRes;
		core::array<video::S3DVertex> AnimatedVertices;
		core::array<CMeshBuffer> MeshBuffer;
		core::aabbox3d<f32> BoundingBox;

	};
	
	class CSkeletonAni : public IAnimatedMeshMS3D, public IMesh
	{
	public:
		enum PLAY_MODE {PLAY,PAUSE,TRANSPLAY};
	public:
		CSkeletonAni(video::IVideoDriver* driver);
		~CSkeletonAni();
	public:
		bool Export(io::IWriteFile *pFile);
		bool Import(io::IReadFile *pFile);
	public:
		void SetAction(s32 frame,CAction_ *pAction,bool bLoop);
		void SetSkin(CSkin *pSkin);
		
		void SetSkeleton(CSkeleton *pSkeleton);
		
		CAction_ *GetAction()
		{
			return m_pAction_;
		}
		CSkin *GetSkin()
		{
			return m_pSkin;
		}
		CSkeleton *GetSkeleton()
		{
			return m_pSkeleton;
		}
		
	protected:
		CSkeleton *m_pSkeleton; //骨架描述
		CAction_ *m_pAction_;
		CSkin *m_pSkin; // 以后支持换装的话，这里应该是一个array:)
		void animate(s32 frame);
		void animateJoint(s32 frame);
		void TransformMesh(); // 根据当前的骨架变换Mesh
		core::array<video::S3DVertex> m_vecVert;
		core::array<SJoint> m_vecJoint; // 在这里存Joint的数据的原因是保存当前的状态，便于以后动作过度功能的加入
		core::aabbox3d<f32> m_BoundingBox;
	protected:
	

	private:
		core::array<video::S3DVertex> m_AnimatedVertices;  //供渲染用
	private:
		bool m_bNeedTransformNormal;
		s32 m_iframeActStart;
		bool m_bHasAnimation;
		f32 m_fTotalTime;
	//开始合并了	
	public: 
		bool LoadOldMs3dMesh(io::IReadFile *pReadFile0);
	private:
		video::IVideoDriver* m_pDriver;

		bool m_bTransitionEnable;
		bool m_bTransiting; // 正在过渡
		
		f32 m_fTransitionTimeEnd;
		f32 m_fTransitionTimeLast;
		bool m_bLoop;


	public:

		// IMesh Interface
		virtual s32 getFrameCount()
		{
			return s32(m_fTotalTime);
		}

		//! returns the animated mesh based on a detail level. 0 is the lowest, 255 the highest detail. Note, that some Meshes will ignore the detail level.
		virtual IMesh* getMesh(s32 frame, s32 detailLevel=255, s32 startFrameLoop=-1, s32 endFrameLoop=-1);

		//! returns amount of mesh buffers.
		virtual u32 getMeshBufferCount() const;

		//! returns pointer to a mesh buffer
		virtual IMeshBuffer* getMeshBuffer(u32 nr) const;

		//! Returns pointer to a mesh buffer which fits a material
 		/** \param material: material to search for
		\return Returns the pointer to the mesh buffer or 
		NULL if there is no such mesh buffer. */
		virtual IMeshBuffer* getMeshBuffer( const video::SMaterial &material) const;

		//! returns an axis aligned bounding box
		virtual const core::aabbox3d<f32>& getBoundingBox() const
		{
			return m_BoundingBox;
		}

		//! set user axis aligned bounding box
		virtual void setBoundingBox( const core::aabbox3df& box);

		//! sets a flag of all contained materials to a new value
		virtual void setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newvalue);

		//! Returns the type of the animated mesh.
		virtual E_ANIMATED_MESH_TYPE getMeshType() const;

		//! Returns a pointer to a transformation matrix of a part of the 
		//! mesh based on a frame time.
		virtual core::matrix4* getMatrixOfJoint(s32 jointNumber, s32 frame);

		//! Gets joint count.
		virtual s32 getJointCount() const;

		//! Gets the name of a joint.
		virtual const c8* getJointName(s32 number) const;

		//! Gets a joint number from its name
		virtual s32 getJointNumber(const c8* name) const;


	};

	

	
}
}
};

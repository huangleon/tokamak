#pragma once
//////////////////////////////////////////////////////////////////
//�ļ��� MilkShape3DMesh.h
//������ MilkShape3D�Ķ�ȡ�����Ҿ�����չ��֧�ֶ������
//		��ԭ��MilkShape3D�ĸĽ����ڣ�
//		1.֧��Ԥ�����Χ�У�ʡ��Framemove��Ŀ���
//		2.��ת��Ϣ����Ԫ�������棬�滻ԭ��ֻ��ʹ����Ԫ������ֵ�ķ���
//		3.֧�ֿ��Ը�����Ҫ���ص����ߵı任���ڲ���Ҫ���յĵط�ʡ�����ߵı任�����Ч�ʡ�
//		4.��ԭ���ѹǼܴ�ʹ����仯ת��Ϊ����仯������cpu��cache������,���ұ��ڽ������ļ����з���
//		5. ֧�ֶ����л�ʱ��ƽ�����ɹ���
//		6.�ڽ��������ȡʱ���������Թ��ˣ��ص�mipmap,�ܽ�ʡһ�����ڴ�
//		7.Ϊ�˱��ڼ��ٶ�ȡ�����Դ洢Ϊ�¸�ʽ
//��ʷ��
//		����				����
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
		//�뿪����
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
		core::quaternion Rotation; //��Ϊ��ת��Ԫ��
		core::vector3df Translation;				
		core::matrix4 AbsoluteTransformationAnimated; //������ת����
		core::matrix4 RelativeTransformation;
		s32 Parent; //���ڵ�			

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
		//����һ���ڵ����ֵõ������ڵ�
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
		core::array< SJointInfo > m_vecJointInfo; //������洢�˵�ǰ�任�Ľ��
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
		CSkeleton *m_pSkeleton; //�Ǽ�����
		CAction_ *m_pAction_;
		CSkin *m_pSkin; // �Ժ�֧�ֻ�װ�Ļ�������Ӧ����һ��array:)
		void animate(s32 frame);
		void animateJoint(s32 frame);
		void TransformMesh(); // ���ݵ�ǰ�ĹǼܱ任Mesh
		core::array<video::S3DVertex> m_vecVert;
		core::array<SJoint> m_vecJoint; // �������Joint�����ݵ�ԭ���Ǳ��浱ǰ��״̬�������Ժ������ȹ��ܵļ���
		core::aabbox3d<f32> m_BoundingBox;
	protected:
	

	private:
		core::array<video::S3DVertex> m_AnimatedVertices;  //����Ⱦ��
	private:
		bool m_bNeedTransformNormal;
		s32 m_iframeActStart;
		bool m_bHasAnimation;
		f32 m_fTotalTime;
	//��ʼ�ϲ���	
	public: 
		bool LoadOldMs3dMesh(io::IReadFile *pReadFile0);
	private:
		video::IVideoDriver* m_pDriver;

		bool m_bTransitionEnable;
		bool m_bTransiting; // ���ڹ���
		
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

#include "CMilkShape3DMesh.h"
#include "os.h"
#include "IVideoDriver.h"
#include "quaternion.h"
#include "IWriteFile.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if (p) { delete(p); (p) = NULL;}
#endif

namespace irr{
namespace scene{
namespace sklani{
	using namespace video;
	using namespace io;
	using namespace core;

	//常量定义
	const f32 fTransitionTime = 300.f; // 300毫秒


	#if defined(_MSC_VER) ||  defined(__BORLANDC__) || defined (__BCPLUSPLUS__) 
	#	pragma pack( push, packing )
	#	pragma pack( 1 )
	#	define PACK_STRUCT
	#elif defined( __GNUC__ )
	#	define PACK_STRUCT	__attribute__((packed))
	#else
	#	error compiler not supported
	#endif


	// File header
	struct MS3DHeader
	{
		c8 ID[10];
		s32 Version;
	} PACK_STRUCT;

	// Vertex information
	struct MS3DVertex
	{
		u8 Flags;
		f32 Vertex[3];
		s8 BoneID;
		u8 RefCount;
	} PACK_STRUCT;

	// Triangle information
	struct MS3DTriangle
	{
		u16 Flags;
		u16 VertexIndices[3];
		f32 VertexNormals[3][3];
		f32 S[3], T[3];
		u8 SmoothingGroup;
		u8 GroupIndex;
	} PACK_STRUCT;

	// Material information
	struct MS3DMaterial
	{
		s8 Name[32];
		f32 Ambient[4];
		f32 Diffuse[4];
		f32 Specular[4];
		f32 Emissive[4];
		f32 Shininess;	// 0.0f - 128.0f
		f32 Transparency;	// 0.0f - 1.0f
		u8 Mode;	// 0, 1, 2 is unused now
		s8 Texture[128];
		s8 Alphamap[128];
	} PACK_STRUCT;

	// Joint information
	struct MS3DJoint
	{
		u8 Flags;
		s8 Name[32];
		s8 ParentName[32];
		f32 Rotation[3];
		f32 Translation[3];
		u16 NumRotationKeyframes;
		u16 NumTranslationKeyframes;
	} PACK_STRUCT;

	
	// Keyframe data
	struct MS3DKeyframe
	{
		f32 Time;
		f32 Parameter[3];
	} PACK_STRUCT;

	// Default alignment
	#if defined(_MSC_VER) ||  defined(__BORLANDC__) || defined (__BCPLUSPLUS__) 
	#	pragma pack( pop, packing )
	#endif

	#undef PACK_STRUCT


	//晕了，文件格式用的是1字节对齐，在这里要转化为1字节对齐的
#define MEMCPY1(a) memcpy(&a,pPtr,sizeof(a));pPtr += sizeof(a)
#define MEMCPY2(a,b) memcpy(a,pPtr,sizeof(a[0]) * (b)); pPtr += sizeof(a[0]) * (b)
#define MEMCPY3(a,b,c) memcpy(a,pPtr,(b) * (c)); pPtr += (b) * (c)
	struct MS3DVertex_t
	{
		u8 Flags;
		f32 Vertex[3];
		s8 BoneID;
		u8 RefCount;
		void Import(const u8 *pPtr)
		{
			MEMCPY1(Flags);	
			MEMCPY2(Vertex,3);
			MEMCPY1(BoneID);
			MEMCPY1(RefCount);
		}
	} ;

	// Triangle information
	struct MS3DTriangle_t
	{
		u16 Flags;
		u16 VertexIndices[3];
		f32 VertexNormals[3][3];
		f32 S[3], T[3];
		u8 SmoothingGroup;
		u8 GroupIndex;
		void Import(const u8 *pPtr)
		{
			MEMCPY1(Flags);
			MEMCPY2(VertexIndices,3);
			MEMCPY3(VertexNormals,9 ,sizeof(f32));
			MEMCPY2(S,3);
			MEMCPY2(T,3);
			MEMCPY1(SmoothingGroup);
			MEMCPY1(GroupIndex);			
		}
	} ;

	// Material information
	struct MS3DMaterial_t
	{
		s8 Name[32];
		f32 Ambient[4];
		f32 Diffuse[4];
		f32 Specular[4];
		f32 Emissive[4];
		f32 Shininess;	// 0.0f - 128.0f
		f32 Transparency;	// 0.0f - 1.0f
		u8 Mode;	// 0, 1, 2 is unused now
		s8 Texture[128];
		s8 Alphamap[128];
		void Import(const u8 *pPtr)
		{			
			MEMCPY2(Name,32 );
			MEMCPY2(Ambient,4);
			MEMCPY2(Diffuse,4);
			MEMCPY2(Specular,4);			
			MEMCPY2(Emissive,4);
			MEMCPY1(Shininess);	// 0.0f - 128.0f
			MEMCPY1(Transparency);	// 0.0f - 1.0f
			MEMCPY1(Mode);	// 0, 1, 2 is unused now
			MEMCPY2(Texture ,128);
			MEMCPY2(Alphamap,128);
		}
	} ;

	// Joint information
	struct MS3DJoint_t
	{
		u8 Flags;
		s8 Name[32];
		s8 ParentName[32];
		f32 Rotation[3];
		f32 Translation[3];
		u16 NumRotationKeyframes;
		u16 NumTranslationKeyframes;
		void Import(const u8 *pPtr)
		{
			MEMCPY1(Flags);
			MEMCPY2(Name,32);
			MEMCPY2(ParentName,32);
			MEMCPY2(Rotation,3);
			MEMCPY2(Translation,3);
			MEMCPY1(NumRotationKeyframes);
			MEMCPY1(NumTranslationKeyframes);
			
		}
	} ;


	//仅仅是用来转换用
	struct SJointImportInfo
	{
		core::stringc Name;
		core::matrix4 RelativeTransformation;
		core::matrix4 AbsoluteTransformation;			
		s32 Parent;
		core::stringc ParentName;

		bool ExportInfo(SJointInfo &info)
		{
			info.strName = Name;
			if (Parent == -1)
			{
				info.wParentIndex = (u16)-1;
			}
			else
			{
				info.wParentIndex = (u16)Parent;
			}
			info.RelativeTransformation = RelativeTransformation;
			return true;
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CRes::CRes()
	{
		m_pResMngr = NULL;
	}
	CRes::~CRes()
	{
		if (m_pResMngr) m_pResMngr->RemoveRes(m_strName);
	}
	bool CResMngr::RegisterRes(const core::stringc &strName,CRes *pRes)
	{
		MAP_NAME2RES::Node *pNode = m_mapRes.find(strName);		
		if (pNode != NULL) return false;
		pRes->SetResName(strName);
		m_mapRes[strName] = pRes;
		pRes->m_pResMngr = this;
		return true;
	}
	void CResMngr::RemoveRes(const core::stringc &strName)
	{	
		m_mapRes.remove(strName);
	}
	CRes *CResMngr::QueryRes(const core::stringc &strName)
	{
		MAP_NAME2RES::Node *pNode = m_mapRes.find(strName);
		if (pNode == NULL) return NULL;
		CRes *pRes = pNode->getValue();
		pRes->grab();
		return pRes;
	}
	void CResMngr::Clear()
	{
		MAP_NAME2RES::Iterator iter = m_mapRes.getIterator();
		while (!iter.atEnd())
		{
			MAP_NAME2RES::Node *pNode = iter.getNode();
			CRes *pRes = pNode->getValue();
			pRes->drop();
			pRes = NULL;
			iter++;
		}
	}

	CActionMngr *CActionMngr::GetInstance()
	{
		static CActionMngr inst;
		return &inst;
	}

	CSkinResMngr *CSkinResMngr::GetInstance()
	{
		static CSkinResMngr inst;
		return &inst;
	}

	CSkeletonMngr *CSkeletonMngr::GetInstance()
	{
		static CSkeletonMngr inst;
		return &inst;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CSkeleton::CSkeleton()
	{
		m_pResSkeleton = NULL;
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CSkeleton::~CSkeleton()
	{
		//if (m_pResSkeleton) m_pResSkeleton->drop();
		m_pResSkeleton = NULL;

	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CSkeleton::operator = (const CSkeleton &skl)
	{
		for (int i = 0; i < (s32)skl.m_vecJointInfo.size(); i++)
		{
			m_vecJointInfo[i] = skl.m_vecJointInfo[i];
		}	
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool CSkeleton::Export(io::IWriteFile *pWriteFile)
	{
		s32 size = (s32)m_vecJointInfo.size();
		pWriteFile->write(&size,sizeof(s32));
		for (s32 i = 0; i < size; i++)
		{
			SJointInfo &info = m_vecJointInfo[i];
			char szBuffer[128];
//			strcpy_s(szBuffer,128,m_vecJointInfo[i].strName.c_str());
			strcpy(szBuffer,m_vecJointInfo[i].strName.c_str());
			pWriteFile->write(szBuffer,128);
			pWriteFile->write(&info.Trans,sizeof(info.Trans));
			pWriteFile->write(&info.Rotate,sizeof(info.Rotate));
			pWriteFile->write(&info.RelativeTransformation,sizeof(info.RelativeTransformation));
			pWriteFile->write(&info.AbsoluteTransformation,sizeof(info.AbsoluteTransformation));
			pWriteFile->write(&info.wParentIndex,sizeof(info.wParentIndex));

		}
		return true;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool CSkeleton::Import(io::IReadFile *pReadFile)
	{
		s32 size ;
		pReadFile->read(&size,sizeof(s32));
		for (s32 i = 0; i < size; i++)
		{
			m_vecJointInfo.push_back(SJointInfo());
			SJointInfo &info = m_vecJointInfo.getLast();
			char szBuffer[128];
			pReadFile->read(szBuffer,128);
			info.strName = szBuffer;
			pReadFile->read(&info.Trans,sizeof(info.Trans));
			pReadFile->read(&info.Rotate,sizeof(info.Rotate));
			pReadFile->read(&info.RelativeTransformation,sizeof(info.RelativeTransformation));
			pReadFile->read(&info.AbsoluteTransformation,sizeof(info.AbsoluteTransformation));
			pReadFile->read(&info.wParentIndex,sizeof(info.wParentIndex));
		
		}
		return true;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int CSkeleton::GetJointIndex(const core::stringc &NameFind) const
	{
		s32 i; 
		for (i = 0; i < (s32)m_vecJointInfo.size(); i++)
		{
			if (NameFind == m_vecJointInfo[i].strName) break;		
		}
		if (i == (s32)m_vecJointInfo.size()) return -1;
		return i;
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CAction_::CAction_()
	{
		m_pKeyframe = NULL;
		m_iJointNum = 0;
		m_iFrameNum = 0;
		m_pKeyframeTime = 0;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CAction_::~CAction_()
	{
		SAFE_DELETE(m_pKeyframe);
		SAFE_DELETE(m_pKeyframeTime);
	}


	bool CAction_::AddAction(CAction_ *pAction,SSubActionInfo &info)
	{
		s32 iTotalFrameNum = pAction->GetFrameNum() + m_iFrameNum;
		info.m_iFrameStart = m_iFrameNum;
		info.m_iFrameEnd = m_iFrameNum + pAction->GetFrameNum();
		m_iFrameNum = iTotalFrameNum;
		f32 *pNewFrameTime = new f32[iTotalFrameNum];
		memcpy(pNewFrameTime,m_pKeyframeTime,sizeof(f32) * iTotalFrameNum);
		SAFE_DELETE(m_pKeyframeTime);
		m_pKeyframeTime = pNewFrameTime;
		memcpy(&pNewFrameTime[info.m_iFrameStart],pAction->m_pKeyframeTime,pAction->GetFrameNum() * sizeof(f32));

		SKeyframe *pNewKeyFrame = new SKeyframe[iTotalFrameNum];
		memcpy(pNewKeyFrame,m_pKeyframe,sizeof(SKeyframe) * iTotalFrameNum);
		SAFE_DELETE(m_pKeyframe);
		m_pKeyframe = pNewKeyFrame;
		memcpy(&pNewKeyFrame[info.m_iFrameStart],pAction->m_pKeyframe,pAction->GetFrameNum() * sizeof(SKeyframe));
		return true;

	}
	bool CAction_::AddAction(const core::stringc &strActionName,SSubActionInfo &info,IrrlichtDevice *Device)
	{
		CAction_ *pNewAction = new CAction_;
		bool bSucced = pNewAction->ImportActionFromFile(strActionName,Device);
		if (!bSucced) return false;
		AddAction(pNewAction,info);
		pNewAction->drop();
		return true;
	}

	bool CAction_::Export(io::IWriteFile *pWriteFile)
	{
		//帧数
		pWriteFile->write(&m_iFrameNum,sizeof(s32));
		pWriteFile->write(&m_iJointNum,sizeof(s32));
		pWriteFile->write(&m_fFramePerSecond,sizeof(f32));
		pWriteFile->write(m_pKeyframeTime,sizeof(f32) * m_iFrameNum );
		pWriteFile->write(m_pKeyframe,sizeof(SKeyframe) * m_iFrameNum * m_iJointNum);
		return true;
			
	}
	bool CAction_::Import(io::IReadFile *pReadFile)
	{
		pReadFile->read(&m_iFrameNum,sizeof(s32));
		pReadFile->read(&m_iJointNum,sizeof(s32));
		pReadFile->read(&m_fFramePerSecond,sizeof(f32));
		SAFE_DELETE(m_pKeyframeTime);
		SAFE_DELETE(m_pKeyframe);
		SetSize(m_iJointNum,m_iFrameNum);
		pReadFile->read(m_pKeyframeTime,sizeof(f32) * m_iFrameNum );
		pReadFile->read(m_pKeyframe,sizeof(SKeyframe) * m_iFrameNum * m_iJointNum);
		return true;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	bool CAction_::GetKeyframeIndex(f32 fTime,s32 &iFrameIndex0,s32 &iFrameIndex1,f32 &fScale,bool bLoop) const
	{
		if (m_iFrameNum <= 0) return false;
		fScale = 0.0f;
		if ((fTime > m_pKeyframeTime[m_iFrameNum - 1]) && bLoop)
		{
		//	fTime = fmodf(fTime,m_pKeyframeTime[m_iFrameNum - 1]);
		}
		if (fTime < m_pKeyframeTime[0])
		{
			iFrameIndex0 = iFrameIndex1 = 0;
		}
		else if (fTime > m_pKeyframeTime[m_iFrameNum - 1])
		{
			iFrameIndex0 = iFrameIndex1 = m_iFrameNum - 1;				
		}
		else
		{
			for (s32 i = 0; i < m_iFrameNum; i++)
			{	

				if (m_pKeyframeTime[i] <= fTime && m_pKeyframeTime[i + 1] >= fTime)
				{
					iFrameIndex0 = i;
					iFrameIndex1 = i + 1;
					fScale = (fTime - m_pKeyframeTime[i]) / (m_pKeyframeTime[i + 1] - m_pKeyframeTime[i]);
					break;
				}
				
			}
			if (iFrameIndex1 > m_iFrameNum - 1) iFrameIndex1 = m_iFrameNum - 1;
		}
		return true;

	}
	bool CAction_::ImportActionFromFile(const stringc &strName,IrrlichtDevice *Device)
	{
		io::IReadFile* file = Device->getFileSystem()->createAndOpenFile(strName.c_str());
		if (!file) return false;
		ImportActionFromFile(file);
		file->drop();
		return true;
	}


	bool CAction_::ImportActionFromFile(io::IReadFile *file)
	{
		s32 i=0,j;	
		if (!file)
			return false;
	
		// find file size
		size_t fileSize = file->getSize();

		// read whole file

		u8* buffer = new u8[fileSize];
		size_t read = (s32)file->read(buffer, fileSize);
		if (read != fileSize)
		{
			delete [] buffer;
			os::Printer::log("Could not read full file. Loading failed", file->getFileName(), ELL_ERROR);
			return false;
		}

		// read header

		const u8 *pPtr = (u8*)((void*)buffer);
		MS3DHeader Header;
		MEMCPY1(Header);
		
		if ( strncmp( Header.ID, "MS3D000000", 10 ) != 0 )
		{
			delete [] buffer;
			os::Printer::log("Not a valid Milkshape3D Model File. Loading failed", file->getFileName(), ELL_ERROR);
			return false;
		}

		#ifdef __BIG_ENDIAN__
			Header.Version = os::Byteswap::byteswap(Header.Version);
		#endif
		if ( Header.Version < 3 || Header.Version > 4 )
		{
			delete [] buffer;
			os::Printer::log("Only Milkshape3D version 1.3 and 1.4 is supported. Loading failed", file->getFileName(), ELL_ERROR);
			return false;
		}



		// get pointers to data

		// vertices
		u16 numVertices = 0;
		MEMCPY1(numVertices);

	#ifdef __BIG_ENDIAN__
		numVertices = os::Byteswap::byteswap(numVertices);
	#endif	
		pPtr += sizeof(MS3DVertex) * numVertices;

			
		// triangles
		u16 numTriangles = 0;//*(u16*)pPtr;
		MEMCPY1(numTriangles);
	#ifdef __BIG_ENDIAN__
		numTriangles = os::Byteswap::byteswap(numTriangles);
	#endif
		pPtr += sizeof(MS3DTriangle) * numTriangles;
	


	
		// groups
		u16 numGroups = 0;//*(u16*)pPtr;
		MEMCPY1(numGroups);
	#ifdef __BIG_ENDIAN__
		numGroups = os::Byteswap::byteswap(numGroups);
	#endif
		
		
	
		//skip groups
		for (i=0; i<numGroups; ++i)
		{			

			pPtr += 33; // name and 1 byte flags
			u16 triangleCount = 0;//*(u16*)pPtr;
			MEMCPY1(triangleCount);
	#ifdef __BIG_ENDIAN__
			triangleCount = os::Byteswap::byteswap(triangleCount);
	#endif			
			
			//pPtr += sizeof(u16) * triangleCount; // triangle indices
			for (j=0; j<triangleCount; ++j) 
			{
				pPtr += sizeof (u16);
			}				
			pPtr += sizeof(c8); // material index
		}
		
		// skip materials
		u16 numMaterials = 0;//*(u16*)pPtr;
		MEMCPY1(numMaterials);
	

	#ifdef __BIG_ENDIAN__
		numMaterials = os::Byteswap::byteswap(numMaterials);
	#endif
		

		//core::array<CSkinRes::SMS3DMeshBuffer> &Buffers = pNewSkin->Buffers;
	


		pPtr += sizeof(MS3DMaterial) * numMaterials;

		


		// animation time
		m_fFramePerSecond = .0f;//*(f32*)pPtr;
		memcpy(&m_fFramePerSecond,pPtr,sizeof(f32));

	#ifdef __BIG_ENDIAN__
		framesPerSecond = os::Byteswap::byteswap(framesPerSecond);
	#endif
		pPtr += sizeof(f32) * 2; // fps and current time
		
		s32 frameCount = 0;//*(s32*)pPtr;
		MEMCPY1(frameCount);
	#ifdef __BIG_ENDIAN__
		frameCount = os::Byteswap::byteswap(frameCount);
	#endif		

		u16 jointCount = 0;//*(u16*)pPtr;
		MEMCPY1(jointCount);
	#ifdef __BIG_ENDIAN__
		jointCount = os::Byteswap::byteswap(jointCount);
	#endif		
		// load joints	
	
		MS3DJoint_t JointInfo ;// (MS3DJoint *)pPtr;
		//memcpy(&JointInfo,pPtr,sizeof(MS3DJoint));
		JointInfo.Import(pPtr);
			
		SetSize(jointCount,JointInfo.NumRotationKeyframes);
	
		for (i=0; i<jointCount; ++i)
		{
			MS3DJoint_t infoJoint ;//= (MS3DJoint*)pPtr;
			infoJoint.Import(pPtr);
	#ifdef __BIG_ENDIAN__
			for (j=0; j<3; ++j)
				infoJoint.Rotation[j] = os::Byteswap::byteswap(infoJoint.Rotation[j]);
			for (j=0; j<3; ++j)
				infoJoint.Translation[j] = os::Byteswap::byteswap(infoJoint.Translation[j]);
			infoJoint.NumRotationKeyframes= os::Byteswap::byteswap(infoJoint.NumRotationKeyframes);
			infoJoint.NumTranslationKeyframes = os::Byteswap::byteswap(infoJoint.NumTranslationKeyframes);
	#endif
			pPtr += sizeof(MS3DJoint);
			
					
			// get rotation keyframes
				
			for (j=0; j<infoJoint.NumRotationKeyframes; ++j)
			{
				MS3DKeyframe kf;// (MS3DKeyframe*)pPtr;
				memcpy(&kf,pPtr,sizeof(MS3DKeyframe));
	#ifdef __BIG_ENDIAN__
				kf.Time = os::Byteswap::byteswap(kf.Time);
				for (u32 l=0; l<3; ++l)
					kf.Parameter[l] = os::Byteswap::byteswap(kf.Parameter[l]);
	#endif
				pPtr += sizeof(MS3DKeyframe);								
				CAction_::SKeyframe *key = &GetJointKeyframe(i,j);
				m_pKeyframeTime[j] = kf.Time * 1000.0f;
				key->m_qRotate.set(kf.Parameter[0],kf.Parameter[1],kf.Parameter[2]);				
				key->m_qRotate.makeInverse();
			}

			// get translation keyframes
			for (j=0; j<infoJoint.NumTranslationKeyframes; ++j)
			{
				MS3DKeyframe kf;// = (MS3DKeyframe*)pPtr;
				memcpy(&kf,pPtr,sizeof(MS3DKeyframe));
	#ifdef __BIG_ENDIAN__
				kf.Time = os::Byteswap::byteswap(kf.Time);
				for (u32 l=0; l<3; ++l)
					kf.Parameter[l] = os::Byteswap::byteswap(kf.Parameter[l]);
	#endif
				pPtr += sizeof(MS3DKeyframe);
				
				CAction_::SKeyframe *key = &GetJointKeyframe(i,j);
				key->m_vTrans.set(kf.Parameter[0],kf.Parameter[1],kf.Parameter[2]);	
			}
		}		
		delete buffer;
		return true;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool CAction_::SplitToSubAction(core::array<SSubActionInfo> &arrayInfo,core::array<CAction_ *> &arrayRet)
	{
		arrayRet.clear();
		
		for (s32 i = 0; i < (s32)arrayInfo.size();i++)
		{
			CAction_ *pNewAction = new CAction_;
			s32 iFrameStart = arrayInfo[i].m_iFrameStart;
			s32 iFrameCount = arrayInfo[i].m_iFrameEnd - arrayInfo[i].m_iFrameStart;
			
			pNewAction->SetSize(m_iJointNum,iFrameCount);
			f32 fTimeStart = m_pKeyframeTime[iFrameStart];
			for (s32 j = 0; j < iFrameCount; j++)
			{
				pNewAction->m_pKeyframeTime[j] = m_pKeyframeTime[iFrameStart + j] - fTimeStart;
				pNewAction->m_pKeyframe[i].m_qRotate = m_pKeyframe[iFrameStart + j].m_qRotate;
				pNewAction->m_pKeyframe[i].m_vTrans = m_pKeyframe[iFrameStart + j].m_vTrans;
			}
			arrayRet.push_back(pNewAction);
		}
		return true;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CAction_::SetSize(s32 iJointNum,s32 iFrameNum)
	{
		if (m_pKeyframe) 
		{
			delete m_pKeyframe;
			m_pKeyframe = NULL;
		}
		m_pKeyframe = new SKeyframe[iJointNum * iFrameNum];
		m_pKeyframeTime = new f32[iJointNum * iFrameNum];
		m_iJointNum = iJointNum;
		m_iFrameNum = iFrameNum;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CSkinRes::~CSkinRes()
	{
		
	}
	bool CSkinRes::Export(io::IWriteFile *file)
	{
		//材质
		s32 size;
		size = (s32)Buffers.size();
		file->write(&size,sizeof(size));
		file->write(Buffers.const_pointer(),sizeof(SBufferInfo) * size);
		//IndexBuffer
		size = (s32)Indices.size();
		file->write(&size,sizeof(size));
		file->write(Indices.const_pointer(),sizeof(u16) * size);
		//Vertex
		size = (s32)Vertices.size();
		file->write(&size,sizeof(size));
		file->write(Vertices.const_pointer(),sizeof(SSkinVertex) * size);

		//BoundBox
		file->write(&BoundingBox,sizeof(aabbox3d<f32>));
		return true;
	}
	bool CSkinRes::Import(io::IReadFile *file,video::IVideoDriver* driver)
	{
		s32 size;
		//size = (s32)Buffers.size();
		file->read(&size,sizeof(s32));
		Buffers.set_used(size);
		file->read(Buffers.pointer(),sizeof(SBufferInfo) * size);
		for (s32 i = 0; i < size; i++)
		{
			Buffers[i].Material.Textures[0] = driver->getTexture((const c8 *)Buffers[i].Texture);
		}
		//IndexBuffer

		file->read(&size,sizeof(s32));
		Indices.set_used(size);
		file->read(Indices.pointer(),sizeof(u16) * size);
		//Vertex
		file->read(&size,sizeof(s32));
		Vertices.set_used(size);
		file->read(Vertices.pointer(),sizeof(SSkinVertex) * size);

		//BoundBox
		file->read(&BoundingBox,sizeof(aabbox3d<f32>));
		return true;

	}

	CSkinRes::SBufferInfo * CSkinRes::GetBufferFromMaterial(const video::SMaterial &mat)
	{
		for (s32 i = 0; i < (s32)Buffers.size(); i++)
		{
			if (Buffers[i].Material == mat) return &Buffers[i];
		}
		return NULL;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CSkin
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CSkin::CSkin()
	{
		m_pSkinRes = NULL;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool CSkin::SetSkinRes(CSkinRes *pSkinRes)
	{
		if (pSkinRes == m_pSkinRes) return true;
		if (pSkinRes)
		{
			if (m_pSkinRes) m_pSkinRes->drop();
			m_pSkinRes = pSkinRes;
			BoundingBox = pSkinRes->GetBoundingBox();
			AnimatedVertices.set_used(pSkinRes->GetVertexCount());
			array<CSkinRes::SSkinVertex> &vecVertex = pSkinRes->GetVertexVector();
			for (s32 i = 0; i < pSkinRes->GetVertexCount(); i++)
			{
				AnimatedVertices[i] = vecVertex[i];
			}
			MeshBuffer.clear();
			array<CSkinRes::SBufferInfo> &Buffers = pSkinRes->GetBufferInfos();
			for (s32 i = 0; i < (s32)Buffers.size(); i++)
			{
				MeshBuffer.push_back(CMeshBuffer());
				MeshBuffer[i].m_Material = Buffers[i].Material;
				MeshBuffer[i].m_IndexCount = Buffers[i].IndexCount;
				MeshBuffer[i].m_Indices = pSkinRes->GetIndexBuffer().pointer() + Buffers[i].IndexStart;
				MeshBuffer[i].m_pSkin = this;
			}
			return true;
		}
		return false;
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CSkin::~CSkin()
	{
		if (m_pSkinRes) m_pSkinRes->drop();
		m_pSkinRes = NULL;
	
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	CSkeletonAni::CSkeletonAni(video::IVideoDriver* driver)
	{
		m_bHasAnimation = false;
		m_pDriver = driver;
		m_fTotalTime = .0f;
		m_bLoop = true;
		m_pSkin = NULL;
		m_pAction_ = NULL;
		m_pSkeleton = NULL;

		m_iframeActStart = 0;
		m_bTransitionEnable = false;
		m_bTransiting = false; // 正在过渡
		
		m_fTransitionTimeEnd = .0f;
		m_fTransitionTimeLast = .0f;
		m_bLoop = true;;

		this->m_bNeedTransformNormal =false;

	}
	CSkeletonAni::~CSkeletonAni()
	{
		SAFE_DELETE(m_pSkin);
		SAFE_DELETE(m_pAction_);
		SAFE_DELETE(m_pSkeleton);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CSkeletonAni::LoadOldMs3dMesh(IReadFile *file)
	{
		s32 i=0,j;	
		if (!file)
			return false;

		m_bHasAnimation = false;

		// find file size
		stringc strName = file->getFileName();
		//先看当前是否存在此名字的骨架和mesh,若找到，则直接返回
		CSkeleton *pSkeletonRes = (CSkeleton *)SkeletonMngr()->QueryRes(strName);
		if (pSkeletonRes != NULL)
		{
			CSkeleton *pNewSkeleton = new CSkeleton;
			*pNewSkeleton = *pSkeletonRes;
			pNewSkeleton->m_pResSkeleton = pSkeletonRes;
			
			CSkinRes *pNewSkinRes = (CSkinRes *)SkinResMngr()->QueryRes(strName);
			if (pNewSkinRes) 
			{
				CSkin *pNewSkin = new CSkin;
				pNewSkin->SetSkinRes(pNewSkinRes);
				SetSkin(pNewSkin);
				SetSkeleton(pNewSkeleton);
				m_bHasAnimation = true;
				return true;
								
			}
			else
			{
				//不应该到这里，应该都存在
				os::Printer::log("不应该走到这里", file->getFileName(), ELL_ERROR);
				pNewSkeleton->drop();
				return false;

			}

		}
		


		


		size_t fileSize = file->getSize();

		// read whole file

		u8* buffer = new u8[fileSize];
		size_t read = (s32)file->read(buffer, fileSize);
		if (read != fileSize)
		{
			delete [] buffer;
			os::Printer::log("Could not read full file. Loading failed", file->getFileName(), ELL_ERROR);
			return false;
		}

		// read header

		const u8 *pPtr = (u8*)((void*)buffer);
		MS3DHeader Header;//(MS3DHeader*)pPtr;
		//由于是第一个读取的结构，因此就不用预处理了
		MEMCPY1(Header);
		if ( strncmp( Header.ID, "MS3D000000", 10 ) != 0 )
		{
			delete [] buffer;
			os::Printer::log("Not a valid Milkshape3D Model File. Loading failed", file->getFileName(), ELL_ERROR);
			return false;
		}

	#ifdef __BIG_ENDIAN__
		Header.Version = os::Byteswap::byteswap(Header.Version);
	#endif
		if ( Header.Version < 3 || Header.Version > 4 )
		{
			delete [] buffer;
			os::Printer::log("Only Milkshape3D version 1.3 and 1.4 is supported. Loading failed", file->getFileName(), ELL_ERROR);
			return false;
		}

		// get pointers to data

		// vertices
		u16 numVertices = 0;//*(u16*)pPtr;		
		MEMCPY1(numVertices);
	#ifdef __BIG_ENDIAN__
		numVertices = os::Byteswap::byteswap(numVertices);
	#endif	
		if (numVertices <= 0) return false;
		//由于不能在奇数地址上读双字节，那么在这里读取后的结构 应该是字节对齐的！，应该使用字节对齐的结构
		MS3DVertex_t *vertices = new MS3DVertex_t[numVertices];
		for (s32 i = 0; i < numVertices; i++)
		{
			vertices[i].Import(pPtr);
			pPtr += sizeof(MS3DVertex);
		}

	#ifdef __BIG_ENDIAN__
		for (i=0; i<numVertices; ++i)
			for (j=0; j<3; ++j)
				vertices[i].Vertex[j] = os::Byteswap::byteswap(vertices[i].Vertex[j]);
	#endif
		
		// triangles
		u16 numTriangles = 0;//*(u16*)pPtr;		
		MEMCPY1(numTriangles);
	
	#ifdef __BIG_ENDIAN__
		numTriangles = os::Byteswap::byteswap(numTriangles);
	#endif				
		

		MS3DTriangle_t *triangles = new MS3DTriangle_t[numTriangles];

		for (s32 i = 0; i < numTriangles;i++)
		{
			triangles[i].Import(pPtr);
			pPtr += sizeof(MS3DTriangle);
		}	


	#ifdef __BIG_ENDIAN__
		for (i=0; i<numTriangles; ++i)
		{
			triangles[i].Flags = os::Byteswap::byteswap(triangles[i].Flags);
			for (j=0; j<3; ++j)
			{
				triangles[i].VertexIndices[j] = os::Byteswap::byteswap(triangles[i].VertexIndices[j]);
				for (u16 k=0; k<3; ++k)
					triangles[i].VertexNormals[j][k] = os::Byteswap::byteswap(triangles[i].VertexNormals[j][k]);
				triangles[i].S[j] = os::Byteswap::byteswap(triangles[i].S[j]);
				triangles[i].T[j] = os::Byteswap::byteswap(triangles[i].T[j]);
			}
		}
	#endif
		
		// groups
		u16 numGroups = 0;//*(u16*)pPtr;
		MEMCPY1(numGroups);
	#ifdef __BIG_ENDIAN__
		numGroups = os::Byteswap::byteswap(numGroups);
	#endif	
		
		CSkinRes *pNewSkin = new CSkinRes;
		array<CSkinRes::SGroup> Groups;
		//skip groups
		for (i=0; i<numGroups; ++i)
		{
			Groups.push_back(CSkinRes::SGroup());
			CSkinRes::SGroup& grp = Groups.getLast();

			// The byte flag is before the name, so add 1
			grp.Name = ((const c8*) pPtr) + 1;

			pPtr += 33; // name and 1 byte flags
			u16 triangleCount = 0;//*(u16*)pPtr;
			MEMCPY1(triangleCount);
	
	#ifdef __BIG_ENDIAN__
			triangleCount = os::Byteswap::byteswap(triangleCount);
	#endif			
			
			//pPtr += sizeof(u16) * triangleCount; // triangle indices
			for (j=0; j<triangleCount; ++j) 
			{
	#ifdef __BIG_ENDIAN__
				grp.VertexIds.push_back(os::Byteswap::byteswap(*(u16*)pPtr));
				pPtr += sizeof (u16);
	#else
				
				u16 wIndex;
				MEMCPY1(wIndex);
				grp.VertexIds.push_back(wIndex);
	#endif
				
			}

			u8 uIndex = 0;
			MEMCPY1(uIndex);
			grp.MaterialIdx = uIndex;			
			 // material index
		}
		
		// skip materials
		u16 numMaterials = 0;
		MEMCPY1(numMaterials);
	#ifdef __BIG_ENDIAN__
		numMaterials = os::Byteswap::byteswap(numMaterials);
	#endif


		//core::array<CSkinRes::SMS3DMeshBuffer> &Buffers = pNewSkin->Buffers;
		core::array<CSkinRes::SBufferInfo> &Buffers = pNewSkin->Buffers;
		if(numMaterials <= 0) 
		{ 
			// if there are no materials, add at least one buffer
			Buffers.push_back (CSkinRes::SBufferInfo()); 		
		}

		for (i=0; i<numMaterials; ++i)
		{
			//MS3DMaterial *material = (MS3DMaterial*)pPtr;
			MS3DMaterial_t material;
			material.Import(pPtr);			
	#ifdef __BIG_ENDIAN__
			for (j=0; j<4; ++j)
				material->Ambient[j] = os::Byteswap::byteswap(material->Ambient[j]);
			for (j=0; j<4; ++j)
				material->Diffuse[j] = os::Byteswap::byteswap(material->Diffuse[j]);
			for (j=0; j<4; ++j)
				material->Specular[j] = os::Byteswap::byteswap(material->Specular[j]);
			for (j=0; j<4; ++j)
				material->Emissive[j] = os::Byteswap::byteswap(material->Emissive[j]);
			material->Shininess = os::Byteswap::byteswap(material->Shininess);
			material->Transparency = os::Byteswap::byteswap(material->Transparency);
	#endif
			pPtr += sizeof(MS3DMaterial);

			Buffers.push_back (CSkinRes::SBufferInfo ());
			CSkinRes::SBufferInfo& tmpBuffer = Buffers.getLast();

			tmpBuffer.Material.MaterialType = video::EMT_SOLID;

			tmpBuffer.Material.AmbientColor = video::SColorf(material.Ambient[0], material.Ambient[1], material.Ambient[2], material.Ambient[3]).toSColor ();
			tmpBuffer.Material.DiffuseColor = video::SColorf(material.Diffuse[0], material.Diffuse[1], material.Diffuse[2], material.Diffuse[3]).toSColor ();
			tmpBuffer.Material.EmissiveColor = video::SColorf(material.Emissive[0], material.Emissive[1], material.Emissive[2], material.Emissive[3]).toSColor ();
			tmpBuffer.Material.SpecularColor = video::SColorf(material.Specular[0], material.Specular[1], material.Specular[2], material.Specular[3]).toSColor ();
			tmpBuffer.Material.Shininess = material.Shininess;
//			strcpy_s((char *)tmpBuffer.Texture ,128, (const char *)material.Texture);
			strcpy((char *)tmpBuffer.Texture ,(const char *)material.Texture);
			m_pDriver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, false);	
			tmpBuffer.Material.Textures[0] =  m_pDriver->getTexture((const c8*)material.Texture);	
			
		}

		// animation time
		f32 framesPerSecond = .0f;//*(f32*)pPtr;
		MEMCPY1(framesPerSecond);
	#ifdef __BIG_ENDIAN__
		framesPerSecond = os::Byteswap::byteswap(framesPerSecond);
	#endif
		pPtr += sizeof(f32); // fps and current time
		
		s32 frameCount = 0;//*(s32*)pPtr;
		MEMCPY1(frameCount);
	#ifdef __BIG_ENDIAN__
		frameCount = os::Byteswap::byteswap(frameCount);
	#endif
		
		m_fTotalTime = (frameCount / framesPerSecond) * 1000.0f;
		
		u16 jointCount = 0;//*(u16*)pPtr;
		MEMCPY1(jointCount);
	#ifdef __BIG_ENDIAN__
		jointCount = os::Byteswap::byteswap(jointCount);
	#endif
		
		// load joints	

		//在这里生成一个骨架文件
		array<stringc> vecParentName;
		SJoint t;

	//	CAction_ *pAction = new CAction_;
	
		MS3DJoint_t JointInfo;
		JointInfo.Import(pPtr);
		if (JointInfo.NumRotationKeyframes > 0) m_bHasAnimation =true;
		
	//	pAction->SetSize(jointCount,pJointInfo->NumRotationKeyframes);
		array<SJointImportInfo> arrayJointInfo;
		
	



		for (i=0; i<jointCount; ++i)
		{
			MS3DJoint_t infoJoint;
			infoJoint.Import(pPtr);
			pPtr += sizeof(MS3DJoint);
			MS3DJoint_t *pJoint = &infoJoint;
	#ifdef __BIG_ENDIAN__
			for (j=0; j<3; ++j)
				pJoint->Rotation[j] = os::Byteswap::byteswap(pJoint->Rotation[j]);
			for (j=0; j<3; ++j)
				pJoint->Translation[j] = os::Byteswap::byteswap(pJoint->Translation[j]);
			pJoint->NumRotationKeyframes= os::Byteswap::byteswap(pJoint->NumRotationKeyframes);
			pJoint->NumTranslationKeyframes = os::Byteswap::byteswap(pJoint->NumTranslationKeyframes);
	#endif
			
			
			
			//开始读入各块骨骼
			arrayJointInfo.push_back(SJointImportInfo());
			SJointImportInfo *pJointInfo = &arrayJointInfo[i];
			pJointInfo->Name = pJoint->Name;
			pJointInfo->RelativeTransformation.setRotationRadians(vector3df(pJoint->Rotation[0],pJoint->Rotation[1],pJoint->Rotation[2]));
			pJointInfo->RelativeTransformation.setTranslation(vector3df(pJoint->Translation[0],pJoint->Translation[1],pJoint->Translation[2]));
			//就差一个父亲了，留到以后再找
			pJointInfo->ParentName = pJoint->ParentName;
			pJointInfo->Parent = -1;
			
			
			// get rotation keyframes
			pPtr += sizeof(MS3DKeyframe) * pJoint->NumRotationKeyframes;	
	//		for (j=0; j<pJoint->NumRotationKeyframes; ++j)
	//		{
	//			MS3DKeyframe* kf = (MS3DKeyframe*)pPtr;
	//#ifdef __BIG_ENDIAN__
	//			kf->Time = os::Byteswap::byteswap(kf->Time);
	//			for (u32 l=0; l<3; ++l)
	//				kf->Parameter[l] = os::Byteswap::byteswap(kf->Parameter[l]);
	//#endif
	//			pPtr += sizeof(MS3DKeyframe);								
	//			CAction_::SKeyframe *key = &pAction->GetJointKeyframe(i,j);
	//			pAction->m_pKeyframeTime[j] = kf->Time * 1000.0f;
	//			key->m_qRotate.set(kf->Parameter[0],kf->Parameter[1],kf->Parameter[2]);				
	//			key->m_qRotate.makeInverse();
	//		}

			pPtr += sizeof(MS3DKeyframe) * pJoint->NumTranslationKeyframes;	
			// get translation keyframes
	/*		for (j=0; j<pJoint->NumTranslationKeyframes; ++j)
			{
				MS3DKeyframe* kf = (MS3DKeyframe*)pPtr;
	#ifdef __BIG_ENDIAN__
				kf->Time = os::Byteswap::byteswap(kf->Time);
				for (u32 l=0; l<3; ++l)
					kf->Parameter[l] = os::Byteswap::byteswap(kf->Parameter[l]);
	#endif
				pPtr += sizeof(MS3DKeyframe);
				
				CAction_::SKeyframe *key = &pAction->GetJointKeyframe(i,j);
				key->m_vTrans.set(kf->Parameter[0],kf->Parameter[1],kf->Parameter[2]);	
			}*/
		}

		for (s32 i = 0; i < (s32)arrayJointInfo.size(); i++)
		{
			SJointImportInfo &info = arrayJointInfo[i];
			if (info.ParentName.size() == 0) continue;
			for (s32 j = 0; j < (s32)arrayJointInfo.size(); j++)
			{
				if (i == j) continue;
				if (info.ParentName == arrayJointInfo[j].Name)
				{
					info.Parent = j;
					break;
				}
				
			}
			if (info.Parent == -1)
				os::Printer::log("Found joint in model without parent.", ELL_WARNING);
		}
		
		// sets up all joints with initial rotation and translation
		for (i=0; i<(s32)arrayJointInfo.size(); ++i)
		{
			SJointImportInfo& info = arrayJointInfo[i];
			
			if (info.Parent == -1)
				info.AbsoluteTransformation  = info.RelativeTransformation;
			else
			{
				info.AbsoluteTransformation = arrayJointInfo[info.Parent].AbsoluteTransformation;
				info.AbsoluteTransformation *= info.RelativeTransformation;
			}			
		}

		

		
		// create vertices and indices, attach them to the joints.
		array<u16> &Indices = pNewSkin->Indices;
		CSkinRes::SSkinVertex v;
		array<CSkinRes::SSkinVertex> &Vertices = pNewSkin->Vertices;


		for (i=0; i<numTriangles; ++i)
		{
			for (j = 0; j<3; ++j)
			{
				v.TCoords.X = triangles[i].S[j];
				v.TCoords.Y = triangles[i].T[j];
				v.Normal.X = triangles[i].VertexNormals[j][0];
				v.Normal.Y = triangles[i].VertexNormals[j][1];
				v.Normal.Z = triangles[i].VertexNormals[j][2];
				if(triangles[i].GroupIndex < Groups.size() && Groups[triangles[i].GroupIndex].MaterialIdx < Buffers.size())
					v.Color = Buffers[Groups[triangles[i].GroupIndex].MaterialIdx].Material.DiffuseColor;
				else
					v.Color.set(255,255,255,255);
				v.Pos.X = vertices[triangles[i].VertexIndices[j]].Vertex[0];
				v.Pos.Y = vertices[triangles[i].VertexIndices[j]].Vertex[1];
				v.Pos.Z = vertices[triangles[i].VertexIndices[j]].Vertex[2];

				//look, if we already have this vertex in our vertex array
				s32 index = -1;
				for (u32 iV = 0; iV < Vertices.size(); ++iV)
				{
					if (v == Vertices[iV])
					{
						index = (s32)iV;
						break;
					}
				}
				if (index == -1)
				{
					s32 boneid = vertices[triangles[i].VertexIndices[j]].BoneID;
					v.BoneId = (u16)boneid;
					Vertices.push_back(v);
					index = Vertices.size() - 1;
				}
				Indices.push_back(index);
	

			}
		}

		//create groups
		s32 iIndex = 0;
		for (i=0; i<(s32)Groups.size(); ++i) 
		{ 
			CSkinRes::SGroup& grp = Groups[i]; 

			if (grp.MaterialIdx >= Buffers.size()) 
				grp.MaterialIdx = 0; 
			/*
			core::array<u16>& indices = Buffers[grp.MaterialIdx].Indices;

			for (u32 k=0; k<grp.VertexIds.size(); ++k)
				for (u32 l=0; l<3; ++l)
					indices.push_back(Indices[++iIndex]);
			*/
			//在这里，用IndexStart (index在Skin Index Buffer中的起始位置）与IndexCount（索引个数）来索引Index缓冲区
			CSkinRes::SBufferInfo &meshBuffer = Buffers[grp.MaterialIdx];
			meshBuffer.IndexStart = iIndex ;
			meshBuffer.IndexCount = grp.VertexIds.size() * 3;
			iIndex += meshBuffer.IndexCount;
		}

		// calculate bounding box
		if (!Vertices.empty())
			m_BoundingBox.reset(Vertices[0].Pos);

		for (i=0; i<(s32)Vertices.size(); ++i)
			m_BoundingBox.addInternalPoint(Vertices[i].Pos);

		// inverse translate and rotate all vertices for making animation easier
	
		if (m_bHasAnimation)
		{
			for (i = 0; i < (s32)Vertices.size(); i++)
			{
				CSkinRes::SSkinVertex &v = Vertices[i];
				if (v.BoneId == (u16)-1) continue;
				SJointImportInfo &info = arrayJointInfo[v.BoneId];
				info.AbsoluteTransformation.inverseTranslateVect(v.Pos);
				info.AbsoluteTransformation.inverseRotateVect(v.Pos);
				info.AbsoluteTransformation.inverseRotateVect(v.Normal);
			}
		}
		m_pSkin = new CSkin;
		m_pSkin->SetSkinRes(pNewSkin);
		m_pSkeleton = new CSkeleton;
		array<SJointInfo> &arrayInfo = m_pSkeleton->GetJointInfoVector();
		for (int i = 0; i < (s32)arrayJointInfo.size(); i++)
		{
			arrayInfo.push_back(SJointInfo());
			SJointInfo &info = arrayInfo.getLast();
			info.AbsoluteTransformation = arrayJointInfo[i].AbsoluteTransformation;
			info.RelativeTransformation = arrayJointInfo[i].RelativeTransformation;
			info.wParentIndex = arrayJointInfo[i].Parent;			
		}
		delete [] buffer;
		delete [] vertices;
		delete [] triangles;
	
		//SetAction(0,pAction,true);
		
		//收工

		return true;
	
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CSkeletonAni::animateJoint(s32 frame)
	{
		f32 fTimeNow = f32(frame);
		if (!m_pAction_) return;
		
	
		
		if (fTimeNow >= m_fTransitionTimeEnd || !m_bTransitionEnable)
		{
			m_bTransiting = false;
		}
		s32 iframeAct = frame - m_iframeActStart;
		f32 fframeAct;

		fframeAct = f32(iframeAct - m_iframeActStart);

		bool bActReady = false;
		s32 iFrame0,iFrame1;
		f32 fScale;
		bActReady = m_pAction_->GetKeyframeIndex(fframeAct,iFrame0,iFrame1,fScale,m_bLoop);
		if (!bActReady) return ;
		
		//下面有一段代码是用来两个不同的动作进行过渡的,如果处于过度，那么的骨骼位置由上一帧和本帧决定，否则仅由上一帧决定！

		float fTransScale = (fTimeNow - m_fTransitionTimeLast) / (m_fTransitionTimeEnd - m_fTransitionTimeLast);
		m_fTransitionTimeLast = fTimeNow;
		for (s32 i = 0; i < (s32)m_pSkeleton->m_vecJointInfo.size(); i++)
		{
			vector3df Trans;
			quaternion Rotate;
			SJointInfo &info = m_pSkeleton->m_vecJointInfo[i];
			CAction_::SKeyframe *pKeyframe0 = m_pAction_->GetKeyframe(iFrame0);
			CAction_::SKeyframe *pKeyframe1 = m_pAction_->GetKeyframe(iFrame1);
			Trans = pKeyframe0[i].m_vTrans + (pKeyframe1[i].m_vTrans - pKeyframe0[i].m_vTrans) * fScale;
			Rotate.slerp(pKeyframe0[i].m_qRotate,pKeyframe1[i].m_qRotate,fScale);
			//这是一段奇怪的代码，初步估计是因为坐标系的不同引起的
		//	Rotate.makeInverse();
			if (m_bTransiting)
			{
				Trans = info.Trans + (info.Trans - Trans) * fTransScale;
				Rotate.slerp(info.Rotate,Rotate,fTransScale);	

			}
			info.Rotate = Rotate;
			info.Trans = Trans;
			core::matrix4 transform;
			transform = Rotate.getMatrix();		
			transform.setTranslation(info.Trans);
			info.AbsoluteTransformation = info.RelativeTransformation * transform;
			if (info.wParentIndex != (u16)-1)
			{
				info.AbsoluteTransformation = m_pSkeleton->m_vecJointInfo[info.wParentIndex].AbsoluteTransformation * info.AbsoluteTransformation;
			}
			
		}
		
	}
	bool CSkeletonAni::Export(io::IWriteFile *pFile)
	{
		
		u32 dwChunk = 'SKLE';
		if (!m_pSkeleton) return false;
		pFile->write(&dwChunk,sizeof(u32));
		m_pSkeleton->Export(pFile);
		dwChunk = 'SKIN';
		if (!m_pSkin) return false;
		pFile->write(&dwChunk,sizeof(u32));
		m_pSkin->m_pSkinRes->Export(pFile);
		dwChunk = 'ACTS';
		if (m_pAction_)
		{
			pFile->write(&dwChunk,sizeof(u32));
			m_pAction_->Export(pFile);
		}
		return true;
	}
	bool CSkeletonAni::Import(io::IReadFile *pFile)
	{
		u32 dwChunk = 0;
		//if (!m_pSkeleton) return false;
		pFile->read(&dwChunk,sizeof(u32));
		if (dwChunk != 'SKLE') return false;
		if (!m_pSkeleton) m_pSkeleton = new CSkeleton;
		m_pSkeleton->Import(pFile);

		pFile->read(&dwChunk,sizeof(u32));
		if (dwChunk != 'SKIN') return false;
		CSkinRes *pSkinRes = new CSkinRes;
		pSkinRes->Import(pFile,m_pDriver);
		m_pSkin = new CSkin;
		m_pSkin->SetSkinRes(pSkinRes);

		
		pFile->read(&dwChunk,sizeof(u32));
		if (dwChunk == 'ACTS')
		{
			CAction_ *pAction_ = new CAction_;
			pAction_->Import(pFile);			
			SetAction(0,pAction_,true);
		}
		return true;
	}

	void CSkeletonAni::SetAction(s32 frame,CAction_ *pAction,bool bLoop)
	{
		//当前是否过度
		m_bLoop = bLoop;
		m_iframeActStart = frame;
		f32 fTimeNow = (f32)frame;
		if (m_pAction_  && m_bTransitionEnable)
		{
			//需要过度
			m_bTransiting = true;
			m_pAction_ = pAction;
			m_fTransitionTimeEnd = fTimeNow + fTransitionTime;			
		}
		else
		{
			m_pAction_ = pAction;
		}
		m_fTotalTime = m_pAction_->GetFrameNum() / m_pAction_->m_fFramePerSecond * 1000.0f;

	}

	void CSkeletonAni::SetSkeleton(CSkeleton *pSkeleton)
	{
		SAFE_DELETE(m_pSkeleton);
		m_pSkeleton = pSkeleton;
	}
	void CSkeletonAni::SetSkin(CSkin *pSkin)
	{
		SAFE_DELETE(m_pSkin);
		m_pSkin = pSkin;
	}

	void CSkeletonAni::TransformMesh()
	{
		//变换当前的Mesh
		
		if (!m_pSkin) return;
		core::array<SJointInfo> &vecJoint = m_pSkeleton->GetJointInfoVector();
		core::array<CSkinRes::SSkinVertex> &arrayVert = m_pSkin->m_pSkinRes->Vertices;
		array<video::S3DVertex > &arrayAniVert = m_pSkin->AnimatedVertices;
		for (s32 i = 0; i < (s32)arrayVert.size(); i++)
		{
			CSkinRes::SSkinVertex &vert = arrayVert[i]; 
			vecJoint[vert.BoneId].AbsoluteTransformation.transformVect(arrayAniVert[i].Pos,
				 arrayVert[i].Pos);
			 if (m_bNeedTransformNormal)
			 {
				 //注意，这里有个问题，应该使用逆矩阵的转秩来变换,要考虑效率了
				 vecJoint[vert.BoneId].AbsoluteTransformation.transformVect(arrayAniVert[i].Normal,
					 arrayVert[i].Normal);
			 }
		}		
	}
	IMesh* CSkeletonAni::getMesh(s32 frame, s32 , s32 , s32 )
	{		
		
		animateJoint(frame);
		TransformMesh();
		return this;
	}
	u32 CSkeletonAni::getMeshBufferCount() const
	{
		if (!m_pSkin) return 0;
		array<CSkin::CMeshBuffer> &Buffers = m_pSkin->MeshBuffer; 
		return Buffers.size();
	}



	//! returns pointer to a mesh buffer
	IMeshBuffer* CSkeletonAni::getMeshBuffer(u32 nr) const
	{
		if (nr < m_pSkin->MeshBuffer.size())
			return (IMeshBuffer*) &m_pSkin->MeshBuffer[nr];
		else
			return 0;
	}

	//! Returns pointer to a mesh buffer which fits a material
	IMeshBuffer* CSkeletonAni::getMeshBuffer( const video::SMaterial &material) const
	{
		if (!m_pSkin) return NULL;
		array<CSkin::CMeshBuffer> &Buffers = m_pSkin->MeshBuffer; 
		for (u32 i=0; i<Buffers.size(); ++i)
		{
			if (Buffers[i].m_Material == material)
				return (IMeshBuffer*) &Buffers[i];
		}
		return 0;
	}



	//! set user axis aligned bounding box
	void CSkeletonAni::setBoundingBox( const core::aabbox3df& box)
	{
		m_BoundingBox = box;
	}

	//! sets a flag of all contained materials to a new value
	void CSkeletonAni::setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newvalue)
	{
		if (!m_pSkin) return ;
		array<CSkin::CMeshBuffer> &Buffers = m_pSkin->MeshBuffer; 
		for (s32 i=0; i<(int)Buffers.size(); ++i) 
			Buffers[i].m_Material.setFlag(flag, newvalue);
	}


	//! Returns the type of the animated mesh.
	E_ANIMATED_MESH_TYPE CSkeletonAni::getMeshType() const
	{
		return EAMT_MS3D;
	}


	core::matrix4* CSkeletonAni::getMatrixOfJoint(s32 jointNumber, s32 frame)
	{
		//注意，这个函数以后需要优化
		if (!m_pSkeleton) return NULL;
		array<SJointInfo> &Joints = m_pSkeleton->GetJointInfoVector();
		
		if (jointNumber < 0 || jointNumber >= (s32)Joints.size())
			return 0;

		animateJoint(frame);

		return &Joints[jointNumber].AbsoluteTransformation;
	}


	//! Gets joint count.
	s32 CSkeletonAni::getJointCount() const
	{
		if (!m_pSkeleton) return NULL;
		array<SJointInfo> &Joints = m_pSkeleton->GetJointInfoVector();
		return Joints.size();
	}


	//! Gets the name of a joint.
	const c8* CSkeletonAni::getJointName(s32 number) const
	{
		if (!m_pSkeleton) return NULL;
		array<SJointInfo> &Joints = m_pSkeleton->GetJointInfoVector();
		if (number < 0 || number >= (s32)Joints.size())
			return 0;
		return Joints[number].strName.c_str();
	}


	//! Gets a joint number from its name
	s32 CSkeletonAni::getJointNumber(const c8* name) const
	{
		if (!m_pSkeleton) return NULL;
		array<SJointInfo> &Joints = m_pSkeleton->GetJointInfoVector();
		for (s32 i=0; i<(s32)Joints.size(); ++i)
			if (Joints[i].strName == name)
				return i;

		return -1;
	}




	CSkin::CMeshBuffer::CMeshBuffer()
	{
		m_pSkin = NULL;
		m_Indices = NULL;
		m_IndexCount = 0;
	}
	//! returns pointer to vertices 
	const void* CSkin::CMeshBuffer::getVertices() const 
	{ 
		if (m_pSkin )
		{
			return m_pSkin->AnimatedVertices.const_pointer();
		}
		return NULL;
	} 

	//! returns pointer to vertices 
	void* CSkin::CMeshBuffer::getVertices() 
	{ 
		if (m_pSkin )
		{
			return m_pSkin->AnimatedVertices.pointer();
		}
		return NULL;
	} 

	//! returns amount of vertices 
	u32 CSkin::CMeshBuffer::getVertexCount() const 
	{ 
		return m_pSkin->AnimatedVertices.size(); 
	} 

	//! returns pointer to Indices 
	const u16* CSkin::CMeshBuffer::getIndices() const 
	{ 
		return m_Indices;
	} 

	//! returns pointer to Indices 
	u16* CSkin::CMeshBuffer::getIndices() 
	{ 
		return m_Indices; 
	} 

	//! returns amount of indices 
	u32 CSkin::CMeshBuffer::getIndexCount() const 
	{ 
		return  m_IndexCount;
	} 

	//! returns an axis aligned bounding box 
	const core::aabbox3d<f32>& CSkin::CMeshBuffer::getBoundingBox() const 
	{ 
	
		return m_pSkin->BoundingBox; 
	
	} 

	//! returns an axis aligned bounding box 
	void CSkin::CMeshBuffer::setBoundingBox( const core::aabbox3df& box) 
	{ 
		if (m_pSkin)
		m_pSkin->BoundingBox = box; 
	} 

	//! returns which type of vertex data is stored.
	video::E_VERTEX_TYPE CSkin::CMeshBuffer::getVertexType() const
	{
		return video::EVT_STANDARD;
	}

	//! returns the byte size (stride, pitch) of the vertex
	u32 CSkin::CMeshBuffer::getVertexPitch() const
	{
		return sizeof ( video::S3DVertex );
	}


//namespace sklani
}
//namespace scene
}
//namespace irr
}


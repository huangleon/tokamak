#ifndef _ANIMATED_MESH_MD2X_H_
#define _ANIMATED_MESH_MD2X_H_

#include <irrlicht.h>

using irr::c8;
using irr::s32;
using irr::u32;
using irr::u16;
using irr::f32;
using irr::scene::IAnimatedMeshMD2;
using irr::scene::IMesh;
using irr::scene::IMeshBuffer;
using irr::io::IReadFile;
using irr::video::SMaterial;
using irr::video::E_VERTEX_TYPE;
using irr::video::EVT_STANDARD;
using irr::core::aabbox3d;
using irr::core::aabbox3df;
using irr::core::array;
using irr::video::E_MATERIAL_FLAG;
using irr::scene::E_ANIMATED_MESH_TYPE;
using irr::scene::EMD2_ANIMATION_TYPE;
using irr::scene::EAMT_MD2;
using irr::core::stringc;
using irr::ELOG_LEVEL;
using irr::ELL_INFORMATION;
using irr::video::S3DVertex;

class CPingPangMD2XMesh
: public IAnimatedMeshMD2
, public IMesh
, public IMeshBuffer
{
    enum { MD2_MAGIC_NUMBER = 844121161 };
    enum { MD2_VERSION		= 8         };
    enum { MD2_MAX_VERTS	= 2048      };
    enum { MD2_FRAME_SHIFT  = 0         }; // 2?

public:
	CPingPangMD2XMesh()
    : m_pTriangles( 0 )
    , m_pTexCoords( 0 )
    , m_nTriangleCount( 0 )
    , m_nVertexCount( 0 )
    {
        //m_Material.ZBuffer = 0;
        //m_Material.ZWriteEnable = false;
        //m_Material.BackfaceCulling = false;
    }

	virtual ~CPingPangMD2XMesh()
    {
        Clearup();
    }

	virtual bool loadFile(
        IReadFile* file
        );

	virtual s32 getFrameCount()
    {
        return m_arrFrames.size();
    }

	virtual IMesh* getMesh(
        s32 frame,
        s32 detailLevel=255,
        s32 startFrameLoop=-1,
        s32 endFrameLoop=-1
        );

	virtual u32 getMeshBufferCount() const
    {
        return 1;
    }

	virtual IMeshBuffer* getMeshBuffer(
        u32 nr
        ) const
    {
        return (IMeshBuffer*) this;
    }

	virtual IMeshBuffer* getMeshBuffer(
        const SMaterial &material
        ) const
    {
	    if( m_Material == material )
		    return (IMeshBuffer*) this;
	    else
		    return 0;
    }

	virtual const SMaterial& getMaterial(
        ) const
    {
        return m_Material;
    }

	virtual SMaterial& getMaterial()
    {
        return m_Material;
    }

	virtual const void* getVertices() const
    {
        return m_arrVertices.const_pointer();
    }

	virtual void* getVertices()
    {
        return m_arrVertices.pointer();
    }

	virtual E_VERTEX_TYPE getVertexType() const
    {
        return EVT_STANDARD;
    }

	virtual u32 getVertexPitch() const
    {
        return sizeof( S3DVertex );
    }

	virtual u32 getVertexCount() const
    {
        return m_arrVertices.size();
    }

	virtual const u16* getIndices() const
    {
        return m_arrIndices.const_pointer();
    }

	virtual u16* getIndices()
    {
        return m_arrIndices.pointer();
    }

	virtual u32 getIndexCount() const
    {
        return m_arrIndices.size();
    }

	virtual const aabbox3d<f32>& getBoundingBox() const
    {
        return m_BoundingBox;
    }

	virtual void setBoundingBox(
        const aabbox3df& box
        )
    {
        m_BoundingBox = box;
    }

	virtual void setMaterialFlag(
        E_MATERIAL_FLAG flag,
        bool newvalue
        )
    {
        m_Material.setFlag(flag, newvalue);
    }

	virtual E_ANIMATED_MESH_TYPE getMeshType() const
    {
        return EAMT_MD2;
    }

	virtual void getFrameLoop(
        EMD2_ANIMATION_TYPE, 
		s32& outBegin,
        s32& outEnd,
        s32& outFps
        ) const;

	virtual bool getFrameLoop(
        const c8* name, 
		s32& outBegin,
        s32& outEnd,
        s32& outFps
        ) const;

	virtual s32 getAnimationCount() const
    {
        return FrameData.size();
    }

	virtual const c8* getAnimationName(
        s32 nr
        ) const;

private:
	void updateInterpolationBuffer(
        s32 frame,
        s32 startFrame,
        s32 endFrame
        );

	virtual void calculateBoundingBox();

	array<aabbox3d<f32> > m_lstBox;
	SMaterial m_Material;

	aabbox3d<f32> m_BoundingBox;

	struct SFrameData
	{
		stringc name;
		s32 begin;
		s32 end;
		s32 fps;
	};

	array< SFrameData > FrameData;

    void log(
        const c8* text,
        const c8* hint,
        ELOG_LEVEL ll = ELL_INFORMATION
        );

    void* m_pTriangles;
    void* m_pTexCoords;
    u32 m_nTriangleCount;
    u32 m_nVertexCount;

    array<void *> m_arrFrames;
    array<u16> m_arrIndices;
    array<S3DVertex> m_arrVertices;

    void Clearup();
};

#endif //_ANIMATED_MESH_MD2X_H_


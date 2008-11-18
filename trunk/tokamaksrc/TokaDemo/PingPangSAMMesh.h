
#ifndef _PING_PANG_SAM_MESH_H_
#define _PING_PANG_SAM_MESH_H_

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

class CPingPangSAMMesh
: public IAnimatedMeshMD2
, public IMesh
, public IMeshBuffer
{
    enum { SAM_MAGIC     = 844121161 };
    enum { SAM_VERSION	 = 0         };

public:
	CPingPangSAMMesh()
        : FrameList(0)
        , FrameCount(0)
        , TriangleCount(0)
    {
    }

	virtual ~CPingPangSAMMesh()
    {
	    if( FrameList )
		    delete []FrameList;
    }

	virtual bool loadFile(
        IReadFile* file
        );

	virtual s32 getFrameCount()
    {
        return FrameCount;
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
	    if (Material == material)
		    return (IMeshBuffer*) this;
	    else
		    return 0;
    }

	virtual const SMaterial& getMaterial(
        ) const
    {
        return Material;
    }

	virtual SMaterial& getMaterial()
    {
        return Material;
    }

	virtual const void* getVertices() const
    {
        return InterpolateBuffer.const_pointer();
    }

	virtual void* getVertices()
    {
        return InterpolateBuffer.pointer();
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
        return FrameList[0].size();
    }

	virtual const u16* getIndices() const
    {
        return Indices.const_pointer();
    }

	virtual u16* getIndices()
    {
        return Indices.pointer();
    }

	virtual u32 getIndexCount() const
    {
        return Indices.size();
    }

	virtual const aabbox3d<f32>& getBoundingBox() const
    {
        return BoundingBox;
    }

	virtual void setBoundingBox(
        const aabbox3df& box
        )
    {
        BoundingBox = box;
    }

	virtual void setMaterialFlag(
        E_MATERIAL_FLAG flag,
        bool newvalue
        )
    {
        Material.setFlag(flag, newvalue);
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

	array<u16> Indices;
	array<S3DVertex> *FrameList;
	array<aabbox3d<f32> > BoxList;
	u32 FrameCount;
	s32 TriangleCount;
	SMaterial Material;

	array<S3DVertex> InterpolateBuffer;
	aabbox3d<f32> BoundingBox;

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
};

#endif //_PING_PANG_SAM_MESH_H_

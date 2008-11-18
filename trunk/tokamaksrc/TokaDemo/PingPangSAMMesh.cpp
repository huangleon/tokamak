
#include "include.h"
#include "PingPangSAMMesh.h"

using irr::u8;
using irr::s16;
using irr::core::if_c_a_else_b;
using irr::core::s32_min;
using irr::core::vector3df;
using irr::ELL_WARNING;
using irr::ELL_ERROR;
using irr::video::SColor;
using irr::scene::EMAT_COUNT;

#ifdef _MSC_VER
#pragma pack( push, packing )
#pragma pack( 1 )
#define PACK_STRUCT
#elif defined( __GNUC__ )
#define PACK_STRUCT	__attribute__((packed))
#else
#error compiler not supported
#endif

struct TSamTexCoord
{
    float u;
    float v;
} PACK_STRUCT;

struct TSamVertex
{
	float x;
	float y;
	float z;
} PACK_STRUCT;

struct TSamFrame
{
	TSamVertex	Vertices[1];
} PACK_STRUCT;

struct TSamFace
{
	u16 nV1;
	u16 nV2;
	u16 nV3;

	u16 nT1;
	u16 nT2;
	u16 nT3;
} PACK_STRUCT;

struct TSamFileHeader
{
	u32 nMagic;           // magic number for SAM, 844121161
	u32 nVersion;         // 0
	
	u32 nVertex;          // count of vertices
	
	u32 nFace;            // count of triangle face
	u32 nTexCoord;        // count of tex coords
	u32 nFrame;           // count of frame
	u32 nFrameSize;       // frame size in bytes
	
	u32 nOffsetFaces;     // offset of face data
	u32 nOffsetTexCoords; // offset of tex coords
	
	u32 nOffsetFrames;    // offset of the frames
	
	u32 nOffsetFileEnd;   // offset of the file end
} PACK_STRUCT;

// Default alignment
#ifdef _MSC_VER
#pragma pack( pop, packing )
#endif

#undef PACK_STRUCT

IMesh* CPingPangSAMMesh::getMesh(
    s32 frame,
    s32 detailLevel,
    s32 startFrameLoop,
    s32 endFrameLoop
    )
{
	if( (u32)frame > FrameCount )
		frame %= FrameCount;

	if( startFrameLoop == -1 && endFrameLoop == -1 )
	{
		startFrameLoop = 0;
		endFrameLoop = FrameCount;
	}

	updateInterpolationBuffer(
        frame,
        startFrameLoop,
        endFrameLoop
        );

	return this;
}

// updates the interpolation buffer
void CPingPangSAMMesh::updateInterpolationBuffer(
    s32 frame,
    s32 startFrameLoop,
    s32 endFrameLoop
    )
{
	u32 firstFrame, secondFrame;
	f32 div = 0.0f;

	if( endFrameLoop == startFrameLoop )
	{
		firstFrame = frame;
		secondFrame = frame;
		div = 0.0f;
	}
	else
	{
		// key frames
		u32 s = startFrameLoop;
		u32 e = endFrameLoop;

		firstFrame = frame;
		secondFrame = if_c_a_else_b(
            firstFrame + 1 > e,
            s,
            firstFrame + 1
            );

		firstFrame = s32_min(
            FrameCount - 1,
            firstFrame
            );
		secondFrame = s32_min(
            FrameCount - 1,
            secondFrame
            );

        if( secondFrame != firstFrame )
            div = (float)(secondFrame - frame)/(float)(secondFrame - firstFrame);
	}

    firstFrame = frame;
    secondFrame = frame;

    //std::cout << frame << ", "
    //    << firstFrame << ", "
    //    << secondFrame << std::endl;

    S3DVertex* target = &InterpolateBuffer[0];
	S3DVertex* first = FrameList[firstFrame].pointer();
	S3DVertex* second = FrameList[secondFrame].pointer();

	s32 count = FrameList[firstFrame].size();

	// interpolate both frames
	for( s32 i = 0; i < count; ++i )
	{
		target->Pos = ( second->Pos - first->Pos ) * div
            + first->Pos;
		target->Normal = ( second->Normal - first->Normal ) * div 
            + first->Normal;

		++target;
		++first;
		++second;
	}

	//update bounding box
	BoundingBox = BoxList[secondFrame].getInterpolated(
        BoxList[firstFrame],
        div
        );
}

// Load a SAM file
bool CPingPangSAMMesh::loadFile(
    IReadFile* file
    )
{
	if (!file)
		return false;

    std::cout << "Load SAM file: " << file->getFileName()
        << std::endl;

	TSamFileHeader header;
	file->read( &header, sizeof(TSamFileHeader) );

	if( header.nMagic != SAM_MAGIC ||
        header.nVersion != SAM_VERSION )
	{
		log(
            "Wrong file header when loading %s.",
            file->getFileName(),
            ELL_WARNING
            );
		return false;
	}

	// read Triangles
	file->seek( header.nOffsetFaces, false );
	TSamFace *triangles = new TSamFace[header.nFace];
	if( !file->read(
        triangles,
        header.nFace * sizeof( TSamFace )
        ) )
	{
		log(
            "Error when reading triangles of %s.",
            file->getFileName(),
            ELL_ERROR
            );
		return false;
	}

	// read TextureCoords
	file->seek( header.nOffsetTexCoords, false );
	TSamTexCoord* textureCoords =
        new TSamTexCoord[header.nTexCoord];
	if( !file->read(
        textureCoords,
        sizeof(TSamTexCoord) * header.nTexCoord
        ) )
	{
		log(
            "Error when reading TextureCoords of %s.",
            file->getFileName(),
            ELL_ERROR
            );
		return false;
	}

    /*// path for the bug of MD2 exporter we use
	for( i = 0 ; i < header.nFace ; ++i )
	{
        u32 tmp = triangles[i].vertexIndices[0];
		triangles[i].vertexIndices[0] = triangles[i].vertexIndices[2];
		triangles[i].vertexIndices[2] = tmp;

        tmp = triangles[i].textureIndices[0];
		triangles[i].textureIndices[0] = triangles[i].textureIndices[2];
		triangles[i].textureIndices[2] = tmp;
	}*/

	// read Vertices
	u8 *buffer =  new u8[((header.nFrameSize+4095)/4096)*4096];
	TSamFrame* frame = (TSamFrame*)buffer;

	array<vector3df>* vertices = new array<vector3df>[header.nFrame];
	array<vector3df>* normals = new array<vector3df>[header.nFrame];

	// create Memory for indices and frames
	TriangleCount = header.nFace;
	if (FrameList)
		delete []FrameList;
	FrameCount = header.nFrame;
	FrameList = new array<S3DVertex>[FrameCount];
    if( !FrameList )
    {
		log(
            "Out of memory when loading %s.",
            file->getFileName(),
            ELL_WARNING
            );
		return false;
    }
	u32 i;
	for( i=0; i < FrameCount; ++i )
		FrameList[i].reallocate( header.nVertex );

	file->seek( header.nOffsetFrames, false );

	for( i = 0; i < header.nFrame; ++i )
	{
		// read vertices
		file->read( frame, header.nFrameSize );

		// add vertices
		vertices[i].reallocate( header.nVertex );
		for( u32 j = 0; j < header.nVertex; ++j )
		{
			vector3df v;
			v.X = frame->Vertices[j].x;
			v.Z = frame->Vertices[j].y;
			v.Y = frame->Vertices[j].z;
			vertices[i].push_back(v);

            // Ignore normal data
            /*
			v.X = 0;
			v.Y = 0;
			v.Z = 0;
			normals[i].push_back(v);
            */
		}

		// calculate bounding boxes
		if( header.nVertex )
		{
			aabbox3d<f32> box;
			box.reset(vertices[i][0]);

			for( u32 j=1; j<header.nVertex; ++j )
				box.addInternalPoint( vertices[i][j] );

			BoxList.push_back(box);
		}
	}

	S3DVertex vtx;
	vtx.Color = SColor(255,255,255,255);

	for( u32 f = 0; f < header.nFrame; ++f )
	{
		array<vector3df>& vert = vertices[f];

		for( u32 t = 0; t < header.nFace ; ++t )
		{
			vtx.Normal = vector3df(0, 0, 0);

            vtx.Pos = vert[triangles[t].nV1];
			vtx.TCoords.X = textureCoords[triangles[t].nT1].u;
			vtx.TCoords.Y = textureCoords[triangles[t].nT1].v;
			FrameList[f].push_back(vtx);

			vtx.Pos = vert[triangles[t].nV2];
			vtx.TCoords.X = textureCoords[triangles[t].nT2].u;
			vtx.TCoords.Y = textureCoords[triangles[t].nT2].v;
			FrameList[f].push_back(vtx);

			vtx.Pos = vert[triangles[t].nV3];
			vtx.TCoords.X = textureCoords[triangles[t].nT3].u;
			vtx.TCoords.Y = textureCoords[triangles[t].nT3].v;
			FrameList[f].push_back(vtx);
		}
	}

	// create indices
	Indices.reallocate( header.nVertex );
	s16 count = TriangleCount*3;
	for( s16 n = 0; n < count; n += 3 )
	{
		Indices.push_back( n+0 );
		Indices.push_back( n+1 );
		Indices.push_back( n+2 );
	}

	// reallocate interpolate buffer
	if( header.nFrame )
	{
		u32 currCount = FrameList[0].size();
		InterpolateBuffer.set_used(currCount);

		for( i = 0; i < currCount; ++i )
		{
			InterpolateBuffer[i].TCoords = FrameList[0].pointer()[i].TCoords;
			InterpolateBuffer[i].Color = vtx.Color;
		}
	}

	// clean up
	delete []normals;
	delete []vertices;
	delete []triangles;
	delete []textureCoords;
    delete []buffer;

	calculateBoundingBox();
	return true;
}

//! calculates the bounding box
void CPingPangSAMMesh::calculateBoundingBox()
{
	BoundingBox.reset(0,0,0);

	if ( !FrameCount )
        return;

    u32 defaultFrame = 1;
	if( defaultFrame>=FrameCount )
		defaultFrame = 0;

	for( u32 j =0; j < FrameList[defaultFrame].size(); ++j )
		BoundingBox.addInternalPoint(
            FrameList[defaultFrame].pointer()[j].Pos
            );
}

//! Returns frame loop data for a special MD2 animation type.
void CPingPangSAMMesh::getFrameLoop(
    EMD2_ANIMATION_TYPE l,
    s32& outBegin,
    s32& outEnd,
    s32& outFPS
    ) const
{
    outBegin = 0;
    outEnd = FrameCount - 1;
    outFPS = 30;
}

//! Returns frame loop data for a special MD2 animation type.
bool CPingPangSAMMesh::getFrameLoop(
    const c8* name,
	s32& outBegin,
    s32&outEnd,
    s32& outFPS
    ) const
{
    outBegin = 0;
    outEnd = FrameCount - 1;
    outFPS = 30;

	return true;
}

//! Returns name of md2 animation.
const c8* CPingPangSAMMesh::getAnimationName(
    s32 nr
    ) const
{
    static const c8 dummy[] = "SAM";
	return dummy;
}

void CPingPangSAMMesh::log(
    const c8* text,
    const c8* hint,
    ELOG_LEVEL ll
    )
{
}


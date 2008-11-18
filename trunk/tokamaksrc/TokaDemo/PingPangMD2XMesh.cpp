#include "include.h"
#include "PingPangMD2XMesh.h"

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
#	pragma pack( push, packing )
#	pragma pack( 1 )
#	define PACK_STRUCT
#elif defined( __GNUC__ )
#	define PACK_STRUCT	__attribute__((packed))
#else
#	error compiler not supported
#endif

#define MFS ( CPingPangMD2XMesh::MD2_FRAME_SHIFT )
#define MD2_FRAME_SHIFT_RECIPROCAL 1.f/( 1 << MFS );

struct SMD2Header
{
	s32 magic;
	s32 version;
	s32 skinWidth;
	s32 skinHeight;
	s32 frameSize;
	s32 numSkins;
	s32 numVertices;
	s32 numTexcoords;
	s32 numTriangles;
	s32 numGlCommands;
	s32 numFrames;
	s32 offsetSkins;
	s32 offsetTexcoords;
	s32 offsetTriangles;
	s32 offsetFrames;
	s32 offsetGlCommands;
	s32 offsetEnd;
} PACK_STRUCT;

struct SMD2Vertex
{
	u8 vertex[3];
	u8 lightNormalIndex;
} PACK_STRUCT;

struct SMD2Frame
{
	f32	scale[3];
	f32	translate[3];
	c8	name[16];
	SMD2Vertex vertices[1];
} PACK_STRUCT;

struct SMD2Triangle
{
	u16 vertexIndices[3];
	u16 textureIndices[3];
} PACK_STRUCT;

struct SMD2TextureCoordinate
{
	s16 s;
	s16 t;
} PACK_STRUCT;

struct SMD2GLCommand
{
	f32 s, t;
	s32 vertexIndex;
} PACK_STRUCT;

// Default alignment
#ifdef _MSC_VER
#	pragma pack( pop, packing )
#endif

#undef PACK_STRUCT

struct SMD2AnimationType
{
	s32 begin;
	s32 end;
	s32 fps;
};

static const
SMD2AnimationType MD2AnimationTypeList[21] =
{
    {   0,  80, 30 },   // STAND
};

IMesh* CPingPangMD2XMesh::getMesh(
    s32 frame,
    s32 detailLevel,
    s32 startFrameLoop,
    s32 endFrameLoop
    )
{
	if( frame > ( getFrameCount() << MD2_FRAME_SHIFT ) )
		frame = ( frame % ( getFrameCount() << MD2_FRAME_SHIFT ) );

	if( startFrameLoop == -1 && endFrameLoop == -1 )
	{
		startFrameLoop = 0;
		endFrameLoop = getFrameCount() << MD2_FRAME_SHIFT;
	}

	updateInterpolationBuffer(
        frame,
        startFrameLoop,
        endFrameLoop
        );

	return this;
}

// updates the interpolation buffer
void CPingPangMD2XMesh::updateInterpolationBuffer(
    s32 frame,
    s32 startFrameLoop,
    s32 endFrameLoop
    )
{
	u32 firstFrame, secondFrame;
	f32 div;

	if( endFrameLoop == startFrameLoop )
	{
		firstFrame = frame >> MD2_FRAME_SHIFT;
		secondFrame = frame >> MD2_FRAME_SHIFT;
		div = 1.0f;
	}
	else
	{
		// key frames
		u32 s = startFrameLoop >> MD2_FRAME_SHIFT;
		u32 e = endFrameLoop >> MD2_FRAME_SHIFT;

		firstFrame = frame >> MD2_FRAME_SHIFT;
		secondFrame = if_c_a_else_b(
            firstFrame + 1 > e,
            s,
            firstFrame + 1
            );

		firstFrame = s32_min(
            getFrameCount() - 1,
            firstFrame
            );
		secondFrame = s32_min(
            getFrameCount() - 1,
            secondFrame
            );

		//div = (frame % (1<<MD2_FRAME_SHIFT)) / (f32)(1<<MD2_FRAME_SHIFT);
		frame &= ( 1 << MD2_FRAME_SHIFT ) - 1;
		div = frame * MD2_FRAME_SHIFT_RECIPROCAL;
	}

    //std::cout << frame << ", "
    //    << firstFrame << ", "
    //    << secondFrame << std::endl;

    SMD2Frame* frmFirst = (SMD2Frame*)m_arrFrames[firstFrame];
    SMD2Frame* frmSecond = (SMD2Frame*)m_arrFrames[secondFrame];
    S3DVertex* vertTarget = &m_arrVertices[0];
	for( u32 t = 0; t < m_nTriangleCount; t++ )
	{
        SMD2Triangle& tri = ( ( SMD2Triangle* )m_pTriangles )[t];
		for( u32 n = 0; n < 3; n++ )
		{
            vector3df posFirst;
            vector3df posSecond;
            u16 vertexindex = tri.vertexIndices[n];

            posFirst.X = frmFirst->translate[0] +
                frmFirst->vertices[vertexindex].vertex[0] * frmFirst->scale[0];
		    posFirst.Z = frmFirst->translate[1] +
                frmFirst->vertices[vertexindex].vertex[1] * frmFirst->scale[1];
		    posFirst.Y = frmFirst->translate[2] +
                frmFirst->vertices[vertexindex].vertex[2] * frmFirst->scale[2];

            if( frmFirst != frmSecond )
            {
                posSecond.X = frmSecond->translate[0] +
                    frmSecond->vertices[vertexindex].vertex[0] * frmSecond->scale[0];
		        posSecond.Z = frmSecond->translate[1] +
                    frmSecond->vertices[vertexindex].vertex[1] * frmSecond->scale[1];
		        posSecond.Y = frmSecond->translate[2] +
                    frmSecond->vertices[vertexindex].vertex[2] * frmSecond->scale[2];

                vertTarget->Pos = ( posSecond - posFirst ) * div
                    + posFirst;
            }
            else
            {
                vertTarget->Pos = posFirst;
            }

            vertTarget++;
		}
	}

	// update bounding box
	m_BoundingBox = m_lstBox[secondFrame].getInterpolated(
        m_lstBox[firstFrame],
        div
        );
}

void CPingPangMD2XMesh::Clearup()
{
    if( m_pTriangles )
        delete [](u8*)m_pTriangles;
    if( m_pTexCoords )
        delete [](u8*)m_pTexCoords;

    for( u32 i = 0; i < m_arrFrames.size(); i++ )
        delete [](u8*)(m_arrFrames[i]);

    m_arrFrames.clear();
    m_arrIndices.clear();
    m_arrVertices.clear();
}

//! loads an md2 file
bool CPingPangMD2XMesh::loadFile(
    IReadFile* file
    )
{
    std::cout << "Loading MD2X file: " << file->getFileName()
        << std::endl;

    if (!file)
		return false;

    Clearup();

	u32 i;
	SMD2Header header;
    SMD2Triangle *triangles = 0;
    SMD2TextureCoordinate* textureCoords = 0;

    // read header
	file->read( &header, sizeof( SMD2Header ) );
	if( header.magic != MD2_MAGIC_NUMBER ||
        header.version != MD2_VERSION )
	{
		log( "MD2 Loader: Wrong file header",
            file->getFileName(), ELL_WARNING
            );
		return false;
	}

    m_nTriangleCount = header.numTriangles;
    m_nVertexCount = header.numVertices;
    m_arrFrames.reallocate( header.numFrames );
    m_arrIndices.reallocate( m_nTriangleCount*3 );
    m_arrVertices.reallocate( m_nTriangleCount*3 );

	// read Triangles
	file->seek( header.offsetTriangles, false );
    m_pTriangles = new SMD2Triangle[header.numTriangles];
	triangles = ( SMD2Triangle * )m_pTriangles;
	if( !file->read( triangles,
        header.numTriangles * sizeof( SMD2Triangle )
        ) )
	{
		log( "MD2 Loader: Error reading triangles.",
            file->getFileName(), ELL_ERROR
            );
		return false;
	}

	// read TextureCoords
	file->seek( header.offsetTexcoords, false );
    m_pTexCoords = new SMD2TextureCoordinate[header.numTexcoords];
	textureCoords = ( SMD2TextureCoordinate* )m_pTexCoords;
	if( !file->read( textureCoords,
        sizeof(SMD2TextureCoordinate) * header.numTexcoords
        ) )
	{
		log( "MD2 Loader: Error reading TextureCoords.",
            file->getFileName(), ELL_ERROR
            );
		return false;
	}

#ifdef MODEL_THEME_0_
    // path for the bug of MD2 exporter we use
	for( i = 0 ; i < header.numTriangles ; ++i )
	{
        u32 tmp = triangles[i].vertexIndices[0];
		triangles[i].vertexIndices[0] = triangles[i].vertexIndices[2];
		triangles[i].vertexIndices[2] = tmp;

        tmp = triangles[i].textureIndices[0];
		triangles[i].textureIndices[0] = triangles[i].textureIndices[2];
		triangles[i].textureIndices[2] = tmp;
	}
#endif

    // read frames
	file->seek( header.offsetFrames, false );
	array<vector3df> positions;
    positions.reallocate( header.numVertices );
    m_lstBox.reallocate( header.numFrames );
	for( i = 0; i < (u32)header.numFrames; ++i )
	{
	    u8* buffer = new u8[header.frameSize];
	    SMD2Frame* frame = ( SMD2Frame* )buffer;

		// read vertices
		file->read( frame, header.frameSize );

		// store frame data
		SFrameData fdata;
		fdata.begin = i;
		fdata.end = i;
		fdata.fps = 7;

		if( frame->name[0] )
		{
			for( s32 s = 0; frame->name[s]!=0 && ( frame->name[s] < '0' ||
				frame->name[s] > '9' ); ++s )
				fdata.name += frame->name[s];

			if( !FrameData.empty() && FrameData[FrameData.size()-1].name == fdata.name )
				++FrameData[FrameData.size()-1].end;
			else
				FrameData.push_back( fdata );
		}

        positions.set_used( 0 );
		for( u32 j = 0; j < (u32)header.numVertices; ++j )
		{
			vector3df v;
			v.X = frame->vertices[j].vertex[0] * frame->scale[0] + frame->translate[0];
			v.Z = frame->vertices[j].vertex[1] * frame->scale[1] + frame->translate[1];
			v.Y = frame->vertices[j].vertex[2] * frame->scale[2] + frame->translate[2];

            positions.push_back( v );
		}

		// calculate bounding boxes
		aabbox3d<f32> box;
		box.reset( positions[0] );

		for( s32 j = 1; j < header.numVertices; ++j )
			box.addInternalPoint( positions[j] );

		m_lstBox.push_back( box );

        m_arrFrames.push_back( frame );
	}

    // prepare the initial tex coords
	S3DVertex vtx;
	vtx.Color = SColor( 255,255,255,255 );
	f32 dmaxs = 1.0f/( header.skinWidth );
	f32 dmaxt = 1.0f/( header.skinHeight );
    m_arrVertices.set_used( 0 );
	for( u32 t = 0; t < (u32)header.numTriangles; t++ )
	{
		for( u32 n = 0; n < 3; n++ )
		{
            s16 tcs = textureCoords[triangles[t].textureIndices[n]].s;
            s16 tct = textureCoords[triangles[t].textureIndices[n]].t;
			vtx.TCoords.X = ( tcs + 0.5f ) * dmaxs;
			vtx.TCoords.Y = ( tct + 0.5f ) * dmaxt;

			
            // Patch for the bug of the exporter
			
            vtx.TCoords.X *= 2.0f;
            vtx.TCoords.Y *= 2.0f;
			

            m_arrVertices.push_back( vtx );
		}
	}

	// create indices
    m_arrIndices.set_used( 0 );
	for( i = 0; i < (u32)header.numTriangles * 3; i+=3 )
	{
		m_arrIndices.push_back( i+0 );
		m_arrIndices.push_back( i+1 );
		m_arrIndices.push_back( i+2 );
	}

    calculateBoundingBox();
	return true;
}

//! calculates the bounding box
void CPingPangMD2XMesh::calculateBoundingBox()
{
	m_BoundingBox.reset(0,0,0);

	if ( !getFrameCount() )
        return;

    s32 defaultFrame = 1;
	if( defaultFrame >= getFrameCount() )
		defaultFrame = 0;

    updateInterpolationBuffer( 0, 0, 0 );
}

//! Returns frame loop data for a special MD2 animation type.
void CPingPangMD2XMesh::getFrameLoop(
    EMD2_ANIMATION_TYPE l,
    s32& outBegin,
    s32& outEnd,
    s32& outFPS
    ) const
{
	if( l < 0 || l >= EMAT_COUNT )
		return;

	outBegin = MD2AnimationTypeList[l].begin << MD2_FRAME_SHIFT;
	outEnd = MD2AnimationTypeList[l].end << MD2_FRAME_SHIFT;

	// correct to anim between last->first frame
	outEnd += MD2_FRAME_SHIFT == 0 ?
        1 : ( 1 << MD2_FRAME_SHIFT ) - 1;
	outFPS = MD2AnimationTypeList[l].fps << MD2_FRAME_SHIFT;
}

//! Returns frame loop data for a special MD2 animation type.
bool CPingPangMD2XMesh::getFrameLoop(
    const c8* name,
	s32& outBegin,
    s32&outEnd,
    s32& outFPS
    ) const
{
	for(s32 i = 0; i < ( s32 )FrameData.size(); ++i )
    {
		if( FrameData[i].name == name )
		{
			outBegin = FrameData[i].begin << MD2_FRAME_SHIFT;
			outEnd = FrameData[i].end << MD2_FRAME_SHIFT;
			outEnd += MD2_FRAME_SHIFT == 0 ?
                1 : ( 1 << MD2_FRAME_SHIFT ) - 1;
			outFPS = FrameData[i].fps << MD2_FRAME_SHIFT;
			return true;
		}
    }

	return false;
}

//! Returns name of md2 animation.
const c8* CPingPangMD2XMesh::getAnimationName(
    s32 nr
    ) const
{
	if( nr < 0 || nr >= ( s32 )FrameData.size() )
		return 0;

	return FrameData[nr].name.c_str();
}

void CPingPangMD2XMesh::log(
    const c8* text,
    const c8* hint,
    ELOG_LEVEL ll
    )
{
}

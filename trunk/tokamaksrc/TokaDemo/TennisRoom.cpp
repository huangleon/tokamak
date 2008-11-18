
/*-----------------------------------------------------------------------------
 *
 *  This file is part of "Tennis game", which is based on Irrlicht Engine.
 *
 *  Revise History:
 *    Date          Author           Comment
 *    2008-08-10    Hu, weixiong     Initial version.
 *    2008-08-16    Hu, weixiong     Added texture.
 *
 *  Copyright (c) 2007 Intel Corporation.
 *
 *-----------------------------------------------------------------------------
 */

#include "TennisRoom.h"
#include "TennisTable.h"
#include "TennisCfg.h"
//#include "TennisPhysics.h"

using irr::core::vector3df;
using irr::video::SColor;
using irr::video::EMF_LIGHTING;

#define RENDER_SCENE_MODEL 0

S3DVertex CTennisRoom::g_vbFence[8] =
{
    // inside
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_TABLE) * 2.5f,
        0,
        GetCfgVarFloat(MIN_Z_TABLE) * 2.5f,
        0, 0, 0,
        0,
        0, 1
        ),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_TABLE) * 2.5f,
        0,
        GetCfgVarFloat(MAX_Z_TABLE) * 2.5f,
        0, 0, 0,
        0,
        0, 1
        ),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_TABLE) * 2.5f,
        0,
        GetCfgVarFloat(MAX_Z_TABLE) * 2.5f,
        0, 0, 0,
        0,
        0, 1
        ),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_TABLE) * 2.5f,
        0,
        GetCfgVarFloat(MIN_Z_TABLE) * 2.5f,
        0, 0, 0,
        0,
        0, 1
        ),
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_TABLE) * 2.5f,
        GetCfgVarFloat(MAX_Y_TABLE) * 0.8f,
        GetCfgVarFloat(MIN_Z_TABLE) * 2.5f,
        0, 0, 0,
        0,
        0, 1
        ),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_TABLE) * 2.5f,
        GetCfgVarFloat(MAX_Y_TABLE) * 0.8f,
        GetCfgVarFloat(MAX_Z_TABLE) * 2.5f,
        0, 0, 0,
        0,
        0, 1
        ),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_TABLE) * 2.5f,
        GetCfgVarFloat(MAX_Y_TABLE) * 0.8f,
        GetCfgVarFloat(MAX_Z_TABLE) * 2.5f,
        0, 0, 0,
        0,
        0, 1
        ),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_TABLE) * 2.5f,
        GetCfgVarFloat(MAX_Y_TABLE) * 0.8f,
        GetCfgVarFloat(MIN_Z_TABLE) * 2.5f,
        0, 0, 0,
        0,
        0, 1
        ),
};

S3DVertex CTennisRoom::g_vbRoom[8] =
{
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        -1, -1, -1,
        SColor(255,255,127,127),
        0, 1),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        -1, 1, -1,
        SColor(255,63,63,63),
        1, 1),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        1, 1, -1,
        SColor(255,63,63,63),
        1, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        1, -1, -1,
        SColor(255,255,127,127),
        0, 0),
    S3DVertex( // 4
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        -1, -1, 1,
        SColor(255,255,127,127),
        0, 0),
    S3DVertex( // 5
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        -1, 1, 1,
        SColor(255,63,63,63),
        0, 0),
    S3DVertex( // 6
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        1, 1, 1,
        SColor(255,63,63,63),
        0, 0),
    S3DVertex( // 7
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        1, -1, 1,
        SColor(255,255,127,127),
        0, 0)
};

S3DVertex CTennisRoom::g_vbRoom2[24] =
{
	// B
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        -1, -1, -1,
        SColor(255,192,192,192),
        //SColor(255,255,32,32),
        //0, 60
        0, 1
        ),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        -1, 1, -1,
        SColor(255,192,192,192),
        //SColor(255,128,0,0),
        0, 0
        ),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        1, 1, -1,
        SColor(255,192,192,192),
        //SColor(255,128,0,0),
        //40, 0
        1, 0
        ),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        1, -1, -1,
        SColor(255,192,192,192),
        //SColor(255,255,32,32),
        //40, 60
        1, 1
        ),

	// T
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM) * 3,
        -1, -1, -1,
        SColor(255,127,127,127),
        0, 1),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM) * 3,
        -1, 1, -1,
        SColor(255,127,127,127),
        1, 1),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM) * 3,
        1, 1, -1,
        SColor(255,127,127,127),
        1, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM) * 3,
        1, -1, -1,
        SColor(255,127,127,127),
        0, 0),

	// L
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        -1, -1, -1,
        SColor(255,200,200,200),
        0, 0),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM) * 3,
        -1, 1, -1,
        SColor(255,200,200,200),
        0, 0),
    S3DVertex( // 2
        GetCfgVarFloat(MIN_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM) * 3,
        1, 1, -1,
        SColor(255,200,200,200),
        0, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        1, -1, -1,
        SColor(255,200,200,200),
        0, 0),

	// R
    S3DVertex( // 0
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        -1, -1, -1,
        SColor(255,200,200,200),
        0, 0),
    S3DVertex( // 1
        GetCfgVarFloat(MAX_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM) * 3,
        -1, 1, -1,
        SColor(255,200,200,200),
        0, 0),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM) * 3,
        1, 1, -1,
        SColor(255,200,200,200),
        0, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        1, -1, -1,
        SColor(255,200,200,200),
        0, 0),

	// F
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        -1, -1, -1,
        SColor(255,192,192,192),
        0, 0),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM) * 3,
        -1, 1, -1,
        SColor(255,192,192,192),
        0, 0),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM) * 3,
        1, 1, -1,
        SColor(255,192,192,192),
        0, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MAX_Z_ROOM),
        1, -1, -1,
        SColor(255,192,192,192),
        0, 0),

	// B
    S3DVertex( // 0
        GetCfgVarFloat(MAX_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        -1, -1, -1,
        SColor(255,192,192,192),
        0, 0),
    S3DVertex( // 1
        GetCfgVarFloat(MAX_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM) * 3,
        -1, 1, -1,
        SColor(255,192,192,192),
        0, 0),
    S3DVertex( // 2
        GetCfgVarFloat(MIN_X_ROOM) * 3,
        GetCfgVarFloat(MAX_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM) * 3,
        1, 1, -1,
        SColor(255,192,192,192),
        0, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MIN_X_ROOM),
        GetCfgVarFloat(MIN_Y_ROOM),
        GetCfgVarFloat(MIN_Z_ROOM),
        1, -1, -1,
        SColor(255,192,192,192),
        0, 0),
};

static const vector3df g_PlanesRoom[][2] =
{
    {//+Y
        vector3df(0.0f, GetCfgVarFloat(MAX_Y_ROOM), 0.0f),
        vector3df(0.0f, -1.0f, 0.0f)
    },
    {//-Y
        vector3df(0.0f, GetCfgVarFloat(MIN_Y_ROOM), 0.0f),
        vector3df(0.0f, 1.0f, 0.0f)
    },
    {//+X
        vector3df(GetCfgVarFloat(MAX_X_ROOM), 0.0f, 0.0f),
        vector3df(-1.0f, 0.0f, 0.0f)
    },
    {//-X
        vector3df(GetCfgVarFloat(MIN_X_ROOM), 0.0f, 0.0f),
        vector3df(1.0f, 0.0f, 0.0f)
    },
    {//+Z
        vector3df(0.0f, 0.0f, GetCfgVarFloat(MAX_Z_ROOM)),
        vector3df(0.0f, 0.0f, -1.0f)
    },
    {//-Z
        vector3df(0.0f, 0.0f, GetCfgVarFloat(MIN_Z_ROOM)),
        vector3df(0.0f, 0.0f, 1.0f)
    },
};

static const f32 g_BoundsRoom[][16] =
{
    {//+Y
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_ROOM), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_ROOM), // x <= 76.3f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_ROOM), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_ROOM), // z <= 137.0f
    },
    {//-Y
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_ROOM), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_ROOM), // x <= 76.3f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_ROOM), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_ROOM), // z <= 137.0f
    },
    {//+X
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_ROOM), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_ROOM), // y <= 76.0f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_ROOM), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_ROOM), // z <= 137.0f
    },
    {//-X
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_ROOM), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_ROOM), // y <= 76.0f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_ROOM), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_ROOM), // z <= 137.0f
    },
    {//+Z
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_ROOM), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_ROOM), // x <= 76.3f
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_ROOM), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_ROOM), // y <= 76.0f
    },
    {//-Z
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_ROOM), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_ROOM), // x <= 76.3f
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_ROOM), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_ROOM), // y <= 76.0f
    },
};

bool CTennisRoom::g_bGeomReady = false;
S3DVertex CTennisRoom::g_vbStages[20][4];
u16 CTennisRoom::g_ibStages[20][12];

void CTennisRoom::SetupStageGeom()
{
    if( g_bGeomReady ) return;
    for( u32 i = 0; i < 20; i++ )
    {
        g_vbStages[i][0] =
            S3DVertex( // 0
                GetCfgVarFloat( MIN_X_STADIUM_BOT ) - 40.0f * i,
                GetCfgVarFloat( MIN_Y_STADIUM ) + 40.0f * i,
                GetCfgVarFloat( MAX_Z_STADIUM_BOT ) + 140.0f * i,
                -1, -1, -1,
                SColor( 255, 192, 192, 192 ),
                0, 1);

        g_vbStages[i][1] =
            S3DVertex( // 1
                GetCfgVarFloat( MAX_X_STADIUM_BOT ) + 40.0f * i,
                GetCfgVarFloat( MIN_Y_STADIUM ) + 40.0f * i,
                GetCfgVarFloat( MAX_Z_STADIUM_BOT ) + 140.0f * i,
                -1, 1, -1,
                SColor( 255, 192, 192, 192 ),
                1, 1);

        g_vbStages[i][2] =
            S3DVertex( // 2
                GetCfgVarFloat( MIN_X_STADIUM_BOT ) - 40.0f * i,
                GetCfgVarFloat( MIN_Y_STADIUM ) + 40.0f * ( i + 1 ),
                GetCfgVarFloat( MAX_Z_STADIUM_BOT ) + 140.0f * i,
                -1, -1, -1,
                SColor( 255, 100, 100, 100 ),
                0, 1);

        g_vbStages[i][3] =
            S3DVertex( // 3
                GetCfgVarFloat( MAX_X_STADIUM_BOT ) + 40.0f * i,
                GetCfgVarFloat( MIN_Y_STADIUM ) + 40.0f * ( i + 1 ),
                GetCfgVarFloat( MAX_Z_STADIUM_BOT ) + 140.0f * i,
                -1, 1, -1,
                SColor( 255, 100, 100, 100 ),
                1, 1);
    }

    for( u32 j = 0; j < 20; j++ )
    {
        u16 buf[12] =
        {
            0 + ( j * 4 ), 2 + ( j * 4 ), 3 + ( j * 4 ),
            0 + ( j * 4 ), 3 + ( j * 4 ), 1 + ( j * 4 ),
            2 + ( j * 4 ), 4 + ( j * 4 ), 5 + ( j * 4 ),
            2 + ( j * 4 ), 5 + ( j * 4 ), 3 + ( j * 4 ),
        };

        memcpy( g_ibStages[j], buf, sizeof(buf) );
    }

    g_bGeomReady = true;
}

CTennisRoom::CTennisRoom(
    ISceneNode* parent,
	ISceneManager* mgr,
	s32 id
	)
	: ISceneNode( parent, mgr, id )
    , Box( -1000.0f, -1000.0f, -2000.0f,
           +1000.0f, +1000.0f, +2000.0f)
{
	Material.Wireframe = false;
	Material.Lighting = false;

    IVideoDriver* pVideoDriver = SceneManager->getVideoDriver();
#ifdef USE_WILSON_ROOM
    SetupStageGeom();

    const char* tex = GetCfgVarStr( FILE_FLOOR_TEXTURE );    
	m_pTexGround = pVideoDriver->getTexture( tex );
#else

    const char* tex = GetCfgVarStr( FILE_SCENE_TEXTURE );
    m_pTexScene = pVideoDriver->getTexture( tex );

    const char* mesh = GetCfgVarStr( FILE_SCENE_MESH );
	if( !( m_pSceneMesh = SceneManager->getMesh( mesh ) ) ||
		!( m_pSceneNode = SceneManager->addAnimatedMeshSceneNode(
            m_pSceneMesh, this
            ) )
       )
		return ;

    aabbox3d<f32> bb = m_pSceneNode->getBoundingBox();
    //vector3df pos = m_pSceneNode->getPosition();
    //pos += vector3df( 0, 0, -bb.MaxEdge.Y );
    //m_pSceneNode->setPosition( pos );
    //f32 fScale = 2740.0f/( bb.MaxEdge.X - bb.MinEdge.X );
    f32 fScale = 1.f;
    vector3df scale( fScale, fScale, fScale );
    m_pSceneNode->setScale( scale );
    //vector3df rot( 0, 90, 0 );
    //m_pSceneNode->setRotation( rot );
	m_pSceneNode->setMaterialFlag( EMF_LIGHTING, false );
	m_pSceneNode->setMaterialTexture(
        0, m_pTexScene
		);
    m_pSceneNode->setLoopMode( false );
	m_pSceneNode->setVisible( true );

    tex = GetCfgVarStr( FILE_SCENE_TEXTURE_EX );
    m_pTexSceneEx = pVideoDriver->getTexture( tex );
    mesh = GetCfgVarStr( FILE_SCENE_MESH_EX );
	if( !( m_pSceneMeshEx = SceneManager->getMesh( mesh ) ) ||
		!( m_pSceneNodeEx = SceneManager->addAnimatedMeshSceneNode(
            m_pSceneMeshEx, this
            ) )
       )
		return ;


	bb = m_pSceneNodeEx->getBoundingBox();
	m_pSceneNodeEx->setMaterialFlag( EMF_LIGHTING, false );
	m_pSceneNodeEx->setMaterialTexture(
       0, m_pTexSceneEx
	);
    //vector3df scale2( 0.8f, 0.8f, 0.8f );
    //m_pSceneNodeEx->setScale( scale );
    m_pSceneNodeEx->setLoopMode( false );
	m_pSceneNodeEx->setVisible( true );


#endif
}

CTennisRoom::~CTennisRoom()
{
	// Scene node cannot do the texture release
	//if(	m_pSceneMesh )
	//	SceneManager->getMeshCache()->removeMesh(m_pSceneMesh);

	//if(	m_pSceneMeshEx )
	//	SceneManager->getMeshCache()->removeMesh(m_pSceneMeshEx);
}

//void CTennisRoom::RegisterPlanes(
//								 CTennisPhysics* physics
//								 )
//{
//	matrix4 bound;
//	f32* m = bound.pointer();
//
//	for( u32 i = 0; i< sizeof(g_PlanesRoom)/sizeof(g_PlanesRoom[0]); i++ )
//	{
//		memcpy( m, g_BoundsRoom[i], 16*sizeof(f32) );
//		CPhysicsPlane plane(
//			g_PlanesRoom[i][0],
//			g_PlanesRoom[i][1],
//			bound
//			);
//		physics->AddPhysicsPlane( plane );
//	}
//}

void CTennisRoom::render()
{
#ifdef USE_WILSON_ROOM
	IVideoDriver* driver = SceneManager->getVideoDriver();
#if 0
	static const u16 indices[] = {
		3, 2, 1, 3, 1, 0,
		0, 1, 5, 0, 5, 4,
		4, 5, 6, 4, 6, 7,
		7, 6, 2, 7, 2, 3,
		1, 2, 5, 2, 6, 5,
		0, 4, 3, 3, 4, 7,
	};

	driver->setMaterial( Material );
	driver->setTransform( ETS_WORLD, AbsoluteTransformation );
	driver->drawIndexedTriangleList(
		&g_vbRoom[0],
        8,
		&indices[0],
        12
		);
#else
	static const u16 indices[] = {
		 0,  1,  2,  0,  2,  3,
		 4,  5,  6,  4,  6,  7,
		 8,  9, 10,  8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23,
	};

    const char* tex = GetCfgVarStr( FILE_FLOOR_TEXTURE );
    
	driver->setMaterial( Material );
	this->setMaterialTexture( 0, m_pTexGround );

	driver->setTransform( ETS_WORLD, AbsoluteTransformation );
	driver->drawIndexedTriangleList(
		&g_vbRoom2[0],
        24,
		&indices[0],
        2//12
		);
#endif
#if 0
	driver->setMaterial( Material );
	driver->setTransform( ETS_WORLD, AbsoluteTransformation );
	static const u16 indices[] = {
		 0,  1,  2,  0,  2,  3,
    };
	driver->drawIndexedTriangleList(
		&g_vbRoom2[0],
        4,
		&indices[0],
        2
		);
	driver->drawIndexedTriangleList(
		&g_vbStages[0][0],
        80,
		&g_ibStages[0][0],
        76
		);
#endif

#endif
}


/*-----------------------------------------------------------------------------
 *
 *  This file is part of "Tennis game", which is based on Irrlicht Engine.
 *
 *  Revise History:
 *    Date          Author           Comment
 *    2008-08-10    Hu, weixiong     Initial version.
 *
 *  Copyright (c) 2007 Intel Corporation.
 *
 *-----------------------------------------------------------------------------
 */

/*
 TennisTable.cpp: implementation of the CTennisTable class.
 */

#include "include.h"
#include "TennisTable.h"
//#include "TennisPhysics.h"

using irr::core::vector3df;
using irr::video::SColor;
using irr::video::S3DVertex;
using irr::video::ETS_WORLD;
using irr::video::EMF_LIGHTING;
using irr::video::EMT_TRANSPARENT_ADD_COLOR;

#define RENDER_TABLE_MODEL 1

S3DVertex CTennisTable::g_vbTable[8] =
{
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_TABLE),
        GetCfgVarFloat(MIN_Y_TABLE),
        GetCfgVarFloat(MIN_Z_TABLE),
        -1, -1, -1,
        SColor(255,0,0,63),
        0, 1),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_TABLE),
        GetCfgVarFloat(MAX_Y_TABLE),
        GetCfgVarFloat(MIN_Z_TABLE),
        -1, 1, -1,
        SColor(255,0,0,96),
        1, 1),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_TABLE),
        GetCfgVarFloat(MAX_Y_TABLE),
        GetCfgVarFloat(MIN_Z_TABLE),
        1, 1, -1,
        SColor(255,0,0,96),
        1, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_TABLE),
        GetCfgVarFloat(MIN_Y_TABLE),
        GetCfgVarFloat(MIN_Z_TABLE),
        1, -1, -1,
        SColor(255,0,0,63),
        0, 0),
    S3DVertex( // 4
        GetCfgVarFloat(MIN_X_TABLE),
        GetCfgVarFloat(MIN_Y_TABLE),
        GetCfgVarFloat(MAX_Z_TABLE),
        -1, -1, 1,
        SColor(255,0,0,63),
        0, 0),
    S3DVertex( // 5
        GetCfgVarFloat(MIN_X_TABLE),
        GetCfgVarFloat(MAX_Y_TABLE),
        GetCfgVarFloat(MAX_Z_TABLE),
        -1, 1, 1,
        SColor(255,0,0,96),
        0, 0),
    S3DVertex( // 6
        GetCfgVarFloat(MAX_X_TABLE),
        GetCfgVarFloat(MAX_Y_TABLE),
        GetCfgVarFloat(MAX_Z_TABLE),
        1, 1, 1,
        SColor(255,0,0,96),
        0, 0),
    S3DVertex( // 7
        GetCfgVarFloat(MAX_X_TABLE),
        GetCfgVarFloat(MIN_Y_TABLE),
        GetCfgVarFloat(MAX_Z_TABLE),
        1, -1, 1,
        SColor(255,0,0,63),
        0, 0)
};

S3DVertex CTennisTable::g_vbTableWhiteBar[12] =
{
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_TABLE),
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MIN_Z_TABLE),
        -1, -1, -1,
        SColor(255,255,255,255),
        0, 1),
    S3DVertex( // 1
        GetCfgVarFloat(MAX_X_TABLE),
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MIN_Z_TABLE),
        -1, 1, -1,
        SColor(255,255,255,255),
        1, 1),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_TABLE),
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MAX_Z_TABLE),
        1, 1, -1,
        SColor(255,255,255,255),
        1, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MIN_X_TABLE),
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MAX_Z_TABLE),
        1, -1, -1,
        SColor(255,255,255,255),
        0, 0),
    S3DVertex( // 4
        GetCfgVarFloat(MIN_X_TABLE) + 2.0f,
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MIN_Z_TABLE) + 2.0f,
        -1, -1, -1,
        SColor(255,255,255,255),
        0, 1),
    S3DVertex( // 5
        GetCfgVarFloat(MAX_X_TABLE) - 2.0f,
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MIN_Z_TABLE) + 2.0f,
        -1, 1, -1,
        SColor(255,255,255,255),
        1, 1),
    S3DVertex( // 6
        GetCfgVarFloat(MAX_X_TABLE) - 2.0f,
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MAX_Z_TABLE) - 2.0f,
        1, 1, -1,
        SColor(255,255,255,255),
        1, 0),
    S3DVertex( // 7
        GetCfgVarFloat(MIN_X_TABLE) + 2.0f,
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MAX_Z_TABLE) - 2.0f,
        1, -1, -1,
        SColor(255,255,255,255),
        0, 0),
    S3DVertex( // 8
        -0.5f,
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MIN_Z_TABLE) + 2.0f,
        -1, -1, -1,
        SColor(255,255,255,255),
        0, 1),
    S3DVertex( // 9
        +0.5f,
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MIN_Z_TABLE) + 2.0f,
        -1, 1, -1,
        SColor(255,255,255,255),
        1, 1),
    S3DVertex( // 10
        +0.5f,
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MAX_Z_TABLE) - 2.0f,
        1, 1, -1,
        SColor(255,255,255,255),
        1, 0),
    S3DVertex( // 11
        -0.5f,
        GetCfgVarFloat(MAX_Y_TABLE) + 0.1f,
        GetCfgVarFloat(MAX_Z_TABLE) - 2.0f,
        1, -1, -1,
        SColor(255,255,255,255),
        0, 0),
};

S3DVertex CTennisTable::g_vbTableBase[8] =
{
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_TABLE_BASE),
        GetCfgVarFloat(MIN_Y_TABLE_BASE),
        GetCfgVarFloat(MIN_Z_TABLE_BASE),
        -1, -1, -1,
        SColor(255,127,0,0),
        0, 1),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_TABLE_BASE),
        GetCfgVarFloat(MAX_Y_TABLE_BASE),
        GetCfgVarFloat(MIN_Z_TABLE_BASE),
        -1, 1, -1,
        SColor(255,127,127,127),
        1, 1),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_TABLE_BASE),
        GetCfgVarFloat(MAX_Y_TABLE_BASE),
        GetCfgVarFloat(MIN_Z_TABLE_BASE),
        1, 1, -1,
        SColor(255,127,127,127),
        1, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_TABLE_BASE),
        GetCfgVarFloat(MIN_Y_TABLE_BASE),
        GetCfgVarFloat(MIN_Z_TABLE_BASE),
        1, -1, -1,
        SColor(255,127,0,0),
        0, 0),
    S3DVertex( // 4
        GetCfgVarFloat(MIN_X_TABLE_BASE),
        GetCfgVarFloat(MIN_Y_TABLE_BASE),
        GetCfgVarFloat(MAX_Z_TABLE_BASE),
        -1, -1, 1,
        SColor(255,127,0,0),
        0, 0),
    S3DVertex( // 5
        GetCfgVarFloat(MIN_X_TABLE_BASE),
        GetCfgVarFloat(MAX_Y_TABLE_BASE),
        GetCfgVarFloat(MAX_Z_TABLE_BASE),
        -1, 1, 1,
        SColor(255,127,127,127),
        0, 0),
    S3DVertex( // 6
        GetCfgVarFloat(MAX_X_TABLE_BASE),
        GetCfgVarFloat(MAX_Y_TABLE_BASE),
        GetCfgVarFloat(MAX_Z_TABLE_BASE),
        1, 1, 1,
        SColor(255,127,127,127),
        0, 0),
    S3DVertex( // 7
        GetCfgVarFloat(MAX_X_TABLE_BASE),
        GetCfgVarFloat(MIN_Y_TABLE_BASE),
        GetCfgVarFloat(MAX_Z_TABLE_BASE),
        1, -1, 1,
        SColor(255,127,0,0),
        0, 0)
};

S3DVertex CTennisTable::g_vbTableNet[8] =
{
    S3DVertex( // 0
        GetCfgVarFloat(MIN_X_TABLE_NET),
        GetCfgVarFloat(MIN_Y_TABLE_NET),
        GetCfgVarFloat(MIN_Z_TABLE_NET),
        -1, -1, -1,
        SColor(255,127,127,127),
        0, 1),
    S3DVertex( // 1
        GetCfgVarFloat(MIN_X_TABLE_NET),
        GetCfgVarFloat(MAX_Y_TABLE_NET),
        GetCfgVarFloat(MIN_Z_TABLE_NET),
        -1, 1, -1,
        SColor(255,255,255,255),
        1, 1),
    S3DVertex( // 2
        GetCfgVarFloat(MAX_X_TABLE_NET),
        GetCfgVarFloat(MAX_Y_TABLE_NET),
        GetCfgVarFloat(MIN_Z_TABLE_NET),
        1, 1, -1,
        SColor(255,255,255,255),
        1, 0),
    S3DVertex( // 3
        GetCfgVarFloat(MAX_X_TABLE_NET),
        GetCfgVarFloat(MIN_Y_TABLE_NET),
        GetCfgVarFloat(MIN_Z_TABLE_NET),
        1, -1, -1,
        SColor(255,127,127,127),
        0, 0),
    S3DVertex( // 4
        GetCfgVarFloat(MIN_X_TABLE_NET),
        GetCfgVarFloat(MIN_Y_TABLE_NET),
        GetCfgVarFloat(MAX_Z_TABLE_NET),
        -1, -1, 1,
        SColor(255,127,127,127),
        0, 0),
    S3DVertex( // 5
        GetCfgVarFloat(MIN_X_TABLE_NET),
        GetCfgVarFloat(MAX_Y_TABLE_NET),
        GetCfgVarFloat(MAX_Z_TABLE_NET),
        -1, 1, 1,
        SColor(255,255,255,255),
        0, 0),
    S3DVertex( // 6
        GetCfgVarFloat(MAX_X_TABLE_NET),
        GetCfgVarFloat(MAX_Y_TABLE_NET),
        GetCfgVarFloat(MAX_Z_TABLE_NET),
        1, 1, 1,
        SColor(255,255,255,255),
        0, 0),
    S3DVertex( // 7
        GetCfgVarFloat(MAX_X_TABLE_NET),
        GetCfgVarFloat(MIN_Y_TABLE_NET),
        GetCfgVarFloat(MAX_Z_TABLE_NET),
        1, -1, 1,
        SColor(255,127,127,127),
        0, 0)
};

CTennisTable::CTennisTable(
    ISceneNode* parent,
    ISceneManager* mgr,
    s32 id
    )
: ISceneNode( parent, mgr, id )
, m_AABox(
      GetCfgVarFloat( MIN_X_TABLE ),
      GetCfgVarFloat( MIN_Y_TABLE_BASE ),
      GetCfgVarFloat( MIN_Z_TABLE ),
      GetCfgVarFloat( MAX_X_TABLE ),
      GetCfgVarFloat( MAX_Y_TABLE_NET ),
      GetCfgVarFloat( MAX_Z_TABLE )
      )
, m_pTableMesh( 0 )
{
    m_Material.Wireframe = false;
    m_Material.Lighting = false;

    u32 i = 0;

#ifdef USE_WILSON_TABLE
    // Use Wilson's table mesh
#define NEW_VERT( x, y, z, u, v ) S3DVertex( x, y, z, 0, 0, 0, 0xFFFFFFFF, u, v )
#define PUSH_VERT( x, y, z, u, v ) m_meshTable[i] = NEW_VERT( x, y, z, u, v )

    // 0 - 3
    PUSH_VERT( -1.0f, 76.0f, -135.0f, 125.0f/256.0f, 156.0f/256.0f ); i++;
    PUSH_VERT( -1.0f, 76.0f, +135.0f, 125.0f/256.0f, 100.0f/256.0f ); i++;
    PUSH_VERT( +1.0f, 76.0f, +135.0f, 131.0f/256.0f, 100.0f/256.0f ); i++;
    PUSH_VERT( +1.0f, 76.0f, -135.0f, 131.0f/256.0f, 156.0f/256.0f ); i++;

    // 4 - 7
    PUSH_VERT( -74.25f, 76.0f, -135.0f, 80.0f/256.0f, 176.0f/256.0f ); i++;
    PUSH_VERT( -74.25f, 76.0f, +135.0f, 80.0f/256.0f, 80.0f/256.0f ); i++;
    PUSH_VERT( +75.25f, 76.0f, +135.0f, 176.0f/256.0f, 80.0f/256.0f ); i++;
    PUSH_VERT( +75.25f, 76.0f, -135.0f, 176.0f/256.0f, 176.0f/256.0f ); i++;

    // 8 - 11
    PUSH_VERT( -76.25f, 76.0f, -137.0f, 60.0f/256.0f, 196.0f/256.0f ); i++;
    PUSH_VERT( -76.25f, 76.0f, +137.0f, 60.0f/256.0f, 60.0f/256.0f ); i++;
    PUSH_VERT( +76.25f, 76.0f, +137.0f, 196.0f/256.0f, 60.0f/256.0f ); i++;
    PUSH_VERT( +76.25f, 76.0f, -137.0f, 196.0f/256.0f, 196.0f/256.0f ); i++;

    // 12 - 15
    PUSH_VERT( -76.25f, 71.0f, -137.0f, 40.0f/256.0f, 216.0f/256.0f ); i++;
    PUSH_VERT( -76.25f, 71.0f, +137.0f, 40.0f/256.0f, 40.0f/256.0f ); i++;
    PUSH_VERT( +76.25f, 71.0f, +137.0f, 216.0f/256.0f, 40.0f/256.0f ); i++;
    PUSH_VERT( +76.25f, 71.0f, -137.0f, 216.0f/256.0f, 216.0f/256.0f ); i++;

    // 16 - 19
    PUSH_VERT( -76.25f*0.8f, 71.0f, -137.0f*0.9f, 40.0f/256.0f, 216.0f/256.0f ); i++;
    PUSH_VERT( -76.25f*0.8f, 71.0f, +137.0f*0.9f, 40.0f/256.0f, 40.0f/256.0f ); i++;
    PUSH_VERT( +76.25f*0.8f, 71.0f, +137.0f*0.9f, 216.0f/256.0f, 40.0f/256.0f ); i++;
    PUSH_VERT( +76.25f*0.8f, 71.0f, -137.0f*0.9f, 216.0f/256.0f, 216.0f/256.0f ); i++;

    // 20 - 23
    PUSH_VERT( -76.25f*0.3f, 40.0f, -137.0f*0.7f, 20.0f/256.0f, 236.0f/256.0f ); i++;
    PUSH_VERT( -76.25f*0.3f, 40.0f, +137.0f*0.7f, 20.0f/256.0f, 20.0f/256.0f ); i++;
    PUSH_VERT( +76.25f*0.3f, 40.0f, +137.0f*0.7f, 236.0f/256.0f, 20.0f/256.0f ); i++;
    PUSH_VERT( +76.25f*0.3f, 40.0f, -137.0f*0.7f, 236.0f/256.0f, 236.0f/256.0f ); i++;

    // 24 - 27
    PUSH_VERT( -76.25f*0.6f, 0.0f, -137.0f*0.8f, 0.0f, 1.0f ); i++;
    PUSH_VERT( -76.25f*0.6f, 0.0f, +137.0f*0.8f, 0.0f, 0.0f ); i++;
    PUSH_VERT( +76.25f*0.6f, 0.0f, +137.0f*0.8f, 1.0f, 0.0f ); i++;
    PUSH_VERT( +76.25f*0.6f, 0.0f, -137.0f*0.8f, 1.0f, 1.0f ); i++;

    i = 0;
#define NEW_TRI( v1, v2, v3 ) \
    {\
        m_indTable[i+0] = v1; \
        m_indTable[i+1] = v2; \
        m_indTable[i+2] = v3; \
    } i+= 3;

    NEW_TRI(  0,  1,  2 );
    NEW_TRI(  0,  2,  3 );
    NEW_TRI(  4,  5,  1 );
    NEW_TRI(  4,  1,  0 );
    NEW_TRI(  3,  2,  6 );
    NEW_TRI(  3,  6,  7 );

    NEW_TRI(  8,  9,  5 ); // L
    NEW_TRI(  8,  5,  4 );  
    NEW_TRI(  7,  6, 10 ); // R
    NEW_TRI(  7, 10, 11 );
    NEW_TRI(  5,  9, 10 ); // T
    NEW_TRI(  5, 10,  6 );
    NEW_TRI(  5,  9, 10 ); // B
    NEW_TRI(  5, 10,  6 );

    NEW_TRI( 12, 13,  9 ); // L
    NEW_TRI( 12,  9,  8 );
    NEW_TRI( 11, 10, 14 ); // R
    NEW_TRI( 11, 14, 15 );
    NEW_TRI(  9, 13, 14 ); // T
    NEW_TRI(  9, 14, 10 );
    NEW_TRI( 12,  8, 11 ); // B
    NEW_TRI( 12, 11, 15 );

    NEW_TRI( 16, 17, 13 ); // L
    NEW_TRI( 16, 13, 12 );
    NEW_TRI( 15, 14, 18 ); // R
    NEW_TRI( 15, 18, 19 );
    NEW_TRI( 13, 17, 18 ); // T
    NEW_TRI( 13, 18, 14 );
    NEW_TRI( 16, 12, 15 ); // B
    NEW_TRI( 16, 15, 19 );

    NEW_TRI( 20, 21, 17 ); // L
    NEW_TRI( 20, 17, 16 );
    NEW_TRI( 19, 18, 22 ); // R
    NEW_TRI( 19, 22, 23 );
    NEW_TRI( 17, 21, 22 ); // T
    NEW_TRI( 17, 22, 18 );
    NEW_TRI( 20, 16, 19 ); // B
    NEW_TRI( 20, 19, 23 );

    NEW_TRI( 24, 25, 21 ); // L
    NEW_TRI( 24, 21, 20 );
    NEW_TRI( 23, 22, 26 ); // R
    NEW_TRI( 23, 26, 27 );
    NEW_TRI( 21, 25, 26 ); // T
    NEW_TRI( 21, 26, 22 );
    NEW_TRI( 24, 20, 23 ); // B
    NEW_TRI( 24, 23, 27 );
#endif

    // Use Wilson's fence mesh
#undef NEW_VERT
#undef PUSH_VERT
#undef NEW_TRI
#define NEW_VERT( x, y, z, u, v ) S3DVertex( x, y, z, 0, 0, 0, 0xFFFFFFFF, u, v )
#define PUSH_VERT( x, y, z, u, v ) m_meshFence[i] = NEW_VERT( x, y, z, u, v )

    i = 0;

#if 0
    const float f0 = 4.3f;
    const float f1 = 4.5f;
    const float f2 = 4.7f;
    // 0 - 3
    PUSH_VERT( -74.25f * f0, 0.0f, -135.0f * f0, 0.25f, 0.75f ); i++;
    PUSH_VERT( -74.25f * f0, 0.0f, +135.0f * f0, 0.25f, 0.25f ); i++;
    PUSH_VERT( +75.25f * f0, 0.0f, +135.0f * f0, 0.75f, 0.25f ); i++;
    PUSH_VERT( +75.25f * f0, 0.0f, -135.0f * f0, 0.75f, 0.75f ); i++;

    // 4 - 7
    PUSH_VERT( -74.25f * f1, 50.0f, -135.0f * f1, 0.125f, 0.875f ); i++;
    PUSH_VERT( -74.25f * f1, 50.0f, +135.0f * f1, 0.125f, 0.125f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, +135.0f * f1, 0.875f, 0.125f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, -135.0f * f1, 0.875f, 0.875f ); i++;

    // 8 - 11
    PUSH_VERT( -74.25f * f2, 0.0f, -135.0f * f2, 0.0f, 1.0f ); i++;
    PUSH_VERT( -74.25f * f2, 0.0f, +135.0f * f2, 0.0f, 0.0f ); i++;
    PUSH_VERT( +75.25f * f2, 0.0f, +135.0f * f2, 1.0f, 0.0f ); i++;
    PUSH_VERT( +75.25f * f2, 0.0f, -135.0f * f2, 1.0f, 1.0f ); i++;
#else
    const float f0 = 4.5f;
    const float f1 = 4.5f;
    const float f2 = 4.5f;

#ifdef _ENABLE_SCROLLING_AD_

    // 0 - 3
    PUSH_VERT( -74.25f * f0, 0.0f, -135.0f * f0, 0.0f, 1.0f ); i++;
    PUSH_VERT( -74.25f * f0, 0.0f, +135.0f * f0, 4.0f, 1.0f ); i++;
    PUSH_VERT( +75.25f * f0, 0.0f, +135.0f * f0, 6.0f, 1.0f ); i++;
    PUSH_VERT( +75.25f * f0, 0.0f, -135.0f * f0, 10.0f, 1.0f ); i++;

    // 4 - 7
    PUSH_VERT( -74.25f * f1, 50.0f, -135.0f * f1, 0.0f, 0.75f ); i++;
    PUSH_VERT( -74.25f * f1, 50.0f, +135.0f * f1, 4.0f, 0.75f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, +135.0f * f1, 6.0f, 0.75f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, -135.0f * f1, 10.0f, 0.75f ); i++;

    // 8 - 11
    PUSH_VERT( -74.25f * f1, 50.0f, -135.0f * f1, 10.0f, 0.75f ); i++;
    PUSH_VERT( -74.25f * f1, 50.0f, +135.0f * f1, 6.0f, 0.75f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, +135.0f * f1, 4.0f, 0.75f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, -135.0f * f1, 0.0f, 0.75f ); i++;

    // 12 - 15
    PUSH_VERT( -74.25f * f2, 0.0f, -135.0f * f2, 10.0f, 1.0f ); i++;
    PUSH_VERT( -74.25f * f2, 0.0f, +135.0f * f2, 6.0f, 1.0f ); i++;
    PUSH_VERT( +75.25f * f2, 0.0f, +135.0f * f2, 4.0f, 1.0f ); i++;
    PUSH_VERT( +75.25f * f2, 0.0f, -135.0f * f2, 0.0f, 1.0f ); i++;

    // 16-19
    PUSH_VERT( +75.25f * f0, 0.0f, -135.0f * f0, -2.0f, 1.0f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, -135.0f * f1, -2.0f, 0.75f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, -135.0f * f1, 12.0f, 0.75f ); i++;
    PUSH_VERT( +75.25f * f2, 0.0f, -135.0f * f2, 12.0f, 1.0f ); i++;

#else

    // 0 - 3
    PUSH_VERT( -74.25f * f0, 0.0f, -135.0f * f0, 0.0f, 1.0f ); i++;
    PUSH_VERT( -74.25f * f0, 0.0f, +135.0f * f0, 4.0f, 1.0f ); i++;
    PUSH_VERT( +75.25f * f0, 0.0f, +135.0f * f0, 6.0f, 1.0f ); i++;
    PUSH_VERT( +75.25f * f0, 0.0f, -135.0f * f0, 10.0f, 1.0f ); i++;

    // 4 - 7
    PUSH_VERT( -74.25f * f1, 50.0f, -135.0f * f1, 0.0f, 0.5f ); i++;
    PUSH_VERT( -74.25f * f1, 50.0f, +135.0f * f1, 4.0f, 0.5f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, +135.0f * f1, 6.0f, 0.5f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, -135.0f * f1, 10.0f, 0.5f ); i++;

    // 8 - 11
    PUSH_VERT( -74.25f * f2, 0.0f, -135.0f * f2, 0.0f, 0.0f ); i++;
    PUSH_VERT( -74.25f * f2, 0.0f, +135.0f * f2, 4.0f, 0.0f ); i++;
    PUSH_VERT( +75.25f * f2, 0.0f, +135.0f * f2, 6.0f, 0.0f ); i++;
    PUSH_VERT( +75.25f * f2, 0.0f, -135.0f * f2, 10.0f, 0.0f ); i++;

    // 12-14
    PUSH_VERT( +75.25f * f0, 0.0f, -135.0f * f0, -2.0f, 1.0f ); i++;
    PUSH_VERT( +75.25f * f1, 50.0f, -135.0f * f1, -2.0f, 0.5f ); i++;
    PUSH_VERT( +75.25f * f2, 0.0f, -135.0f * f2, -2.0f, 0.0f ); i++;

#endif

#endif

    i = 0;
#define NEW_TRI( v1, v2, v3 ) \
    {\
        m_indFence[i+0] = v1; \
        m_indFence[i+1] = v2; \
        m_indFence[i+2] = v3; \
    } i+= 3;

#ifdef _ENABLE_SCROLLING_AD_
    NEW_TRI(  4,  5,  1 ); // L
    NEW_TRI(  4,  1,  0 );  
    NEW_TRI(  3,  2,  6 ); // R
    NEW_TRI(  3,  6,  7 );
    NEW_TRI(  1,  5,  6 ); // T
    NEW_TRI(  1,  6,  2 );
    NEW_TRI(  4,  0, 16 ); // B
    NEW_TRI(  4, 16, 17 );

    NEW_TRI( 12, 13,  9 ); // L
    NEW_TRI( 12,  9,  8 );
    NEW_TRI( 11, 10, 14 ); // R
    NEW_TRI( 11, 14, 15 );
    NEW_TRI(  9, 13, 14 ); // T
    NEW_TRI(  9, 14, 10 );
    NEW_TRI( 12,  8, 18 ); // B
    NEW_TRI( 12, 18, 19 );
#else
    NEW_TRI(  4,  5,  1 ); // L
    NEW_TRI(  4,  1,  0 );  
    NEW_TRI(  3,  2,  6 ); // R
    NEW_TRI(  3,  6,  7 );
    NEW_TRI(  1,  5,  6 ); // T
    NEW_TRI(  1,  6,  2 );
    NEW_TRI(  4,  0, 12 ); // B
    NEW_TRI(  4, 12, 13 );

    NEW_TRI(  8,  9,  5 ); // L
    NEW_TRI(  8,  5,  4 );
    NEW_TRI(  7,  6, 10 ); // R
    NEW_TRI(  7, 10, 14 );
    NEW_TRI(  5,  9, 10 ); // T
    NEW_TRI(  5, 10,  6 );
    NEW_TRI(  8,  4, 13 ); // B
    NEW_TRI(  8, 13, 14 );
#endif

#ifdef USE_WILSON_ROOM
    // Use Wilson's stage mesh
    const float f3 = 7.0f;
    const float f4 = 50.0f;
    const float f5 = 100.0f;
    SColor clrLight(255,128,128,128);
    SColor clrDark(255,80,80,80);
    SColor clrLight2(255,100,100,100);

    m_meshStage[0] = S3DVertex( -74.25f * f3, 0.0f, -135.0f * f3,
        0, 0, 0, clrLight2, 0, 0 );
    m_meshStage[1] = S3DVertex( -74.25f * f3, 0.0f, +135.0f * f3,
        0, 0, 0, clrLight2, 0, 0 );
    m_meshStage[2] = S3DVertex( +75.25f * f3, 0.0f, +135.0f * f3,
        0, 0, 0, clrLight2, 0, 0 );
    m_meshStage[3] = S3DVertex( +75.25f * f3, 0.0f, -135.0f * f3,
        0, 0, 0, clrLight2, 0, 0 );

    for( i = 1; i <= 10; i++ )
    {
        m_meshStage[4+(i-1)*8+0] = m_meshStage[4+(i-1)*8-4];
        m_meshStage[4+(i-1)*8+1] = m_meshStage[4+(i-1)*8-3];
        m_meshStage[4+(i-1)*8+2] = m_meshStage[4+(i-1)*8-2];
        m_meshStage[4+(i-1)*8+3] = m_meshStage[4+(i-1)*8-1];
        m_meshStage[4+(i-1)*8+0].Pos.Y += f4;
        m_meshStage[4+(i-1)*8+1].Pos.Y += f4;
        m_meshStage[4+(i-1)*8+2].Pos.Y += f4;
        m_meshStage[4+(i-1)*8+3].Pos.Y += f4;

        m_meshStage[4+(i-1)*8+4] = m_meshStage[4+(i-1)*8+0];
        m_meshStage[4+(i-1)*8+5] = m_meshStage[4+(i-1)*8+1];
        m_meshStage[4+(i-1)*8+6] = m_meshStage[4+(i-1)*8+2];
        m_meshStage[4+(i-1)*8+7] = m_meshStage[4+(i-1)*8+3];
        m_meshStage[4+(i-1)*8+4].Pos.X -= f5;
        m_meshStage[4+(i-1)*8+5].Pos.X -= f5;
        m_meshStage[4+(i-1)*8+6].Pos.X += f5;
        m_meshStage[4+(i-1)*8+7].Pos.X += f5;
        m_meshStage[4+(i-1)*8+4].Pos.Z -= f5;
        m_meshStage[4+(i-1)*8+5].Pos.Z += f5;
        m_meshStage[4+(i-1)*8+6].Pos.Z += f5;
        m_meshStage[4+(i-1)*8+7].Pos.Z -= f5;

        m_meshStage[4+(i-1)*8+0].Color = clrLight;
        m_meshStage[4+(i-1)*8+1].Color = clrLight;
        m_meshStage[4+(i-1)*8+2].Color = clrLight;
        m_meshStage[4+(i-1)*8+3].Color = clrLight;
        m_meshStage[4+(i-1)*8+4].Color = clrDark;
        m_meshStage[4+(i-1)*8+5].Color = clrDark;
        m_meshStage[4+(i-1)*8+6].Color = clrDark;
        m_meshStage[4+(i-1)*8+7].Color = clrDark;

        {
            // L
            m_indStage[(i-1)*48+0] = 4 + (i-1)*8 +0;
            m_indStage[(i-1)*48+1] = 4 + (i-1)*8 +1;
            m_indStage[(i-1)*48+2] = 4 + (i-1)*8 -3;
            m_indStage[(i-1)*48+3] = 4 + (i-1)*8 +0;
            m_indStage[(i-1)*48+4] = 4 + (i-1)*8 -3;
            m_indStage[(i-1)*48+5] = 4 + (i-1)*8 -4;

            // R
            m_indStage[(i-1)*48+6] = 4 + (i-1)*8 -1;
            m_indStage[(i-1)*48+7] = 4 + (i-1)*8 -2;
            m_indStage[(i-1)*48+8] = 4 + (i-1)*8 +2;
            m_indStage[(i-1)*48+9] = 4 + (i-1)*8 -1;
            m_indStage[(i-1)*48+10] = 4 + (i-1)*8 +2;
            m_indStage[(i-1)*48+11] = 4 + (i-1)*8 +3;

            // T
            m_indStage[(i-1)*48+12] = 4 + (i-1)*8 -3;
            m_indStage[(i-1)*48+13] = 4 + (i-1)*8 +1;
            m_indStage[(i-1)*48+14] = 4 + (i-1)*8 +2;
            m_indStage[(i-1)*48+15] = 4 + (i-1)*8 -3;
            m_indStage[(i-1)*48+16] = 4 + (i-1)*8 +2;
            m_indStage[(i-1)*48+17] = 4 + (i-1)*8 -2;

            // B
            m_indStage[(i-1)*48+18] = 4 + (i-1)*8 +0;
            m_indStage[(i-1)*48+19] = 4 + (i-1)*8 -4;
            m_indStage[(i-1)*48+20] = 4 + (i-1)*8 -1;
            m_indStage[(i-1)*48+21] = 4 + (i-1)*8 +0;
            m_indStage[(i-1)*48+22] = 4 + (i-1)*8 -1;
            m_indStage[(i-1)*48+23] = 4 + (i-1)*8 +3;
        }
        {
            // L
            m_indStage[(i-1)*48+24] = 4 + (i-1)*8 +0 +4;
            m_indStage[(i-1)*48+25] = 4 + (i-1)*8 +1 +4;
            m_indStage[(i-1)*48+26] = 4 + (i-1)*8 -3 +4;
            m_indStage[(i-1)*48+27] = 4 + (i-1)*8 +0 +4;
            m_indStage[(i-1)*48+28] = 4 + (i-1)*8 -3 +4;
            m_indStage[(i-1)*48+29] = 4 + (i-1)*8 -4 +4;

            // R
            m_indStage[(i-1)*48+30] = 4 + (i-1)*8 -1 +4;
            m_indStage[(i-1)*48+31] = 4 + (i-1)*8 -2 +4;
            m_indStage[(i-1)*48+32] = 4 + (i-1)*8 +2 +4;
            m_indStage[(i-1)*48+33] = 4 + (i-1)*8 -1 +4;
            m_indStage[(i-1)*48+34] = 4 + (i-1)*8 +2 +4;
            m_indStage[(i-1)*48+35] = 4 + (i-1)*8 +3 +4;

            // T
            m_indStage[(i-1)*48+36] = 4 + (i-1)*8 -3 +4;
            m_indStage[(i-1)*48+37] = 4 + (i-1)*8 +1 +4;
            m_indStage[(i-1)*48+38] = 4 + (i-1)*8 +2 +4;
            m_indStage[(i-1)*48+39] = 4 + (i-1)*8 -3 +4;
            m_indStage[(i-1)*48+40] = 4 + (i-1)*8 +2 +4;
            m_indStage[(i-1)*48+41] = 4 + (i-1)*8 -2 +4;

            // B
            m_indStage[(i-1)*48+42] = 4 + (i-1)*8 +0 +4;
            m_indStage[(i-1)*48+43] = 4 + (i-1)*8 -4 +4;
            m_indStage[(i-1)*48+44] = 4 + (i-1)*8 -1 +4;
            m_indStage[(i-1)*48+45] = 4 + (i-1)*8 +0 +4;
            m_indStage[(i-1)*48+46] = 4 + (i-1)*8 -1 +4;
            m_indStage[(i-1)*48+47] = 4 + (i-1)*8 +3 +4;
        }
    }
#endif
}

CTennisTable::~CTennisTable()
{
//	delete m_pAdAnimator;

	//if(	m_pTableMesh )
	//	SceneManager->getMeshCache()->removeMesh(m_pTableMesh);

	//if(	m_pTableNetMesh )
	//	SceneManager->getMeshCache()->removeMesh(m_pTableNetMesh);
}

void CTennisTable::render()
{
    IVideoDriver* driver = SceneManager->getVideoDriver();
    
    driver->setMaterial( m_Material );
    driver->setTransform( ETS_WORLD, AbsoluteTransformation );
    
#ifdef USE_WILSON_TABLE

#if 0
    static const u16 indices[] = {
        0, 1, 2, 0, 2, 3,
        3, 2, 6, 3, 6, 7,
        7, 6, 5, 7, 5, 4,
        4, 5, 1, 4, 1, 0,
        1, 5, 6, 1, 6, 2,
        0, 3, 7, 0, 7, 4,
    };
    driver->drawIndexedTriangleList(
        &g_vbTableBase[0],
        8,
        &indices[0],
        12
        );
    driver->drawIndexedTriangleList(
        &g_vbTable[0],
        8,
        &indices[0],
        12
        );
#else
    m_Material.Textures[0] = m_pTexTable;
    driver->setMaterial( m_Material );
    driver->drawIndexedTriangleList(
        &m_meshTable[0],
        28,
        &m_indTable[0],
        46
        );

#ifdef _ENABLE_SCROLLING_AD_
    m_Material.Textures[0] = m_pTexFence;
    driver->setMaterial( m_Material );
    driver->drawIndexedTriangleList(
        &m_meshFence[0],
        20,
        &m_indFence[0],
        16
        );
#else
    m_Material.Textures[0] = m_pTexFence;
    driver->setMaterial( m_Material );
    driver->drawIndexedTriangleList(
        &m_meshFence[0],
        15,
        &m_indFence[0],
        16
        );
#endif

#ifdef USE_WILSON_ROOM
    m_Material.Textures[0] = 0;
    driver->setMaterial( m_Material );
    driver->drawIndexedTriangleList(
        &m_meshStage[0],
        84,
        &m_indStage[0],
        160
        );
#endif

#endif

#ifdef _ENABLE_SCROLLING_AD_

	/*
    driver->drawIndexedTriangleList(
        &g_vbTableNet[0], 8, &indices[0], 12
        );
	*/
	{
		f32 deltaH = ( GetCfgVarFloat( MAX_Y_TABLE_NET ) -
			GetCfgVarFloat( MIN_Y_TABLE_NET ) ) / 10.0f;

		for( u32 i = 0; i <= 10; i++ )
		{
			driver->draw3DLine(
				vector3df(
					GetCfgVarFloat(MIN_X_TABLE_NET),
					GetCfgVarFloat(MIN_Y_TABLE_NET) + deltaH * i,
					0.0f
					),
				vector3df(
					GetCfgVarFloat(MAX_X_TABLE_NET),
					GetCfgVarFloat(MIN_Y_TABLE_NET) + deltaH * i,
					0.0f 
					),
					(
						i == 10 ?
						SColor(255, 255, 255, 255) : SColor(255, 0, 0, 192)
					)
				);
		}

		f32 deltaW = ( GetCfgVarFloat( MAX_X_TABLE_NET ) -
			GetCfgVarFloat( MIN_X_TABLE_NET ) ) / 80.0f;
		for( u32 j = 0; j <= 80; j++ )
		{
			driver->draw3DLine(
				vector3df(
					GetCfgVarFloat(MIN_X_TABLE_NET) + deltaW * j,
					GetCfgVarFloat(MAX_Y_TABLE_NET),
					0.0f 
					),
				vector3df(
					GetCfgVarFloat(MIN_X_TABLE_NET) + deltaW * j,
					GetCfgVarFloat(MIN_Y_TABLE_NET),
					0.0f 
					),
					(
						(( j == 0 )||( j == 80 )) ?
						SColor(255, 127, 127, 127) : SColor(255, 0, 0, 192)
					)
				);
		}
	}

	{
	    static const u16 indices2[] = {
			0, 4, 5, 0, 5, 1,
			1, 5, 6, 1, 6, 2,
			2, 6, 7, 2, 7, 3,
			3, 7, 4, 3, 4, 0,

			9,  8, 11, 
			9, 11, 10,
		};
		driver->drawIndexedTriangleList(
			&g_vbTableWhiteBar[0],
            12,
            &indices2[0],
            10
			);
	}

#endif
#else

#ifdef USE_WILSON_TABLE
    m_Material.Textures[0] = m_pTexTable;
    driver->setMaterial( m_Material );
    driver->drawIndexedTriangleList(
        &m_meshTable[0],
        28,
        &m_indTable[0],
        46
        );
#endif

#ifdef _ENABLE_SCROLLING_AD_
    m_Material.Textures[0] = m_pTexFence;
    driver->setMaterial( m_Material );
    driver->drawIndexedTriangleList(
        &m_meshFence[0],
        15,
        &m_indFence[0],
        16
        );
#endif
#endif
}

static const vector3df g_PlanesTable[][2] =
{
    // Table
    {//+Y
        vector3df(0.0f, GetCfgVarFloat(MAX_Y_TABLE), 0.0f),
        vector3df(0.0f, 1.0f, 0.0f)
    },
    {//-Y
        vector3df(0.0f, GetCfgVarFloat(MIN_Y_TABLE), 0.0f),
        vector3df(0.0f, -1.0f, 0.0f)
    },
    {//+X
        vector3df(GetCfgVarFloat(MAX_X_TABLE), 0.0f, 0.0f),
        vector3df(1.0f, 0.0f, 0.0f)
    },
    {//-X
        vector3df(GetCfgVarFloat(MIN_X_TABLE), 0.0f, 0.0f),
        vector3df(-1.0f, 0.0f, 0.0f)
    },
    {//+Z
        vector3df(0.0f, 0.0f, GetCfgVarFloat(MAX_Z_TABLE)),
        vector3df(0.0f, 0.0f, 1.0f)
    },
    {//-Z
        vector3df(0.0f, 0.0f, GetCfgVarFloat(MIN_Z_TABLE)),
        vector3df(0.0f, 0.0f, -1.0f)
    },

    // Table Base
    {//+X
        vector3df(GetCfgVarFloat(MAX_X_TABLE_BASE), 0.0f, 0.0f),
        vector3df(1.0f, 0.0f, 0.0f)
    },
    {//-X
        vector3df(GetCfgVarFloat(MIN_X_TABLE_BASE), 0.0f, 0.0f),
        vector3df(-1.0f, 0.0f, 0.0f)
    },
    {//+Z
        vector3df(0.0f, 0.0f, GetCfgVarFloat(MAX_Z_TABLE_BASE)),
        vector3df(0.0f, 0.0f, 1.0f)
    },
    {//-Z
        vector3df(0.0f, 0.0f, GetCfgVarFloat(MIN_Z_TABLE_BASE)),
        vector3df(0.0f, 0.0f, -1.0f)
    },

    // Net
    {//+Y
        vector3df(0.0f, GetCfgVarFloat(MAX_Y_TABLE_NET), 0.0f),
        vector3df(0.0f, 1.0f, 0.0f)
    },
    {//+X
        vector3df(GetCfgVarFloat(MAX_X_TABLE_NET), 0.0f, 0.0f),
        vector3df(1.0f, 0.0f, 0.0f)
    },
    {//-X
        vector3df(GetCfgVarFloat(MIN_X_TABLE_NET), 0.0f, 0.0f),
        vector3df(-1.0f, 0.0f, 0.0f)
    },
    {//+Z
        vector3df(0.0f, 0.0f, GetCfgVarFloat(MAX_Z_TABLE_NET)),
        vector3df(0.0f, 0.0f, 1.0f)
    },
    {//-Z
        vector3df(0.0f, 0.0f, GetCfgVarFloat(MIN_Z_TABLE_NET)),
        vector3df(0.0f, 0.0f, -1.0f)
    },
};

static const f32 g_BoundsTable[][16] =
{
    {//+Y
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_TABLE), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_TABLE), // x <= 76.3f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_TABLE), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_TABLE), // z <= 137.0f
    },
    {//-Y
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_TABLE), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_TABLE), // x <= 76.3f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_TABLE), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_TABLE), // z <= 137.0f
    },
    {//+X
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE), // y <= 76.0f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_TABLE), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_TABLE), // z <= 137.0f
    },
    {//-X
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE), // y <= 76.0f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_TABLE), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_TABLE), // z <= 137.0f
    },
    {//+Z
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_TABLE), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_TABLE), // x <= 76.3f
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE), // y <= 76.0f
    },
    {//-Z
         1.0f, 0.0f,   0.0f, -GetCfgVarFloat(MIN_X_TABLE), // x >= -76.3f
        -1.0f, 0.0f,   0.0f,  GetCfgVarFloat(MAX_X_TABLE), // x <= 76.3f
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE), // y <= 76.0f
    },

    {//+X
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE_BASE), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE_BASE), // y <= 76.0f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_TABLE_BASE), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_TABLE_BASE), // z <= 137.0f
    },
    {//-X
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE_BASE), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE_BASE), // y <= 76.0f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_TABLE_BASE), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_TABLE_BASE), // z <= 137.0f
    },
    {//+Z
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_TABLE_BASE), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_TABLE_BASE), // x <= 76.3f
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE_BASE), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE_BASE), // y <= 76.0f
    },
    {//-Z
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_TABLE_BASE), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_TABLE_BASE), // x <= 76.3f
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE_BASE), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE_BASE), // y <= 76.0f
    },

    // Net
    {//+Y
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_TABLE_NET), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_TABLE_NET), // x <= 76.3f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_TABLE_NET), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_TABLE_NET), // z <= 137.0f
    },
    {//+X
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE_NET), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE_NET), // y <= 76.0f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_TABLE_NET), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_TABLE_NET), // z <= 137.0f
    },
    {//-X
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE_NET), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE_NET), // y <= 76.0f
         0.0f,  0.0f,  1.0f, -GetCfgVarFloat(MIN_Z_TABLE_NET), // z >= -137.0f
         0.0f,  0.0f, -1.0f,  GetCfgVarFloat(MAX_Z_TABLE_NET), // z <= 137.0f
    },
    {//+Z
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_TABLE_NET), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_TABLE_NET), // x <= 76.3f
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE_NET), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE_NET), // y <= 76.0f
    },
    {//-Z
         1.0f,  0.0f,  0.0f, -GetCfgVarFloat(MIN_X_TABLE_NET), // x >= -76.3f
        -1.0f,  0.0f,  0.0f,  GetCfgVarFloat(MAX_X_TABLE_NET), // x <= 76.3f
         0.0f,  1.0f,  0.0f, -GetCfgVarFloat(MIN_Y_TABLE_NET), // y >= 71.0f
         0.0f, -1.0f,  0.0f,  GetCfgVarFloat(MAX_Y_TABLE_NET), // y <= 76.0f
    },
};

//void CTennisTable::RegisterPlanes(
//								  CTennisPhysics* physics
//								  )
//{
//	matrix4 bound;
//	f32* m = bound.pointer();
//
//	for( u32 i = 0; i< sizeof(g_PlanesTable)/sizeof(g_PlanesTable[0]); i++)
//	{
//		memcpy( m, g_BoundsTable[i], 16*sizeof(f32) );
//		CPhysicsPlane plane(
//			g_PlanesTable[i][0],
//			g_PlanesTable[i][1],
//			bound
//			);
//		physics->AddPhysicsPlane( plane );
//	}
//}

bool CTennisTable::LoadModel(
    ISceneNode* parent,
	ISceneManager *pSM,
	IVideoDriver *pVideoDriver
	)
{
    const char* tex = GetCfgVarStr( FILE_TABLE_TEXTURE );
    m_pTexTable = pVideoDriver->getTexture( tex );

    tex = GetCfgVarStr( FILE_FENCE_TEXTURE );
    m_pTexFence = pVideoDriver->getTexture( tex );

#ifndef USE_WILSON_TABLE
 //   const char* mesh = GetCfgVarStr( FILE_TABLE_MESH );
	//if( !( m_pTableMesh = pSM->getMesh( mesh ) ) ||
	//	!( m_pTableNode = pSM->addAnimatedMeshSceneNode(
 //           m_pTableMesh, this
 //           ) )
 //      )
	//	return false;

	const char* Netmesh = GetCfgVarStr( FILE_TABLE_NET_MESH );
	m_pTableNetMesh = pSM->getMesh( Netmesh );
	const char* texNet = GetCfgVarStr( FILE_TABLE_NET_TEXTURE );
	ITexture* m_pTexNetTable = pVideoDriver->getTexture( texNet );
	//vector3df scale( fScaleX, fScaleY, fScaleZ );
	vector3df scale( 1.0f, 1.0f, 1.0f );

	vector3df pos[] = { vector3df(0, 0, 0)
		, vector3df(0, 0, -940)
		, vector3df(-470, 0, -470)
		, vector3df(470, 0, -470)
	};
	vector3df rot[] = { vector3df(0, 0, 0)
		, vector3df(0, 0, 0)
		, vector3df(0, 90, 0)
		, vector3df(0, 90, 0)
	};

	for ( int i = 0; i < NET_COUNT; i++ )
	{
		m_pTableNetNode[i] = pSM->addAnimatedMeshSceneNode( m_pTableNetMesh, this );

		m_pTableNetNode[i]->setScale( scale );
		m_pTableNetNode[i]->setMaterialTexture( 0, m_pTexNetTable );
		m_pTableNetNode[i]->setMaterialFlag( EMF_LIGHTING, false );
		m_pTableNetNode[i]->getMaterial( 0 ).MaterialType = EMT_TRANSPARENT_ADD_COLOR;
		m_pTableNetNode[i]->setVisible( true );

		m_pTableNetNode[i]->setPosition( pos[i] );
		m_pTableNetNode[i]->setRotation( rot[i] );
	}

	//aabbox3d<f32> bb = m_pTableNode->getBoundingBox();
 //   vector3df pos = m_pTableNode->getPosition();
 //   m_pTableNode->setPosition( pos );
    //pos += vector3df( 0, 0, -bb.MaxEdge.Y );
#if 0    
	f32 fmin = GetCfgVarFloat( MIN_X_TABLE_NET );
	f32 fmax = GetCfgVarFloat( MAX_X_TABLE_NET );
	f32 fLenX = fmax - fmin;

	fmin = 0; // GetCfgVarFloat( MIN_Y_TABLE );
	fmax = GetCfgVarFloat( MAX_Y_TABLE_NET );
	f32 fLenY = fmax - fmin;

	fmin = GetCfgVarFloat( MIN_Z_TABLE );
	fmax = GetCfgVarFloat( MAX_Z_TABLE );
	f32 fLenZ = fmax - fmin;

    f32 fScaleX = fLenX/( bb.MaxEdge.X - bb.MinEdge.X );
	f32 fScaleY = fLenY/( bb.MaxEdge.Y - bb.MinEdge.Y );
    f32 fScaleZ = fLenZ/( bb.MaxEdge.Z - bb.MinEdge.Z );
#endif
    //m_pTableNode->setScale( scale );
	//m_pTableNetNode->setPosition( pos );

	//m_pTableNode->setMaterialFlag( EMF_LIGHTING, false );
	//
	//m_pTableNode->setMaterialTexture(
 //       0, m_pTexTable
	//	);

#ifdef USE_SHADOWVOLUME
//	m_pTableNode->addShadowVolumeSceneNode();
	m_pTableNetNode->addShadowVolumeSceneNode();
#endif
//    m_pTableNode->setLoopMode( false );
//	m_pTableNode->setVisible( true );
#endif

//	m_pTableNode->setVisible( false );

    //m_pFenceMesh = pSM->getMesh( "../../media/weilan.md2" );
    //m_pFenceMeshNode = pSM->addAnimatedMeshSceneNode(
    //    m_pFenceMesh, parent );
    //bb = m_pFenceMeshNode->getBoundingBox();
    //pos = m_pFenceMeshNode->getPosition();
    //m_pFenceMeshNode->setPosition( pos );

    //fLenX = 150.f * 4.5;
    //fLenY = 50;
    //fLenZ = 270.f * 4.5;
    //fScaleX = fLenX/( bb.MaxEdge.X - bb.MinEdge.X );
    //fScaleY = fLenY/( bb.MaxEdge.Y - bb.MinEdge.Y );
    //fScaleZ = fLenZ/( bb.MaxEdge.Z - bb.MinEdge.Z );    
    //m_pFenceMeshNode->setScale( vector3df( fScaleX, fScaleY, fScaleZ ) );

    //ITexture* pText = pVideoDriver->getTexture( "../../media/weilan.tga" );
    //m_pFenceMeshNode->setMaterialFlag( EMF_LIGHTING, false );
    //m_pFenceMeshNode->setMaterialTexture( 0, pText );

    //m_pFenceMeshNode->setVisible( true );
    //m_pFenceMeshNode->setLoopMode( true );

	return true;
}

void CTennisTable::OnAnimate(
        u32 uTime
        )
{
	ISceneNode::OnAnimate(uTime);

#ifdef _ENABLE_SCROLLING_AD_
	static const float addrs[4][6] =
	{
		{ 1.00f, 0.95f, 0.90f, 0.85f, 0.80f, 0.75f, },
		{ 0.75f, 0.70f, 0.65f, 0.60f, 0.55f, 0.50f, },
		{ 0.50f, 0.45f, 0.40f, 0.35f, 0.30f, 0.25f, },
		{ 0.25f, 0.20f, 0.15f, 0.10f, 0.05f, 0.00f, },
	};
	static bool bHold = true;
	static u32 uBegin = uTime;
	static u32 index_ad = 0;
	if( bHold )
	{
		if( ( uTime - uBegin ) <= 5000 ) return;

		uBegin = uTime;
		bHold = false;
		index_ad++;
		index_ad %= 4;
	}

	u32 utmp = ( uTime - uBegin )/100;
	utmp %= 6;
	if( utmp == 5 )
	{
		bHold = true;
		uBegin = uTime;
	}

	float v = addrs[index_ad][utmp];
	m_meshFence[0].TCoords.Y = v+0.25f;
	m_meshFence[1].TCoords.Y = v+0.25f;
	m_meshFence[2].TCoords.Y = v+0.25f;
	m_meshFence[3].TCoords.Y = v+0.25f;

	m_meshFence[4].TCoords.Y = v;
	m_meshFence[5].TCoords.Y = v;
	m_meshFence[6].TCoords.Y = v;
	m_meshFence[7].TCoords.Y = v;

	m_meshFence[8].TCoords.Y = v;
	m_meshFence[9].TCoords.Y = v;
	m_meshFence[10].TCoords.Y = v;
	m_meshFence[11].TCoords.Y = v;

	m_meshFence[12].TCoords.Y = v+0.25f;
	m_meshFence[13].TCoords.Y = v+0.25f;
	m_meshFence[14].TCoords.Y = v+0.25f;
	m_meshFence[15].TCoords.Y = v+0.25f;

	m_meshFence[16].TCoords.Y = v+0.25f;
	m_meshFence[17].TCoords.Y = v;
	m_meshFence[18].TCoords.Y = v;
	m_meshFence[19].TCoords.Y = v+0.25f;
#endif
}

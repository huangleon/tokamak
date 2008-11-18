
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

#ifndef _PING_PANG_TABLE_H
#define _PING_PANG_TABLE_H

#include <irrlicht.h>
//#define _ENABLE_SCROLLING_AD_

using irr::u32;
using irr::u16;
using irr::s32;
using irr::f32;
using irr::scene::ISceneNode;
using irr::scene::ISceneManager;
using irr::video::IVideoDriver;
using irr::core::aabbox3d;
using irr::video::SMaterial;
using irr::video::S3DVertex;
using irr::video::ITexture;
using irr::scene::IAnimatedMesh;
using irr::scene::IAnimatedMeshSceneNode;

class CTennisPhysics;

class CTennisTable
	: public ISceneNode
{
public:
	CTennisTable(
        ISceneNode* parent,
        ISceneManager* mgr,
        s32 id
        );

	virtual ~CTennisTable();

	//void RegisterPlanes(
	//	CTennisPhysics* physics
	//	);

    bool LoadModel(
        ISceneNode* parent,
        ISceneManager *pSceneMngr,
        IVideoDriver *pVideoDriver
        );

#ifndef USE_WILSON_TABLE
	ISceneNode* getTableNetNode(int i) const { return m_pTableNetNode[i]; }
#endif

private:
	aabbox3d<f32> m_AABox;
	SMaterial m_Material;

	static S3DVertex g_vbTable[8];
	static S3DVertex g_vbTableWhiteBar[12];
	static S3DVertex g_vbTableBase[8];
	static S3DVertex g_vbTableNet[8];

    ITexture * m_pTexTable;

#ifndef USE_WILSON_TABLE
	IAnimatedMesh* m_pTableMesh;
	IAnimatedMeshSceneNode* m_pTableNode;

	// use 4 different net to fence
	IAnimatedMesh* m_pTableNetMesh;
	enum {
		NET_COUNT = 4
	};
	IAnimatedMeshSceneNode* m_pTableNetNode[NET_COUNT];

	IAnimatedMesh* m_pFenceMesh;
	IAnimatedMeshSceneNode* m_pFenceMeshNode;
#endif

    // using Wilson's table mesh
#ifdef USE_WILSON_TABLE
    S3DVertex m_meshTable[28];
    u16 m_indTable[46*3];
#endif

#ifdef USE_WILSON_FENCE
#ifdef _ENABLE_SCROLLING_AD_
    S3DVertex m_meshFence[20];
    u16 m_indFence[16*3];
    ITexture * m_pTexFence;
#else
    S3DVertex m_meshFence[12+3];
    u16 m_indFence[16*3];
    ITexture * m_pTexFence;
#endif
#endif

#ifdef USE_WILSON_ROOM
    S3DVertex m_meshStage[84];
    u16 m_indStage[480];
    ITexture * m_pTexStage;
#endif

public:
    void OnAnimate(
        u32 uTime
        );

public:
	virtual const
    aabbox3d<f32>& getBoundingBox() const
	{
		return m_AABox;
	}

	virtual u32 getMaterialCount()
	{
		return 1;
	}

	virtual SMaterial& getMaterial(
        u32 i
        )
	{
		return m_Material;
	}	

    virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}

	virtual void render();
};
extern CTennisTable* g_TennisTable;

#endif // _PING_PANG_TABLE_H

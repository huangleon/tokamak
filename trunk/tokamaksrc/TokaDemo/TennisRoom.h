
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

#ifndef _PING_PANG_ROOM_H_
#define _PING_PANG_ROOM_H_

#include <irrlicht.h>

using irr::f32;
using irr::u16;
using irr::s32;
using irr::u32;
using irr::scene::ISceneNode;
using irr::scene::ISceneManager;
using irr::core::aabbox3d;
using irr::video::S3DVertex;
using irr::video::SMaterial;
using irr::scene::IAnimatedMesh;
using irr::scene::IAnimatedMeshSceneNode;
using irr::video::ITexture;

class CTennisPhysics;

class CTennisRoom
: public ISceneNode
{
	aabbox3d<f32> Box;
	static S3DVertex g_vbRoom[8];
	static S3DVertex g_vbRoom2[24];
	SMaterial Material;

    static S3DVertex g_vbStages[20][4];
    static u16 g_ibStages[20][12];
    static bool g_bGeomReady;
    static void SetupStageGeom();

    static S3DVertex g_vbFence[8];

#ifdef USE_WILSON_ROOM
    ITexture *m_pTexGround;
#else
    IAnimatedMesh* m_pSceneMesh;
	IAnimatedMeshSceneNode* m_pSceneNode;
    ITexture *m_pTexScene;
    IAnimatedMesh* m_pSceneMeshEx;
	IAnimatedMeshSceneNode* m_pSceneNodeEx;
    ITexture *m_pTexSceneEx;
#endif

public:
	CTennisRoom(
        ISceneNode* parent,
        ISceneManager* mgr,
        s32 id
        );
	virtual ~CTennisRoom();

	//void RegisterPlanes(
	//	CTennisPhysics* physics
	//	);

	ISceneNode* getSceneNode() const { return m_pSceneNode; }

	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}

	virtual void render();

	virtual const
    aabbox3d<f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual u32 getMaterialCount()
	{
		return 1;
	}

	virtual SMaterial& getMaterial(
        u32 i
        )
	{
		return Material;
	}	
};

extern CTennisRoom* g_TennisRoom;
#endif //_PING_PANG_ROOM_H_

#pragma once
#include <irrlicht.h>
#include "CCameraMayaSceneNode.h"
//#include "TennisBall.h"

using irr::u32;
using irr::s32;
using irr::SEvent;
using irr::scene::ISceneNode;
using irr::scene::ISceneManager;
using irr::IrrlichtDevice;

class CTestManager :
	public irr::scene::CCameraMayaSceneNode
{
public:
	CTestManager(ISceneNode* parent, ISceneManager* mgr, s32 id);
public:
	virtual ~CTestManager(void);
	virtual bool OnEvent(SEvent event);

	IrrlichtDevice* m_pDevice;
	u32 m_speed;
//	CTennisBall* m_pBall;
};

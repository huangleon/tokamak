// TestScene.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "include.h"
#include "TestManager.h"
#include "TennisRoom.h"
#include "TennisTable.h"
#include "PingPangMeshLoader.h"
#include "utility/TokaPhysics.h"
#include "utility/GameLog.h"
#include "RemoteController/RemoterFactory.h"
#include "RemoteMap/RMManager.h"
#include "TennisCfg.h"

#define Xoff (-200.0f)
#define Yoff (+150.0f)
#define Zoff (+220.0f)

#define XMARGIN 5
#define YMARGIN 5

using irr::video::EDT_DIRECT3D9;
using irr::video::EDT_OPENGLES;
using irr::core::dimension2d;
using irr::IrrlichtDevice;
using irr::createDevice;
using irr::gui::IGUIEnvironment;
using irr::core::rect;
using irr::core::PI;
using irr::video::SColor;
using irr::core::stringw;

using TM::Physics::CTokaPhysics;
using TM::Physics::TokaBodyParam;
using TM::Physics::E_CUBE_BODY;
using TM::Physics::E_SPHERE_BODY;
using TM::Physics::TokaPhyInitParam;

using TM::E_SMB_REMOTE;
using TM::RemoteMap::CRemoteMapManager;
using TM::CRemoterFactory;

CTennisTable* g_TennisTable;
CTennisRoom* g_TennisRoom;

int main(int argc, char* argv[])
{
	CTennisCfgVars tennisCfg;
	LoadCfgFile( CFG_FILE_PATH, &tennisCfg );

	CRemoterFactory m_remoteManager;
	CRemoteMapManager m_remoteMapper(E_SMB_REMOTE);

	//CSampleCar sc;
	//
	//sc.Reset();

	ENABLE_LOG(1);
	ENABLE_LOG(2);

	IrrlichtDevice *device =
		createDevice( EDT_DIRECT3D9, dimension2d<s32>(1280, 720),
			dimension2d<s32>(1280, 720),16,
			false, false, false, 0);

	device->setWindowCaption(L"Test Scene");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IVideoDriver* vd = device->getVideoDriver();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	CPingPangMeshLoader *pMD2MeshLoader = new CPingPangMeshLoader(driver);

	smgr->addExternalMeshLoader(pMD2MeshLoader);
	pMD2MeshLoader->drop();

	guienv->addStaticText(L"Test Scene",
		rect<int>(10,10,260,22), true);

	// CAMERA
//	ICameraSceneNode* cam = smgr->addCameraSceneNodeMaya();
	CTestManager* cam = new CTestManager( smgr->getRootSceneNode(), smgr, 1 );
	cam->m_pDevice = device;
	device->setEventReceiver( cam );
	smgr->setActiveCamera( cam );
	cam->drop();

	cam->setFOV( PI/ 8.0f );
	cam->setNearValue( GetCfgVarFloat(CAMERA_NEAR_VALUE) );
	cam->setFarValue( GetCfgVarFloat(CAMERA_FAR_VALUE) );
	cam->setAspectRatio( 1280.0f / 720.0f );

	// Point: [-520.329, 792.506, -2058.37]
	// Point: [-2.86412, -67.1384, -27.8035]
	//cam->setPosition(vector3df(GetCfgVarFloat(MAX_X_TABLE) + 200, GetCfgVarFloat(MAX_Y_TABLE) + 100, 0));
	//cam->setTarget(vector3df(0, GetCfgVarFloat(MAX_Y_TABLE), 0));
	cam->setPosition( vector3df(-520.329, 792.506, -2058.37) );
	cam->setTarget( vector3df(-2.86412, -67.1384, -27.8035) );
	/////////////////////////////////////////////////////////////

	// ROOM
	CTennisRoom* pRoom = new CTennisRoom( smgr->getRootSceneNode(), smgr, 2 );
	pRoom->drop();
	g_TennisRoom = pRoom;
	/////////////////////////////////////////////////////////////

	// Table
	CTennisTable* pTable = new CTennisTable( smgr->getRootSceneNode(), smgr, 3);
	pTable->LoadModel( smgr->getRootSceneNode(), smgr, vd );
	pTable->drop();
	g_TennisTable = pTable;
	/////////////////////////////////////////////////////////////

#if 0
	// Prepare physics and ball
	CTennisPhysics* pPhysics = CTennisPhysics::GetPhysicsEngine();
	u32 uTime = device->getTimer()->getTime();
	float g = GetCfgVarFloat( BALL_GRAVITY_ACC );
	float r = GetCfgVarFloat( BALL_RADIUS );

	static vector3df p( 0.0f, 100.0f,  140.0f );
	static vector3df v( 0.0f, -90.0f, -320.0f );
	vector3df a( 0.0f, g, 0.0f );
	pPhysics->ResetInitialState(
		p, v, a, r, uTime
		);
	vector3df src, dst;
	
	// src.Y should be player's hand height
	src.set(
		50,
		180.0f,
		GetCfgVarFloat( MAX_Z_HITRANGE ) + 10
		);
	dst.set(
		-( GetCfgVarFloat( MAX_X_TABLE ) - 50.0f),
		0.f,
		-GetCfgVarFloat( MAX_Z_TABLE ) + 90
		); 
#endif
	// Debug for tokamak
	TokaPhyInitParam initParam;
	initParam.rbCount = CTokaPhysics::CUBECOUNT;
	initParam.gravity = vector3df(0, -9.8f, 0);
	CTokaPhysics::getInstance()->InitTokaPhysics( initParam );
	irr::scene::ISceneNode *CubeNode[CTokaPhysics::CUBECOUNT];

	vector3df pos[] = { vector3df(-100.0f, 50.f, -600.f)
		, vector3df(-100.0f, 150.f, -600.f)
		, vector3df(100.f, 250.f, -600.f)
		, vector3df(.0f, 350.f, -500.f)
		, vector3df(100.0f, 350.f, -500.f)
		, vector3df(-100.0f, 350.f, -500.f)
	};
	vector3df tmppos;
	for ( int i = 0; i < CTokaPhysics::CUBECOUNT; i++)
	{
		//CubeNode[i] = new PhysicsCubeNode(
		//	smgr->getRootSceneNode(), smgr, 666);
//		CubeNode[i] = smgr->addCubeSceneNode( 50 );
		CubeNode[i] = smgr->addSphereSceneNode ( 50 / 2.f );
		CubeNode[i]->setMaterialFlag( irr::video::EMF_LIGHTING, false );
		//		CubeNode[i]->setMaterialTexture(0, driver->getTexture("../../media/t351sml.jpg"));
		CubeNode[i]->setMaterialTexture(0, driver->getTexture("../../media-tokamak/earth.bmp"));
		CubeNode[i]->getMaterial(0).MaterialType = irr::video::EMT_SOLID;
		tmppos = pos[0];
		tmppos.Y += i * 50.f;
		CubeNode[i]->setPosition( tmppos );
		CubeNode[i]->setRotation( vector3df( 0, 0, -10 ) );

		TokaBodyParam bdparam;
		bdparam.bodyType = E_SPHERE_BODY;
//		bdparam.bodyType = E_CUBE_BODY;
		bdparam.bodyMass = 100.f;
		bdparam.angDamping = .001f;
		bdparam.linDamping = .0f;
		bdparam.matIndex = 0;
		bdparam.body_x = 50.0f;
		bdparam.body_y = 50.0f;
		bdparam.body_z = 50.0f;
		CTokaPhysics::getInstance()->attachNode( CubeNode[i], bdparam );
	}

	// Remote
	m_remoteManager.addRemoteFilter( "00:12:6f" );
	// 50 Hz
	m_remoteManager.presetRemoteFreq(0);
	m_remoteManager.presetRemoteSensorRange(0);

	m_remoteManager.attachRemoteEventReceiver( &m_remoteMapper );
	m_remoteManager.attachRemoteEEventReceiver( &m_remoteMapper );

	if ( m_remoteManager.CreateRemoteControllers() )
	{
		m_remoteMapper.createAnalyzers( m_remoteManager.availableRemoteCount() );
	}
	/*
	We have done everything, so lets draw it. We also write the current
	frames per second and the name of the driver to the caption of the
	window.
	*/
	int lastFPS = -1;

	while(device->run())
	{
		/*
		Anything can be drawn between a beginScene() and an endScene()
		call. The beginScene clears the screen with a color and also the
		depth buffer if wanted. Then we let the Scene Manager and the
		GUI Environment draw their content. With the endScene() call
		everything is presented on the screen.
		*/

		m_remoteManager.ProcessRemoteInput();
		TM::RemoteMap::AnalyzeResult ar;
		m_remoteMapper.getAnalyzeResult( 0, ar );

		if ( ar.angleY < 0 )
		{
			std::cout << ar.angleY << std::endl;
			CTokaPhysics::getInstance()->pushBody( 0, fabs(ar.angleY) / 100.f );
		}
		else if ( ar.angleY > 0 )
		{
			std::cout << ar.angleY << std::endl;
			CTokaPhysics::getInstance()->pushBody( 1, fabs(ar.angleY) / 100.f );
		}
		else
		{
//			CTokaPhysics::getInstance()->pushBody( -1 );
		}

		if ( ar.angleX < 0 )
		{
			CTokaPhysics::getInstance()->pushBody( 3, fabs(ar.angleX) / 100.f );
		}
		else if ( ar.angleX > 0 )
		{
			CTokaPhysics::getInstance()->pushBody( 2, fabs(ar.angleX) / 100.f );
		}
		else
		{
//			CTokaPhysics::getInstance()->pushBody( -1 );
		}

		CTokaPhysics::getInstance()->stepForward( device->getTimer()->getTime() );

		driver->beginScene(true, true, SColor(255,100,101,140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			stringw tmp(L"Movement Example - Irrlicht Engine [");
			tmp += driver->getName();
			tmp += L"] fps: "; 
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
	}

	CTokaPhysics::getInstance()->ReleaseTokaPhysics();
	CTokaPhysics::getInstance()->releaseInstance();
	
	device->drop();
	UnloadCfgFile();

	return 0;
}


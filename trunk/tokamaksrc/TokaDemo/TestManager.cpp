#include "TestManager.h"

#include <iostream>
//#include "TennisPhysics.h"
//#include "TennisTable.h"
//#include "TennisRoom.h"
#include "utility/irrUtility.h"
#include "utility/TokaPhysics.h"
#include "utility/GameLog.h"

using irr::s32;
using irr::EET_KEY_INPUT_EVENT;
using irr::EET_MOUSE_INPUT_EVENT;
using irr::EMIE_LMOUSE_PRESSED_DOWN;
using irr::EMIE_LMOUSE_LEFT_UP;
using irr::KEY_RETURN;
using irr::KEY_KEY_S;
using irr::KEY_KEY_F;
using irr::KEY_KEY_B;
using irr::KEY_KEY_A;
using irr::KEY_UP;
using irr::KEY_DOWN;
using irr::KEY_LEFT;
using irr::KEY_RIGHT;
using GameUtility::physics::CTokaPhysics;

const f32 fspeed[] = {0.001f, 0.01f, 0.05f, 0.1f, 0.3f, 0.7f, 1.0f, 1.5f, 2.0f, 3.0f};
const int SPDSIZE = 10;
CTestManager::CTestManager(ISceneNode* parent, ISceneManager* mgr, s32 id)
:CCameraMayaSceneNode(parent, mgr, id, -1500, 200, 500),
m_speed(6)
{
}

CTestManager::~CTestManager(void)
{
}
bool CTestManager::OnEvent(SEvent event)
{
	int i = 0;
	static bool bkeyS = false;
	static bool bkeyF = false;
	static bool bkeyB = false;
	
	static bool bkeyLeft = false;
	static bool bkeyRight = false;
	static bool bkeyUp = false;
	static bool bkeyDown = false;
	static bool bkeyA = false;

	switch (event.EventType)
	{
	case EET_KEY_INPUT_EVENT:

		if ( event.KeyInput.Key == KEY_RETURN && !event.KeyInput.PressedDown )
		{
			std::cout << m_pDevice->getSceneManager()->getActiveCamera()->getPosition() << std::endl;
			std::cout << m_pDevice->getSceneManager()->getActiveCamera()->getTarget() << std::endl;
		}
		
#if 0
		if (!bkeyS && event.KeyInput.Key == KEY_KEY_S && event.KeyInput.PressedDown)
		{
			bkeyS = true;
//			std::cout << "ks..." << std::endl;
			if (m_speed > 0)
				--m_speed;
			m_pDevice->getTimer()->setSpeed(fspeed[m_speed]);
		}
		if (bkeyS && event.KeyInput.Key == KEY_KEY_S && !event.KeyInput.PressedDown)
		{
			bkeyS = false;
		}
		
		if (!bkeyF && event.KeyInput.Key == KEY_KEY_F && event.KeyInput.PressedDown)
		{
			bkeyF = true;
//			std::cout << "kf..." << std::endl;
			if (m_speed < SPDSIZE - 1)
				++m_speed;
			m_pDevice->getTimer()->setSpeed(fspeed[m_speed]);
		}
		if (bkeyF && event.KeyInput.Key == KEY_KEY_F && !event.KeyInput.PressedDown)
		{
			bkeyF = false;
		}
		if (!bkeyB && event.KeyInput.Key == KEY_KEY_B && event.KeyInput.PressedDown)
		{
			bkeyB = true;
			CTennisTrack& track = m_pBall->GetTrack();
			f32 fTimeElapse = m_pDevice->getTimer()->getTime() / 1000.0f - track.GetBaseTime();
			CTennisPhysics* pPhysics = CTennisPhysics::GetPhysicsEngine();
			
			track.setWait(false);
			if (fTimeElapse < pPhysics->GetTrackPeakDeltaT(track))
				m_pBall->GetTrack().SetBaseTime(pPhysics->GetTrackPeakDeltaT(track), true);
			else
				m_pBall->GetTrack().SetBaseTime(m_pDevice->getTimer()->getTime()/ 1000.f, true);
		}
		if (bkeyB && event.KeyInput.Key == KEY_KEY_B && !event.KeyInput.PressedDown)
		{
			bkeyF = false;
		}
#endif

		//////////////////////////////////////////////////////////////////////////
		// left key
		if ( !bkeyLeft && event.KeyInput.Key == KEY_LEFT && event.KeyInput.PressedDown )
		{
			vector3df rottmp( 0, 0, 1 ), rottable, rotroom;
#if 0
			// Test code of rotating floor
			vector3df pos;
			rotroom = g_TennisRoom->getSceneNode()->getRotation();
			rotroom += rottmp;
			g_TennisRoom->getSceneNode()->setRotation( rotroom );
			for ( int i = 0; i < 4; i++ )
			{
				rottable = g_TennisTable->getTableNetNode(i)->getRotation();
				rottable += rottmp;
				g_TennisTable->getTableNetNode(i)->setRotation( rottable );

				if ( i > 1 )
				{
					pos = g_TennisTable->getTableNetNode(i)->getPosition();
					GameUtility::rotateVectorByVector( pos, vector3df(0, 0, 0), vector3df(0, 0, -1), 1 );
					g_TennisTable->getTableNetNode(i)->setPosition( pos );
				}
			}
			CTokaPhysics::Instance()->rotateAnimateBody( true, rotroom );
#else
			// Test code of push 
			CTokaPhysics::Instance()->pushBody(2, 1.f);
#endif

			bkeyLeft = true;
		}
		if ( event.KeyInput.Key == KEY_LEFT && !event.KeyInput.PressedDown )
		{
			CTokaPhysics::Instance()->pushBody(-1, 1.f);
			bkeyLeft = false;
		}

		// right key
		if ( !bkeyRight && event.KeyInput.Key == KEY_RIGHT && event.KeyInput.PressedDown )
		{
			vector3df rottmp( 0, 0, -1 ), rottable, rotroom;
#if 0
			// Test code of rotating floor
			vector3df pos;
			rotroom = g_TennisRoom->getSceneNode()->getRotation();
			rotroom += rottmp;
			g_TennisRoom->getSceneNode()->setRotation( rotroom );
			for ( int i = 0; i < 4; i++ )
			{
				rottable = g_TennisTable->getTableNetNode(i)->getRotation();
				rottable += rottmp;
				g_TennisTable->getTableNetNode(i)->setRotation( rottable );

				if ( i > 1 )
				{
					pos = g_TennisTable->getTableNetNode(i)->getPosition();
					GameUtility::rotateVectorByVector( pos, vector3df(0, 0, 0), vector3df(0, 0, -1), -1 );
					g_TennisTable->getTableNetNode(i)->setPosition( pos );
				}
			}
			CTokaPhysics::Instance()->rotateAnimateBody( false, rotroom );
#else
			// Test code of push
			CTokaPhysics::Instance()->pushBody(3);
#endif
			bkeyRight = true;
		}
		if ( event.KeyInput.Key == KEY_RIGHT && !event.KeyInput.PressedDown )
		{
			CTokaPhysics::Instance()->pushBody(-1);
			bkeyRight = false;
		}
		// up key
		if ( !bkeyUp && event.KeyInput.Key == KEY_UP && event.KeyInput.PressedDown )
		{
			CTokaPhysics::Instance()->pushBody(0);
			bkeyUp = true;
		}
		if ( event.KeyInput.Key == KEY_UP && !event.KeyInput.PressedDown )
		{
			CTokaPhysics::Instance()->pushBody(-1);
			bkeyUp = false;
		}

		// down key
		if ( !bkeyDown && event.KeyInput.Key == KEY_DOWN && event.KeyInput.PressedDown )
		{
			CTokaPhysics::Instance()->pushBody(1);
			bkeyDown = true;
		}
		if ( event.KeyInput.Key == KEY_DOWN && !event.KeyInput.PressedDown )
		{
			CTokaPhysics::Instance()->pushBody(-1);
			bkeyDown = false;
		}

		// A key
		if ( !bkeyA && event.KeyInput.Key == KEY_KEY_A && event.KeyInput.PressedDown )
		{
			CTokaPhysics::Instance()->pushBody(4);
			bkeyA = true;
		}
		if ( event.KeyInput.Key == KEY_KEY_A && !event.KeyInput.PressedDown )
		{
			CTokaPhysics::Instance()->pushBody(-1);
			bkeyA = false;
		}

		break;
	default:
		break;
	}

	return CCameraMayaSceneNode::OnEvent(event);
}
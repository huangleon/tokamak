
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

#ifndef _PING_PANG_INCLUDE_H_
#define _PING_PANG_INCLUDE_H_

#ifdef _IRR_WINDOWS_
//#define _CRTDBG_MAP_ALLOC 
//#include  "crtdbg.h"
#endif


#include <assert.h>
#include <iostream>

#include <irrlicht.h>
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

//using namespace irr;
//using namespace core;
//using namespace scene;
//using namespace video;
//using namespace io;
//using namespace gui;

#include "TennisCfg.h"

/*
 Option for model themes:
 0: Wilson's theme, default
 1: Boy
 2: Q-like
 */
#define MODEL_THEME_1

//#define USE_WILSON_ROOM
//#define USE_WILSON_TABLE
#define USE_WILSON_FENCE

#define DISABLE_REPLAY 1

// _USE_ZTHREAD macro control zthread linkable
//
//#define _USE_ZTHREAD

#ifdef _IRR_WINDOWS_
//#define USE_IRRKLANG
#endif

#ifdef USE_IRRKLANG
	#include <irrKlang.h>	// problem here? go to http://www.ambiera.com/irrklang and download
							// the irrKlang library or undefine USE_IRRKLANG at the beginning
							// of this file.
	#ifdef _IRR_WINDOWS_
	#pragma comment (lib, "irrKlang.lib")
	#endif
#endif

#ifdef  _IRR_WINDOWS_
//#define USE_SHADOWVOLUME
#else
//#define _OLO_TOP
#endif

#endif //_PING_PANG_INCLUDE_H_

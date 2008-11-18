
/*-----------------------------------------------------------------------------
*
*  This file is part of "Tennis game", which is based on Irrlicht Engine.
*
*  Revise History:
*    Date          Author           Comment
*    2008-08-10    Hu, weixiong     Initial version.
*    2008-08-16    Hu, weixiong     Added support for string configuration.
*
*  Copyright (c) 2007 Intel Corporation.
*
*-----------------------------------------------------------------------------
*/

#include "TennisCfg.h"

const dimension2di RENDER_SIZE(1280, 720);

#ifdef WIN32
#include <windows.h>
const irr::core::dimension2di SCREEN_RESOLUTION
(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#endif

CONSTCFGTYPE MIN_X_TABLE = "MIN_X_TABLE";                                        
CONSTCFGTYPE MIN_Y_TABLE = "MIN_Y_TABLE";                                        
CONSTCFGTYPE MIN_Z_TABLE = "MIN_Z_TABLE";                                        
CONSTCFGTYPE MAX_X_TABLE = "MAX_X_TABLE";                                        
CONSTCFGTYPE MAX_Y_TABLE = "MAX_Y_TABLE";                                        
CONSTCFGTYPE MAX_Z_TABLE = "MAX_Z_TABLE";                                        
CONSTCFGTYPE MIN_X_TABLE_BASE = "MIN_X_TABLE_BASE";                              
CONSTCFGTYPE MIN_Y_TABLE_BASE = "MIN_Y_TABLE_BASE";                              
CONSTCFGTYPE MIN_Z_TABLE_BASE = "MIN_Z_TABLE_BASE";                              
CONSTCFGTYPE MAX_X_TABLE_BASE = "MAX_X_TABLE_BASE";                              
CONSTCFGTYPE MAX_Y_TABLE_BASE = "MAX_Y_TABLE_BASE";                              
CONSTCFGTYPE MAX_Z_TABLE_BASE = "MAX_Z_TABLE_BASE";                              
CONSTCFGTYPE MIN_X_TABLE_NET = "MIN_X_TABLE_NET";                                
CONSTCFGTYPE MIN_Y_TABLE_NET = "MIN_Y_TABLE_NET";                                
CONSTCFGTYPE MIN_Z_TABLE_NET = "MIN_Z_TABLE_NET";                                
CONSTCFGTYPE MAX_X_TABLE_NET = "MAX_X_TABLE_NET";                                
CONSTCFGTYPE MAX_Y_TABLE_NET = "MAX_Y_TABLE_NET";                                
CONSTCFGTYPE MAX_Z_TABLE_NET = "MAX_Z_TABLE_NET";                                
CONSTCFGTYPE MIN_X_ROOM = "MIN_X_ROOM";                                          
CONSTCFGTYPE MIN_Y_ROOM = "MIN_Y_ROOM";                                          
CONSTCFGTYPE MIN_Z_ROOM = "MIN_Z_ROOM";                                          
CONSTCFGTYPE MAX_X_ROOM = "MAX_X_ROOM";                                          
CONSTCFGTYPE MAX_Y_ROOM = "MAX_Y_ROOM";                                          
CONSTCFGTYPE MAX_Z_ROOM = "MAX_Z_ROOM";                                          
CONSTCFGTYPE MIN_X_STADIUM_BOT = "MIN_X_STADIUM_BOT";                            
CONSTCFGTYPE MIN_Z_STADIUM_BOT = "MIN_Z_STADIUM_BOT";                            
CONSTCFGTYPE MAX_X_STADIUM_BOT = "MAX_X_STADIUM_BOT";                            
CONSTCFGTYPE MAX_Z_STADIUM_BOT = "MAX_Z_STADIUM_BOT";                            
CONSTCFGTYPE MIN_X_STADIUM_TOP = "MIN_X_STADIUM_TOP";                            
CONSTCFGTYPE MIN_Z_STADIUM_TOP = "MIN_Z_STADIUM_TOP";                            
CONSTCFGTYPE MAX_X_STADIUM_TOP = "MAX_X_STADIUM_TOP";                            
CONSTCFGTYPE MAX_Z_STADIUM_TOP = "MAX_Z_STADIUM_TOP";                            
CONSTCFGTYPE MIN_Y_STADIUM = "MIN_Y_STADIUM";                                    
CONSTCFGTYPE MAX_Y_STADIUM = "MAX_Y_STADIUM";                                    
CONSTCFGTYPE BALL_RADIUS = "BALL_RADIUS";                                        
CONSTCFGTYPE BALL_GRAVITY_ACC = "BALL_GRAVITY_ACC";                              
CONSTCFGTYPE BALL_COLLISION_COEEF = "BALL_COLLISION_COEEF";
CONSTCFGTYPE BALL_FRICTION_COEEF = "BALL_FRICTION_COEEF";
CONSTCFGTYPE BALL_COLLISION_SPEED = "BALL_COLLISION_SPEED";
CONSTCFGTYPE BALL_COLLISION_START = "BALL_COLLISION_START";
CONSTCFGTYPE BALL_SERVE_COEEF = "BALL_SERVE_COEEF";
CONSTCFGTYPE BALL_SPEED_MAJOR1 = "BALL_SPEED_MAJOR1";
CONSTCFGTYPE BALL_SPEED_MAJOR2 = "BALL_SPEED_MAJOR2";
CONSTCFGTYPE BALL_SPEED_MAJOR3 = "BALL_SPEED_MAJOR3";
CONSTCFGTYPE BALL_SPEED_MAJOR4 = "BALL_SPEED_MAJOR4";
CONSTCFGTYPE BALL_SPEED_MAJOR5 = "BALL_SPEED_MAJOR5";
CONSTCFGTYPE BALL_SPEED_MAJOR6 = "BALL_SPEED_MAJOR6";
CONSTCFGTYPE BALL_SPEED_MINOR1 = "BALL_SPEED_MINOR1";
CONSTCFGTYPE BALL_SPEED_MINOR2 = "BALL_SPEED_MINOR2";
CONSTCFGTYPE BALL_SPEED_MINOR3 = "BALL_SPEED_MINOR3";
CONSTCFGTYPE BALL_SPEED_MINOR4 = "BALL_SPEED_MINOR4";
CONSTCFGTYPE BALL_SPEED_MINOR5 = "BALL_SPEED_MINOR5";
CONSTCFGTYPE BALL_SPEED_MINOR6 = "BALL_SPEED_MINOR6";
CONSTCFGTYPE BALL_SPIN_FACTOR1 = "BALL_SPIN_FACTOR1";
CONSTCFGTYPE BALL_SPIN_FACTOR2 = "BALL_SPIN_FACTOR2";
CONSTCFGTYPE BALL_SPIN_FACTOR3 = "BALL_SPIN_FACTOR3";
CONSTCFGTYPE BALL_TRAIL_RFACTOR = "BALL_TRAIL_RFACTOR";
CONSTCFGTYPE BALL_TRAIL_LENGTH = "BALL_TRAIL_LENGTH";
CONSTCFGTYPE BALL_TRAIL_FLENGTH = "BALL_TRAIL_FLENGTH";
CONSTCFGTYPE BALL_SPINEFFECT_WIDTH = "BALL_SPINEFFECT_WIDTH";
CONSTCFGTYPE BALL_SPINEFFECT_HEIGHT = "BALL_SPINEFFECT_HEIGHT";
CONSTCFGTYPE HITTIM_DURATION = "HITTIM_DURATION";                                
CONSTCFGTYPE Z_BACK_TOHIT = "Z_BACK_TOHIT,";                                    
CONSTCFGTYPE MAX_Z_HITBALL = "MAX_Z_HITBALL";                                    
CONSTCFGTYPE HIT_ACTIONTIME = "HIT_ACTIONTIME";                                  
CONSTCFGTYPE POSTHIT_BACKTIME = "POSTHIT_BACKTIME";                              
CONSTCFGTYPE POSTHIT_BACK_THRESHOLD = "POSTHIT_BACK_THRESHOLD";                  
CONSTCFGTYPE ACC_THRESHOLD = "ACC_THRESHOLD";                                    
CONSTCFGTYPE MAX_INTERVALTIME = "MAX_INTERVALTIME";                              
CONSTCFGTYPE MAX_Z_HITRANGE = "MAX_Z_HITRANGE";                                  
CONSTCFGTYPE MIN_Z_HITRANGE = "MIN_Z_HITRANGE";                                  
CONSTCFGTYPE STEP_Z = "STEP_Z";                                                  
CONSTCFGTYPE MAX_X_HITRANGE = "MAX_X_HITRANGE";                                  
CONSTCFGTYPE MIN_X_HITRANGE = "MIN_X_HITRANGE";                                  
CONSTCFGTYPE STEP_X = "STEP_X";                                                  
CONSTCFGTYPE MAX_Y_HITRANGE = "MAX_Y_HITRANGE";                                  
CONSTCFGTYPE MIN_Y_HITRANGE = "MIN_Y_HITRANGE";                                  
CONSTCFGTYPE STEP_Y = "STEP_Y";                                                  
CONSTCFGTYPE CAMERA_NEAR_VALUE = "CAMERA_NEAR_VALUE";                            
CONSTCFGTYPE CAMERA_FAR_VALUE = "CAMERA_FAR_VALUE";                              
CONSTCFGTYPE REPLAY_POSSIBILITY = "REPLAY_POSSIBILITY";                          
CONSTCFGTYPE CFG_INDEX_FLOAT_MAX = "CFG_INDEX_FLOAT_MAX";                        
CONSTCFGTYPE FILE_LOADINGSCREEN = "FILE_LOADINGSCREEN";                          
CONSTCFGTYPE FILE_LOADINGBAR = "FILE_LOADINGBAR";                                
CONSTCFGTYPE FILE_LOADINGPROGRESS = "FILE_LOADINGPROGRESS";                      
CONSTCFGTYPE FILE_SETUPINPUT = "FILE_SETUPINPUT";                                
CONSTCFGTYPE FILE_STARTBAR = "FILE_STARTBAR";                                    
CONSTCFGTYPE FILE_DIALOGQUIT = "FILE_DIALOGQUIT";                                
CONSTCFGTYPE FILE_FONT = "FILE_FONT";                                            
CONSTCFGTYPE FILE_TEXTURE_SCOREBAR = "FILE_TEXTURE_SCOREBAR";
CONSTCFGTYPE FILE_SCORE_FONT = "FILE_SCORE_FONT";                                
CONSTCFGTYPE FILE_SCORE_FONT2 = "FILE_SCORE_FONT2";                              
CONSTCFGTYPE FILE_BALL_TEXTURE = "FILE_BALL_TEXTURE";
CONSTCFGTYPE FILE_FLOOR_TEXTURE = "FILE_FLOOR_TEXTURE";                          
CONSTCFGTYPE FILE_RACKET_MESH = "FILE_RACKET_MESH";                              
CONSTCFGTYPE FILE_RACKET_MESH2 = "FILE_RACKET_MESH2";                            
CONSTCFGTYPE FILE_SCENE_MESH = "FILE_SCENE_MESH";                                
CONSTCFGTYPE FILE_SCENE_TEXTURE = "FILE_SCENE_TEXTURE";                          
CONSTCFGTYPE FILE_SCENE_MESH_EX = "FILE_SCENE_MESH_EX";                          
CONSTCFGTYPE FILE_SCENE_TEXTURE_EX = "FILE_SCENE_TEXTURE_EX";                    
CONSTCFGTYPE FILE_TABLE_MESH = "FILE_TABLE_MESH";                                
CONSTCFGTYPE FILE_TABLE_TEXTURE = "FILE_TABLE_TEXTURE";                          
CONSTCFGTYPE FILE_TABLE_NET_MESH = "FILE_TABLE_NET_MESH";                        
CONSTCFGTYPE FILE_TABLE_NET_TEXTURE = "FILE_TABLE_NET_TEXTURE";                  
CONSTCFGTYPE FILE_FENCE_TEXTURE = "FILE_FENCE_TEXTURE";                          
CONSTCFGTYPE FILE_FENCE_TEXTURE_1 = "FILE_FENCE_TEXTURE_1";                      
CONSTCFGTYPE FILE_FENCE_TEXTURE_2 = "FILE_FENCE_TEXTURE_2";                      
CONSTCFGTYPE FILE_RACKET_TEXTURE = "FILE_RACKET_TEXTURE";                        
CONSTCFGTYPE FILE_PLAYER_MESH_1 = "FILE_PLAYER_MESH_1";                          
CONSTCFGTYPE FILE_PLAYER_TEXTURE_1 = "FILE_PLAYER_TEXTURE_1";                    
CONSTCFGTYPE FILE_PLAYER_MESH_2 = "FILE_PLAYER_MESH_2";                          
CONSTCFGTYPE FILE_PLAYER_TEXTURE_2 = "FILE_PLAYER_TEXTURE_2";                    
CONSTCFGTYPE FILE_PLAYER_MESH_3 = "FILE_PLAYER_MESH_3";                          
CONSTCFGTYPE FILE_PLAYER_TEXTURE_3 = "FILE_PLAYER_TEXTURE_3";                    
CONSTCFGTYPE FILE_PLAYER_MESH_4 = "FILE_PLAYER_MESH_4";                          
CONSTCFGTYPE FILE_PLAYER_TEXTURE_4 = "FILE_PLAYER_TEXTURE_4";                    
CONSTCFGTYPE FILE_PLAYER_MESH_5 = "FILE_PLAYER_MESH_5";                          
CONSTCFGTYPE FILE_PLAYER_TEXTURE_5 = "FILE_PLAYER_TEXTURE_5";                    
CONSTCFGTYPE FILE_PLAYER_MESH_6 = "FILE_PLAYER_MESH_6";                          
CONSTCFGTYPE FILE_PLAYER_TEXTURE_6 = "FILE_PLAYER_TEXTURE_6";                    
CONSTCFGTYPE FILE_PLAYER_MESH_7 = "FILE_PLAYER_MESH_7";                          
CONSTCFGTYPE FILE_PLAYER_TEXTURE_7 = "FILE_PLAYER_TEXTURE_7";                    
CONSTCFGTYPE FILE_PLAYER_MESH_8 = "FILE_PLAYER_MESH_8";                          
CONSTCFGTYPE FILE_PLAYER_TEXTURE_8 = "FILE_PLAYER_TEXTURE_8";                    
CONSTCFGTYPE FILE_SOUND_START = "FILE_SOUND_START";                              
CONSTCFGTYPE FILE_SOUND_RAKETKA1 = "FILE_SOUND_RAKETKA1";                        
CONSTCFGTYPE FILE_SOUND_RAKETKA2 = "FILE_SOUND_RAKETKA2";                        
CONSTCFGTYPE FILE_SOUND_TABLE = "FILE_SOUND_TABLE";                              
CONSTCFGTYPE FILE_SOUND_BEEP = "FILE_SOUND_BEEP";                                
CONSTCFGTYPE FILE_SOUND_APPLAUSE = "FILE_SOUND_APPLAUSE";                        
CONSTCFGTYPE FILE_SOUND_OPENNING = "FILE_SOUND_OPENNING";                        
CONSTCFGTYPE FILE_SOUND_END = "FILE_SOUND_END";                                  
CONSTCFGTYPE FILE_INTRO_LOGO1 = "FILE_INTRO_LOGO1";                              
CONSTCFGTYPE FILE_INTRO_LOGO2 = "FILE_INTRO_LOGO2";                              
CONSTCFGTYPE FILE_MAINMENU_BACKGROUND = "FILE_MAINMENU_BACKGROUND";              
CONSTCFGTYPE FILE_MAINMENU_OPTION_START = "FILE_MAINMENU_OPTION_START";          
CONSTCFGTYPE FILE_MAINMENU_OPTION_START_FOCUSED = "FILE_MAINMENU_OPTION_START_FOCUSED";                                                                          
CONSTCFGTYPE FILE_MAINMENU_OPTION_EXIT = "FILE_MAINMENU_OPTION_EXIT";            
CONSTCFGTYPE FILE_MAINMENU_OPTION_EXIT_FOCUSED = "FILE_MAINMENU_OPTION_EXIT_FOCUSED";                                                                            
CONSTCFGTYPE FILE_MAINMENU_OPTION_SETUP_DISABLED = "FILE_MAINMENU_OPTION_SETUP_DISABLED";                                                                        
CONSTCFGTYPE FILE_MAINMENU_OPTION_REMOTER_DISABLED = "FILE_MAINMENU_OPTION_REMOTER_DISABLED";                                                                    
CONSTCFGTYPE FILE_MAINMENU_OPTION_ROLE_DISABLED = "FILE_MAINMENU_OPTION_ROLE_DISABLED";                                                                          
CONSTCFGTYPE FILE_MAINMENU_OPTION_SINGLE = "FILE_MAINMENU_OPTION_SINGLE";        
CONSTCFGTYPE FILE_MAINMENU_OPTION_SINGLE_FOCUSED = "FILE_MAINMENU_OPTION_SINGLE_FOCUSED";                                                                        
CONSTCFGTYPE FILE_MAINMENU_OPTION_DOUBLE = "FILE_MAINMENU_OPTION_DOUBLE";        
CONSTCFGTYPE FILE_MAINMENU_OPTION_DOUBLE_FOCUSED = "FILE_MAINMENU_OPTION_DOUBLE_FOCUSED";                                                                        
CONSTCFGTYPE FILE_MAINMENU_OPTION_NETWORK = "FILE_MAINMENU_OPTION_NETWORK";        
CONSTCFGTYPE FILE_MAINMENU_OPTION_NETWORK_FOCUSED = "FILE_MAINMENU_OPTION_NETWORK_FOCUSED";                                                                        
CONSTCFGTYPE FILE_MAINMENU_OPTION_BACK = "FILE_MAINMENU_OPTION_BACK";        
CONSTCFGTYPE FILE_MAINMENU_OPTION_BACK_FOCUSED = "FILE_MAINMENU_OPTION_BACK_FOCUSED";                                                                        
CONSTCFGTYPE FILE_MATCHMENU_BACKGROUND = "FILE_MATCHMENU_BACKGROUND";            
CONSTCFGTYPE FILE_MATCHMENU_OPTION_CONTINUE = "FILE_MATCHMENU_OPTION_CONTINUE";  
CONSTCFGTYPE FILE_MATCHMENU_OPTION_CONTINUE_FOCUSED = "FILE_MATCHMENU_OPTION_CONTINUE_FOCUSED";                                                                  
CONSTCFGTYPE FILE_MATCHMENU_OPTION_BACK = "FILE_MATCHMENU_OPTION_BACK";          
CONSTCFGTYPE FILE_MATCHMENU_OPTION_BACK_FOCUSED = "FILE_MATCHMENU_OPTION_BACK_FOCUSED";                                                                          
CONSTCFGTYPE FILE_REPLAY_1 = "FILE_REPLAY_1";                                    
CONSTCFGTYPE FILE_REPLAY_2 = "FILE_REPLAY_2";                                    
CONSTCFGTYPE FILE_REPLAY_3 = "FILE_REPLAY_3";                                    
CONSTCFGTYPE FILE_REPLAY_4 = "FILE_REPLAY_4";                                    
CONSTCFGTYPE FILE_REPLAY_5 = "FILE_REPLAY_5";                                    
CONSTCFGTYPE FILE_REPLAY_6 = "FILE_REPLAY_6";                                    
CONSTCFGTYPE FILE_LOADINGSCREEN01 = "FILE_LOADINGSCREEN01";                      
CONSTCFGTYPE FILE_LOADINGSCREEN02 = "FILE_LOADINGSCREEN02";                      
CONSTCFGTYPE FILE_LOADINGSCREEN03 = "FILE_LOADINGSCREEN03";                      
CONSTCFGTYPE FILE_LOADINGSCREEN04 = "FILE_LOADINGSCREEN04";                      
CONSTCFGTYPE FILE_LOADINGSCREEN05 = "FILE_LOADINGSCREEN05";                      
CONSTCFGTYPE FILE_LOADINGSCREEN06 = "FILE_LOADINGSCREEN06";                      
CONSTCFGTYPE FILE_LOADINGSCREEN07 = "FILE_LOADINGSCREEN07";                      
CONSTCFGTYPE FILE_LOADINGSCREEN08 = "FILE_LOADINGSCREEN08";                      
CONSTCFGTYPE FILE_MAINMENU_BACKGROUND01 = "FILE_MAINMENU_BACKGROUND01";          
CONSTCFGTYPE FILE_MAINMENU_BACKGROUND02 = "FILE_MAINMENU_BACKGROUND02";          
CONSTCFGTYPE FILE_MAINMENU_BACKGROUND03 = "FILE_MAINMENU_BACKGROUND03";          
CONSTCFGTYPE FILE_MAINMENU_BACKGROUND04 = "FILE_MAINMENU_BACKGROUND04";          
CONSTCFGTYPE FILE_MAINMENU_BACKGROUND05 = "FILE_MAINMENU_BACKGROUND05";          
CONSTCFGTYPE FILE_MAINMENU_BACKGROUND06 = "FILE_MAINMENU_BACKGROUND06";          
CONSTCFGTYPE FILE_MAINMENU_BACKGROUND07 = "FILE_MAINMENU_BACKGROUND07";          
CONSTCFGTYPE FILE_MAINMENU_BACKGROUND08 = "FILE_MAINMENU_BACKGROUND08";          
CONSTCFGTYPE FILE_LOG_DEBUG = "FILE_LOG_DEBUG";                                  
CONSTCFGTYPE FILE_RANKLIST_BACKGROUND = "FILE_RANKLIST_BACKGROUND";              
CONSTCFGTYPE FILE_DEFAULT_FONT = "FILE_DEFAULT_FONT";                            
CONSTCFGTYPE FILE_PLAYER_SELECT_TITLE1 = "FILE_PLAYER_SELECT_TITLE1";            
CONSTCFGTYPE FILE_PLAYER_SELECT_TITLE2 = "FILE_PLAYER_SELECT_TITLE2";            
CONSTCFGTYPE FILE_PINGPANG_LOGO = "FILE_PINGPANG_LOGO";                
CONSTCFGTYPE FILE_PLAYER_SELECT_CONFIRM = "FILE_PLAYER_SELECT_CONFIRM";          
CONSTCFGTYPE FILE_PLAYER_SELECT_NAME = "FILE_PLAYER_SELECT_NAME";                
CONSTCFGTYPE FILE_PLAYER_SELECT_CHAR_GIRL = "FILE_PLAYER_SELECT_CHAR_GIRL";      
CONSTCFGTYPE FILE_PLAYER_SELECT_CHAR_BOY = "FILE_PLAYER_SELECT_CHAR_BOY";        
CONSTCFGTYPE FILE_PLAYER_SELECT_BUTTON_BACK = "FILE_PLAYER_SELECT_BUTTON_BACK";  
CONSTCFGTYPE FILE_BALL_SHADOW_TEX = "FILE_BALL_SHADOW_TEX";                      
CONSTCFGTYPE FILE_BALL_COLLI_TEX = "FILE_BALL_COLLI_TEX";

CONSTCFGTYPE FILE_BALL_SPIN_CW_TEX1 = "FILE_BALL_SPIN_CW_TEX1";
CONSTCFGTYPE FILE_BALL_SPIN_CW_TEX2 = "FILE_BALL_SPIN_CW_TEX2";
CONSTCFGTYPE FILE_BALL_SPIN_CW_TEX3 = "FILE_BALL_SPIN_CW_TEX3";
CONSTCFGTYPE FILE_BALL_SPIN_CW_TEX4 = "FILE_BALL_SPIN_CW_TEX4";
CONSTCFGTYPE FILE_BALL_SPIN_CW_TEX5 = "FILE_BALL_SPIN_CW_TEX5";
CONSTCFGTYPE FILE_BALL_SPIN_CW_TEX6 = "FILE_BALL_SPIN_CW_TEX6";
CONSTCFGTYPE FILE_BALL_SPIN_CW_TEX7 = "FILE_BALL_SPIN_CW_TEX7";
CONSTCFGTYPE FILE_BALL_SPIN_CW_TEX8 = "FILE_BALL_SPIN_CW_TEX8";

CONSTCFGTYPE FILE_BALL_SPIN_CCW_TEX1 = "FILE_BALL_SPIN_CCW_TEX1";
CONSTCFGTYPE FILE_BALL_SPIN_CCW_TEX2 = "FILE_BALL_SPIN_CCW_TEX2";
CONSTCFGTYPE FILE_BALL_SPIN_CCW_TEX3 = "FILE_BALL_SPIN_CCW_TEX3";
CONSTCFGTYPE FILE_BALL_SPIN_CCW_TEX4 = "FILE_BALL_SPIN_CCW_TEX4";
CONSTCFGTYPE FILE_BALL_SPIN_CCW_TEX5 = "FILE_BALL_SPIN_CCW_TEX5";
CONSTCFGTYPE FILE_BALL_SPIN_CCW_TEX6 = "FILE_BALL_SPIN_CCW_TEX6";
CONSTCFGTYPE FILE_BALL_SPIN_CCW_TEX7 = "FILE_BALL_SPIN_CCW_TEX7";
CONSTCFGTYPE FILE_BALL_SPIN_CCW_TEX8 = "FILE_BALL_SPIN_CCW_TEX8";

CONSTCFGTYPE FILE_BALL_LEFTSHADOW = "FILE_BALL_LEFTSHADOW"; 
CONSTCFGTYPE HIT_PREPARE_TIME = "HIT_PREPARE_TIME";

CONSTCFGTYPE CFG_LOADING = "LOADING";
CONSTCFGTYPE CFG_FILE_CONNECTING = "FILE_CONNECTING";
CONSTCFGTYPE CFG_FILE_CONNECT_FAILED_1 = "FILE_CONNECT_FAILED_1";
CONSTCFGTYPE CFG_FILE_CONNECT_FAILED_2 = "FILE_CONNECT_FAILED_2";
CONSTCFGTYPE CFG_FILE_CONNECT_SUCCEED = "FILE_CONNECT_SUCCEED";
CONSTCFGTYPE CFG_FILE_CONNECT_SQUARE = "FILE_CONNECT_SQUARE";
CONSTCFGTYPE CFG_MAX_CONNECT_TRIES = "MAX_CONNECT_TRIES";
CONSTCFGTYPE CFG_SECONDS_BEFORE_EXIT = "SECONDS_BEFORE_EXIT";
CONSTCFGTYPE CFG_SECONDS_BEFORE_RETRY = "SECONDS_BEFORE_RETRY";

CONSTCFGTYPE CFG_ENERGY = "ENERGY";
CONSTCFGTYPE CFG_ENERGY_MAX_CST = "MAX_CST";
CONSTCFGTYPE CFG_ENERGY_MAX_ACC = "MAX_ACC";
CONSTCFGTYPE CFG_ENERGY_FILE_BACKGROUND = "FILE_BACKGROUND";
CONSTCFGTYPE CFG_ENERGY_FILE_CALORIE = "FILE_CALORIE";
CONSTCFGTYPE CFG_ENERGY_FILE_CONTINUE = "FILE_CONTINUE";

CONSTCFGTYPE CFG_FILE_POWER_A = "FILE_POWER_A";
CONSTCFGTYPE CFG_FILE_POWER_B = "FILE_POWER_B";
CONSTCFGTYPE CFG_FILE_POWER_LEVEL = "FILE_POWER_LEVEL";

CONSTCFGTYPE CHOP_HIGH2LOW_POSSI = "CHOP_HIGH2LOW_POSSI";
CONSTCFGTYPE SUPERHIT_RATE = "SUPERHIT_RATE";
CONSTCFGTYPE NPC_SUPERHIT_RATE = "NPC_SUPERHIT_RATE";
CONSTCFGTYPE ACC_HIGH_MODE_THRESHOLD = "ACC_HIGH_MODE_THRESHOLD";
CONSTCFGTYPE MAX_HIT_COUNT = "MAX_HIT_COUNT";
CONSTCFGTYPE MAX_SUPERHITRATE = "MAX_SUPERHITRATE";
CONSTCFGTYPE END_TIME = "END_TIME";
CONSTCFGTYPE MAX_SUPERHITTIME_FACTOR = "MAX_SUPERHITTIME_FACTOR";
CONSTCFGTYPE MIN_SUPERHITTIME_FACTOR = "MIN_SUPERHITTIME_FACTOR";
CONSTCFGTYPE MAX_HIT_ACC = "MAX_HIT_ACC";
CONSTCFGTYPE MAX_CAM_XMOVEOFFSET = "MAX_CAM_XMOVEOFFSET";
CONSTCFGTYPE MIN_CAM_XMOVEOFFSET = "MIN_CAM_XMOVEOFFSET";
CONSTCFGTYPE CAM_ZMOVEOFFSET = "CAM_ZMOVEOFFSET";
CONSTCFGTYPE CAM_ANIM_TIME = "CAM_ANIM_TIME";

CONSTCFGTYPE CFG_FILE_KEYPAD = "FILE_KEYPAD";
CONSTCFGTYPE CFG_FILE_KEY_FRAME = "FILE_KEY_FRAME";
CONSTCFGTYPE CFG_FILE_INPUT_ARROW = "FILE_INPUT_ARROW";
CONSTCFGTYPE CFG_FILE_INPUT_PLAYER_NAME = "FILE_INPUT_PLAYER_NAME";

CONSTCFGTYPE CFG_FONT_INPUT = "FONT_INPUT";
CONSTCFGTYPE CFG_FILE_INPUT_HELP = "FILE_INPUT_HELP";

CONSTCFGTYPE CFG_FILE_SPEED_BK = "FILE_SPEED_BK";

CONSTCFGTYPE MIN_BALL_DISPLAYSPEED = "MIN_BALL_DISPLAYSPEED";
CONSTCFGTYPE MAX_BALL_DISPLAYSPEED = "MAX_BALL_DISPLAYSPEED";
CONSTCFGTYPE SUPERHIT_KEY = "SUPERHIT_KEY";
CONSTCFGTYPE ACC_SPIN_THRESHOLD_1 = "ACC_SPIN_THRESHOLD_1";
CONSTCFGTYPE ACC_SPIN_THRESHOLD_2 = "ACC_SPIN_THRESHOLD_2";
CONSTCFGTYPE NPC_SPIN_HITBACK_POSSI = "NPC_SPIN_HITBACK_POSSI";
CONSTCFGTYPE SPIN_HITBACK_STRENGTH = "SPIN_HITBACK_STRENGTH";

CONSTCFGTYPE CFG_GAMELIST						= "GAMELIST";
CONSTCFGTYPE CFG_GAMELIST_BK						= "GAME_LIST_BK";
CONSTCFGTYPE CFG_GAMELIST_ARROW_UP				= "GAMELIST_ARROW_UP";
CONSTCFGTYPE CFG_GAMELIST_ARROW_DOWN				= "GAMELIST_ARROW_DOWN";
CONSTCFGTYPE CFG_GAMELIST_BUTTON_BACK			= "GAMELIST_BUTTON_BACK";
CONSTCFGTYPE CFG_GAMELIST_BUTTON_BACK_FOCUSED	= "GAMELIST_BUTTON_BACK_FOCUSED";
CONSTCFGTYPE CFG_GAMELIST_BUTTON_USERLIST			= "GAMELIST_BUTTON_USERLIST";
CONSTCFGTYPE CFG_GAMELIST_BUTTON_USERLIST_FOCUSED		= "GAMELIST_BUTTON_USERLIST_FOCUSED";
CONSTCFGTYPE CFG_GAMELIST_BUTTON_CREATE			= "GAMELIST_BUTTON_CREATE";
CONSTCFGTYPE CFG_GAMELIST_BUTTON_CREATE_FOCUSED	= "GAMELIST_BUTTON_CREATE_FOCUSED";
CONSTCFGTYPE CFG_GAMELIST_BUTTON_LIST			= "GAMELIST_BUTTON_LIST";
CONSTCFGTYPE CFG_GAMELIST_BUTTON_LIST_FOCUSED	= "GAMELIST_BUTTON_LIST_FOCUSED";
CONSTCFGTYPE CFG_GAMELIST_ICON_GAME_SELECTED		= "GAMELIST_ICON_GAME_SELECTED";
CONSTCFGTYPE CFG_GAMELIST_ICON_GAME_WAITING		= "GAMELIST_ICON_GAME_WAITING";
CONSTCFGTYPE CFG_GAMELIST_ICON_ROOM				= "GAMELIST_ICON_ROOM";

CONSTCFGTYPE CFG_USERLIST_BK									= "USERLIST_BK";
CONSTCFGTYPE CFG_USERLIST_ICON_USER_SELECTED		= "USERLIST_ICON_USER_SELECTED";
CONSTCFGTYPE CFG_USERLIST_ICON_STATUS_WAITING		= "USERLIST_ICON_STATUS_WAITING";
CONSTCFGTYPE CFG_USERLIST_ICON_STATUS_PLAYING		= "USERLIST_ICON_STATUS_PLAYING";
CONSTCFGTYPE CFG_USERLIST_ICON_STATUS_IDLE    		= "USERLIST_ICON_STATUS_IDLE";

CONSTCFGTYPE CFG_FILE_NETWORK_WAITING1			= "FILE_NETWORK_WAITING1";
CONSTCFGTYPE CFG_FILE_NETWORK_WAITING2			= "FILE_NETWORK_WAITING2";


CONSTCFGTYPE CFG_GAME_SERVER_ADDR				= "GAME_SERVER_ADDR";
CONSTCFGTYPE CFG_GAME_SERVER_PORT				= "GAME_SERVER_PORT";
CONSTCFGTYPE CFG_CLIENT_PORT						= "CLIENT_PORT";

CONSTCFGTYPE CFG_FILE_LOGIN_FAILED				= "FILE_LOGIN_FAILED";
CONSTCFGTYPE CFG_FILE_SERVER_CONNECTION_FAILED	= "FILE_SERVER_CONNECTION_FAILED";
CONSTCFGTYPE CFG_FILE_NETWORK_DROPPED			= "FILE_NETWORK_DROPPED";
CONSTCFGTYPE CFG_FILE_NETWORK_CONNECTING			= "FILE_NETWORK_CONNECTING";
CONSTCFGTYPE CFG_FILE_NETWORK_RECONNECTING		= "FILE_NETWORK_RECONNECTING";
CONSTCFGTYPE CFG_FILE_GAME_TERMINATED			= "FILE_GAME_TERMINATED";
CONSTCFGTYPE CFG_FILE_DIALOG_BK512x128			= "FILE_DIALOG_BK512x128";

CONSTCFGTYPE CFG_DEFAULT_USERNAME				= "DEFAULT_USERNAME";
CONSTCFGTYPE CFG_DEFAULT_PASSWORD				= "DEFAULT_PASSWORD";

CONSTCFGTYPE CFG_FILE_REMOTE_RECONNECTING		= "FILE_REMOTE_RECONNECTING";
CONSTCFGTYPE CFG_FILE_REMOTE_RECONNECT_FAILED	= "FILE_REMOTE_RECONNECT_FAILED";

CONSTCFGTYPE CFG_CAMERA_CENTER_Y					= "CAMERA_CENTER_Y";
CONSTCFGTYPE CFG_CAMERA_VECTOR0_Y				= "CAMERA_VECTOR0_Y";
CONSTCFGTYPE CFG_CAMERA_VECTOR3_Y				= "CAMERA_VECTOR3_Y";
CONSTCFGTYPE CFG_CAMERA_VECTOR3_Z				= "CAMERA_VECTOR3_Z";
CONSTCFGTYPE CFG_CAMERA_DSTVECTOR_X				= "CAMERA_DSTVECTOR_X";
CONSTCFGTYPE CFG_CAMERA_DSTVECTOR_Y				= "CAMERA_DSTVECTOR_Y";

CONSTCFGTYPE CFG_USERDETAIL							= "USERDETAIL";
CONSTCFGTYPE FILE_USERDETAIL_BK						= "FILE_USERDETAIL_BK";
CONSTCFGTYPE FILE_USER_OP_INVITE					= "FILE_USER_OP_INVITE";
CONSTCFGTYPE FILE_USER_OP_INVITE_DISABLED	= "FILE_USER_OP_INVITE_DISABLED";
CONSTCFGTYPE FILE_USER_OP_JOIN						= "FILE_USER_OP_JOIN";
CONSTCFGTYPE FILE_USER_OP_JOIN_DISABLED		= "FILE_USER_OP_JOIN_DISABLED";
CONSTCFGTYPE FILE_USER_OP_WATCH					= "FILE_USER_OP_WATCH";
CONSTCFGTYPE FILE_USER_OP_WATCH_DISABLED	= "FILE_USER_OP_WATCH_DISABLED";
CONSTCFGTYPE FILE_USER_OP_BACK						= "FILE_USER_OP_BACK";
CONSTCFGTYPE FILE_BUTTON_SPRITE						= "FILE_BUTTON_SPRITE";

// Tips texture files
CONSTCFGTYPE FILE_TIPS_SERVEBALL1 = "FILE_TIPS_SERVEBALL1";
CONSTCFGTYPE FILE_TIPS_SERVEBALL2 = "FILE_TIPS_SERVEBALL2";
CONSTCFGTYPE FILE_TIPS_SERVEBALL3 = "FILE_TIPS_SERVEBALL3";

CONSTCFGTYPE FILE_TIPS_SWINGBALL1 = "FILE_TIPS_SWINGBALL1";
CONSTCFGTYPE FILE_TIPS_SWINGBALL2 = "FILE_TIPS_SWINGBALL2";
CONSTCFGTYPE FILE_TIPS_SWINGBALL3 = "FILE_TIPS_SWINGBALL3";

CONSTCFGTYPE FILE_TIPS_SPINBALL1 = "FILE_TIPS_SPINBALL1";
CONSTCFGTYPE FILE_TIPS_SPINBALL2 = "FILE_TIPS_SPINBALL2";
CONSTCFGTYPE FILE_TIPS_SPINBALL3 = "FILE_TIPS_SPINBALL3";

CONSTCFGTYPE FILE_TIPS_BUTTON1 = "FILE_TIPS_BUTTON1";
CONSTCFGTYPE FILE_TIPS_BUTTON2 = "FILE_TIPS_BUTTON2";
CONSTCFGTYPE FILE_TIPS_PLUS = "FILE_TIPS_PLUS";

// Wii mote control settings
CONSTCFGTYPE FILE_REMOTE_LIB = "FILE_REMOTE_LIB";
CONSTCFGTYPE CFG_USE_WIIMOTE = "CFG_USE_WIIMOTE";

CONSTCFGTYPE CFG_FILE_PATH = "TokaDemo.cfg";

void CTennisCfgVars::ResetCfgVars( ConfigParser& cfg_parser )
{
	cfg_parser.set(MIN_X_TABLE, -550.f/2);
	cfg_parser.set(MIN_Y_TABLE, 0.f);
	cfg_parser.set(MIN_Z_TABLE, -1200.f/2);
	cfg_parser.set(MAX_X_TABLE, 550.f/2);
	cfg_parser.set(MAX_Y_TABLE, 0.f);
	cfg_parser.set(MAX_Z_TABLE, 1200.f/2);

	cfg_parser.set(MIN_X_TABLE_BASE, -550.f/2 * 0.7f);
	cfg_parser.set(MIN_Y_TABLE_BASE, 0.0f);
	cfg_parser.set(MIN_Z_TABLE_BASE, -1200.0f/2 * 0.7f);
	cfg_parser.set(MAX_X_TABLE_BASE, 550.f/2 * 0.7f);
	cfg_parser.set(MAX_Y_TABLE_BASE, 0.0f);
	cfg_parser.set(MAX_Z_TABLE_BASE, 1200.0f/2 * 0.7f);

	cfg_parser.set(MIN_X_TABLE_NET, -1097.f/2 - 15.25f);
	cfg_parser.set(MIN_Y_TABLE_NET, 101.0f - 0.1f);
	cfg_parser.set(MIN_Z_TABLE_NET, -0.5f);
	cfg_parser.set(MAX_X_TABLE_NET, 1097.f/2 + 15.25f);
	cfg_parser.set(MAX_Y_TABLE_NET, 101.0f + 8.25f);
	cfg_parser.set(MAX_Z_TABLE_NET, 0.5f);
/*
	cfg_parser.set(MIN_X_TABLE, -152.5f/2);
	cfg_parser.set(MIN_Y_TABLE, 71.0f);
	cfg_parser.set(MIN_Z_TABLE, -274.0f/2);
	cfg_parser.set(MAX_X_TABLE, 152.5f/2);
	cfg_parser.set(MAX_Y_TABLE, 76.0f);
	cfg_parser.set(MAX_Z_TABLE, 274.0f/2);
	cfg_parser.set(MIN_X_TABLE_BASE, -152.5f/2 * 0.7f);
	cfg_parser.set(MIN_Y_TABLE_BASE, 0.0f);
	cfg_parser.set(MIN_Z_TABLE_BASE, -274.0f/2 * 0.7f);
	cfg_parser.set(MAX_X_TABLE_BASE, 152.5f/2 * 0.7f);
	cfg_parser.set(MAX_Y_TABLE_BASE, 71.0f);
	cfg_parser.set(MAX_Z_TABLE_BASE, 274.0f/2 * 0.7f);
	cfg_parser.set(MIN_X_TABLE_NET, -76.3f - 15.25f);
	cfg_parser.set(MIN_Y_TABLE_NET, 76.0f - 0.1f);
	cfg_parser.set(MIN_Z_TABLE_NET, -0.5f);
	cfg_parser.set(MAX_X_TABLE_NET, 76.3f + 15.25f);
	cfg_parser.set(MAX_Y_TABLE_NET, 76.0f + 15.25f);
	cfg_parser.set(MAX_Z_TABLE_NET, 0.5f);
*/
	cfg_parser.set(MIN_X_ROOM, -762.5f * 1.0f);
	cfg_parser.set(MIN_Y_ROOM, 0.0f);
	cfg_parser.set(MIN_Z_ROOM, -1370.0f * 1.0f);
	cfg_parser.set(MAX_X_ROOM, 762.5f * 1.0f);
	cfg_parser.set(MAX_Y_ROOM, 3000.0f);
	cfg_parser.set(MAX_Z_ROOM, 1370.0f * 1.0f);

	cfg_parser.set(MIN_X_STADIUM_BOT, -700.0f * 0.5f);
	cfg_parser.set(MIN_Z_STADIUM_BOT, -1400.0f * 0.5f);
	cfg_parser.set(MAX_X_STADIUM_BOT, 700.0f * 0.5f);
	cfg_parser.set(MAX_Z_STADIUM_BOT, 1400.0f * 0.5f);
	cfg_parser.set(MIN_X_STADIUM_TOP, -700.0f * 1.8f);
	cfg_parser.set(MIN_Z_STADIUM_TOP, -1400.0f * 1.8f);
	cfg_parser.set(MAX_X_STADIUM_TOP, 700.0f * 1.8f);
	cfg_parser.set(MAX_Z_STADIUM_TOP, 1400.0f * 1.8f);
	cfg_parser.set(MIN_Y_STADIUM, 0.0f);
	cfg_parser.set(MAX_Y_STADIUM, 3000.0f);

	cfg_parser.set(BALL_RADIUS, 30.0f/2);
	cfg_parser.set(BALL_GRAVITY_ACC, -980.0f/2.0f);
	cfg_parser.set(BALL_COLLISION_COEEF, .5f);
	cfg_parser.set(BALL_FRICTION_COEEF, .3f);
	cfg_parser.set(BALL_COLLISION_SPEED, 20.f);
	cfg_parser.set(BALL_COLLISION_START, 10.f);
	cfg_parser.set(BALL_SERVE_COEEF, 0.7f);

	cfg_parser.set(BALL_SPEED_MAJOR1, 1.2f);// SLOW
	cfg_parser.set(BALL_SPEED_MAJOR2, 1.f);// NORMAL
	cfg_parser.set(BALL_SPEED_MAJOR3, 1.f);// NORMAL fast1
	cfg_parser.set(BALL_SPEED_MAJOR4, 1.f);// NORMAL fast2
	cfg_parser.set(BALL_SPEED_MAJOR5, 1.f);// NORMAL fast3
	cfg_parser.set(BALL_SPEED_MAJOR6, 1.f);// FAST

	cfg_parser.set(BALL_SPEED_MINOR1, .5f);
	cfg_parser.set(BALL_SPEED_MINOR2, .75f);
	cfg_parser.set(BALL_SPEED_MINOR3, .5f);
	cfg_parser.set(BALL_SPEED_MINOR4, .25f);
	cfg_parser.set(BALL_SPEED_MINOR5, .1f);
	cfg_parser.set(BALL_SPEED_MINOR6, .0f);

	cfg_parser.set(BALL_SPIN_FACTOR1, .2f);
	cfg_parser.set(BALL_SPIN_FACTOR2, .5f);
	cfg_parser.set(BALL_SPIN_FACTOR3, .8f);

	cfg_parser.set(BALL_TRAIL_RFACTOR, .2f);
	cfg_parser.set(BALL_TRAIL_LENGTH, 2);
	cfg_parser.set(BALL_TRAIL_FLENGTH, 12);

	cfg_parser.set(BALL_SPINEFFECT_WIDTH, 14.f);
	cfg_parser.set(BALL_SPINEFFECT_HEIGHT, 5.f);

	cfg_parser.set(HITTIM_DURATION, 1.0f);
	cfg_parser.set(Z_BACK_TOHIT, 50.0f);
	cfg_parser.set(MAX_Z_HITBALL, 350.0f);
	cfg_parser.set(HIT_ACTIONTIME, 0.6f);
	cfg_parser.set(POSTHIT_BACKTIME, 0.7f);
	cfg_parser.set(POSTHIT_BACK_THRESHOLD, 10.f);
	cfg_parser.set(ACC_THRESHOLD, 200);
	cfg_parser.set(MAX_INTERVALTIME, 120.f);
	cfg_parser.set(MAX_Z_HITRANGE, 1000.f);
	cfg_parser.set(MIN_Z_HITRANGE, 1000.f);
	cfg_parser.set(STEP_Z, 50.f);
	cfg_parser.set(MAX_X_HITRANGE, 411.5 + 13.1f);
	cfg_parser.set(MIN_X_HITRANGE, -(411.5 + 13.1f));
	cfg_parser.set(STEP_X, 30.f);
	cfg_parser.set(MAX_Y_HITRANGE, 180.f);
	cfg_parser.set(MIN_Y_HITRANGE, 80.f);
	cfg_parser.set(STEP_Y, 50.f);
	cfg_parser.set(CAMERA_NEAR_VALUE, 30.f);
	cfg_parser.set(CAMERA_FAR_VALUE, 60000.f);
	cfg_parser.set(REPLAY_POSSIBILITY, 10.f);
	//cfg_parser.set(FILE_LOADINGSCREEN, "../../media-tokamak/ui_background.jpg");
	//cfg_parser.set(FILE_LOADINGBAR, "../../media-tokamak/ui_loading.png");
	//cfg_parser.set(FILE_LOADINGPROGRESS, "../../media-tokamak/loading-over.png");
	//cfg_parser.set(FILE_SETUPINPUT, "../../media-tokamak/ui_setupinput.png");
	//cfg_parser.set(FILE_STARTBAR, "../../media-tokamak/press-a.png");
	//cfg_parser.set(FILE_DIALOGQUIT, "../../media-tokamak/ui_dialog_quit.png");
	cfg_parser.set(FILE_FONT, "../../media-tokamak/fontcourier.bmp");
	cfg_parser.set(FILE_TEXTURE_SCOREBAR, "../../media-tokamak/4a.png");
	cfg_parser.set(FILE_SCORE_FONT, "../../media-tokamak/number21.png");
	cfg_parser.set(FILE_SCORE_FONT2, "../../media-tokamak/number22.png");
	cfg_parser.set(FILE_BALL_TEXTURE, "../../media-tokamak/ball_tennis.bmp");
	cfg_parser.set(FILE_FLOOR_TEXTURE, "../../media-tokamak/tennis_1.jpg");
	cfg_parser.set(FILE_RACKET_MESH, "../../media-tokamak/tennis_girl_racket.md2");
	cfg_parser.set(FILE_RACKET_MESH2, "../../media-tokamak/tennis_boy_racket.md2");
	cfg_parser.set(FILE_SCENE_MESH, "../../media-tokamak/tennis_1.md2");
	cfg_parser.set(FILE_SCENE_TEXTURE, "../../media-tokamak/tennis_1.jpg");
	cfg_parser.set(FILE_SCENE_MESH_EX, "../../media-tokamak/tennis_2.md2");
	cfg_parser.set(FILE_SCENE_TEXTURE_EX, "../../media-tokamak/tennis_2.jpg");
	cfg_parser.set(FILE_TABLE_MESH, "../../media-tokamak/table.md2");
	cfg_parser.set(FILE_TABLE_TEXTURE, "../../media-tokamak/table_512_DVN.tga");
	cfg_parser.set(FILE_TABLE_NET_MESH, "../../media-tokamak/tennis_net.md2");
	cfg_parser.set(FILE_TABLE_NET_TEXTURE, "../../media-tokamak/tennis_1.jpg");
	
	cfg_parser.set(FILE_FENCE_TEXTURE, "../../media-tokamak/fence_logo3.jpg");
	cfg_parser.set(FILE_FENCE_TEXTURE_1, "../../media-tokamak/fence_logo3.jpg");
	cfg_parser.set(FILE_FENCE_TEXTURE_2, "../../media-tokamak/fence_logo3.jpg");

	cfg_parser.set(FILE_RACKET_TEXTURE, "../../media-tokamak/racket.tga");
	
	cfg_parser.set(FILE_PLAYER_MESH_1, "../../media-tokamak/m_player.md2");
	cfg_parser.set(FILE_PLAYER_TEXTURE_1, "../../media-tokamak/m_player_small.jpg");
	cfg_parser.set(FILE_PLAYER_MESH_2, "../../media-tokamak/m_player.md2");
	cfg_parser.set(FILE_PLAYER_TEXTURE_2, "../../media-tokamak/m_player_small.tga");
	cfg_parser.set(FILE_PLAYER_MESH_3, "../../media-tokamak/tennis_boy_body.md2");
	cfg_parser.set(FILE_PLAYER_TEXTURE_3, "../../media-tokamak/boy3.tga");
	cfg_parser.set(FILE_PLAYER_MESH_4, "../../media-tokamak/tennis_girl_body.md2");
	cfg_parser.set(FILE_PLAYER_TEXTURE_4, "../../media-tokamak/girl3.tga");

	cfg_parser.set(FILE_SOUND_RAKETKA1, "../../media-tokamak/Raketka1.wav");
	cfg_parser.set(FILE_SOUND_RAKETKA2, "../../media-tokamak/Raketka2.wav");
	cfg_parser.set(FILE_SOUND_TABLE, "../../media-tokamak/Table.wav");
	cfg_parser.set(FILE_SOUND_BEEP, "../../media-tokamak/Beep.wav");
	cfg_parser.set(FILE_SOUND_APPLAUSE, "../../media-tokamak/applause.wav");
	cfg_parser.set(FILE_SOUND_OPENNING, "../../media-tokamak/opening.wav");
	
	cfg_parser.set(FILE_INTRO_LOGO1, "../../media-tokamak/intro_logo.jpg");
	cfg_parser.set(FILE_INTRO_LOGO2, "../../media-tokamak/intro_logo.jpg");
	
//	cfg_parser.set(FILE_MAINMENU_BACKGROUND, "../../media-tokamak/main_menu_background.jpg");
	cfg_parser.set(FILE_MAINMENU_OPTION_START, "../../media-tokamak/main_menu_start.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_START_FOCUSED, "../../media-tokamak/main_menu_start_focused.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_EXIT, "../../media-tokamak/main_menu_exit.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_EXIT_FOCUSED, "../../media-tokamak/main_menu_exit_focused.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_SETUP_DISABLED, "../../media-tokamak/main_menu_setup_disabled.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_REMOTER_DISABLED, "../../media-tokamak/main_menu_remoter_disabled.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_ROLE_DISABLED, "../../media-tokamak/main_menu_role_disabled.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_SINGLE, "../../media-tokamak/main_menu_single.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_SINGLE_FOCUSED, "../../media-tokamak/main_menu_single_focused.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_DOUBLE, "../../media-tokamak/main_menu_double.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_DOUBLE_FOCUSED, "../../media-tokamak/main_menu_double_focused.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_NETWORK, "../../media-tokamak/main_menu_network.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_NETWORK_FOCUSED, "../../media-tokamak/main_menu_network_focused.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_BACK, "../../media-tokamak/main_menu_back.png");
	cfg_parser.set(FILE_MAINMENU_OPTION_BACK_FOCUSED, "../../media-tokamak/main_menu_back_focused.png");
	cfg_parser.set(FILE_MATCHMENU_BACKGROUND, "../../media-tokamak/game_menu_background.png");
	cfg_parser.set(FILE_MATCHMENU_OPTION_CONTINUE, "../../media-tokamak/match_menu_continue.png");
	cfg_parser.set(FILE_MATCHMENU_OPTION_CONTINUE_FOCUSED, "../../media-tokamak/match_menu_continue_focused.png");
	cfg_parser.set(FILE_MATCHMENU_OPTION_BACK, "../../media-tokamak/match_menu_back.png");
	cfg_parser.set(FILE_MATCHMENU_OPTION_BACK_FOCUSED, "../../media-tokamak/match_menu_back_focused.png");
	//cfg_parser.set(FILE_REPLAY_1, "../../media-tokamak/replay01.png");
	//cfg_parser.set(FILE_REPLAY_2, "../../media-tokamak/replay02.png");
	//cfg_parser.set(FILE_REPLAY_3, "../../media-tokamak/replay03.png");
	//cfg_parser.set(FILE_REPLAY_4, "../../media-tokamak/replay04.png");
	//cfg_parser.set(FILE_REPLAY_5, "../../media-tokamak/replay05.png");
	//cfg_parser.set(FILE_REPLAY_6, "../../media-tokamak/replay06.png");
	cfg_parser.set(FILE_LOADINGSCREEN01, "../../media-tokamak/ui_background01.jpg");
	cfg_parser.set(FILE_LOADINGSCREEN02, "../../media-tokamak/ui_background02.jpg");
	cfg_parser.set(FILE_LOADINGSCREEN03, "../../media-tokamak/ui_background03.jpg");
	cfg_parser.set(FILE_LOADINGSCREEN04, "../../media-tokamak/ui_background04.jpg");
	cfg_parser.set(FILE_LOADINGSCREEN05, "../../media-tokamak/ui_background05.jpg");
	cfg_parser.set(FILE_LOADINGSCREEN06, "../../media-tokamak/ui_background06.jpg");
	cfg_parser.set(FILE_LOADINGSCREEN07, "../../media-tokamak/ui_background07.jpg");
	cfg_parser.set(FILE_LOADINGSCREEN08, "../../media-tokamak/ui_background08.jpg");
	cfg_parser.set(FILE_MAINMENU_BACKGROUND01, "../../media-tokamak/mainmenu_background01.jpg");
	cfg_parser.set(FILE_MAINMENU_BACKGROUND02, "../../media-tokamak/mainmenu_background02.jpg");
	cfg_parser.set(FILE_MAINMENU_BACKGROUND03, "../../media-tokamak/mainmenu_background03.jpg");
	cfg_parser.set(FILE_MAINMENU_BACKGROUND04, "../../media-tokamak/mainmenu_background04.jpg");
	cfg_parser.set(FILE_MAINMENU_BACKGROUND05, "../../media-tokamak/mainmenu_background05.jpg");
	cfg_parser.set(FILE_MAINMENU_BACKGROUND06, "../../media-tokamak/mainmenu_background06.jpg");
	cfg_parser.set(FILE_MAINMENU_BACKGROUND07, "../../media-tokamak/mainmenu_background07.jpg");
	cfg_parser.set(FILE_MAINMENU_BACKGROUND08, "../../media-tokamak/mainmenu_background08.jpg");
	cfg_parser.set(FILE_LOG_DEBUG, "../../log/tennis_log");
	cfg_parser.set(FILE_RANKLIST_BACKGROUND, "../../media-tokamak/bg_ranklist.png");
	cfg_parser.set(FILE_DEFAULT_FONT, "../../media-tokamak/fontcartoon_20_bold.bmp");
	cfg_parser.set(FILE_PLAYER_SELECT_TITLE1, "../../media-tokamak/player_select_title1.png");
	cfg_parser.set(FILE_PLAYER_SELECT_TITLE2, "../../media-tokamak/player_select_title2.png");
	cfg_parser.set(FILE_PINGPANG_LOGO, "../../media-tokamak/tennis_logo.png");
	cfg_parser.set(FILE_PLAYER_SELECT_CONFIRM, "../../media-tokamak/player_select_confirm.png");
	cfg_parser.set(FILE_PLAYER_SELECT_NAME, "../../media-tokamak/player_select_name.png");
	cfg_parser.set(FILE_PLAYER_SELECT_CHAR_GIRL, "../../media-tokamak/girl_tennis.jpg");
	cfg_parser.set(FILE_PLAYER_SELECT_CHAR_BOY, "../../media-tokamak/boy_tennis.jpg");
	cfg_parser.set(FILE_PLAYER_SELECT_BUTTON_BACK, "../../media-tokamak/button_back.png");
	cfg_parser.set(FILE_BALL_SHADOW_TEX, "../../media-tokamak/ball_shad.tga");
	cfg_parser.set(FILE_BALL_COLLI_TEX, "../../media-tokamak/fireball.tga");

	cfg_parser.set(FILE_BALL_SPIN_CW_TEX1, "../../media-tokamak/ball_fire01.tga");
	cfg_parser.set(FILE_BALL_SPIN_CW_TEX2, "../../media-tokamak/ball_fire02.tga");
	cfg_parser.set(FILE_BALL_SPIN_CW_TEX3, "../../media-tokamak/ball_fire03.tga");
	cfg_parser.set(FILE_BALL_SPIN_CW_TEX4, "../../media-tokamak/ball_fire04.tga");
	cfg_parser.set(FILE_BALL_SPIN_CW_TEX5, "../../media-tokamak/ball_fire05.tga");
	cfg_parser.set(FILE_BALL_SPIN_CW_TEX6, "../../media-tokamak/ball_fire06.tga");
	cfg_parser.set(FILE_BALL_SPIN_CW_TEX7, "../../media-tokamak/ball_fire07.tga");
	cfg_parser.set(FILE_BALL_SPIN_CW_TEX8, "../../media-tokamak/ball_fire08.tga");

	cfg_parser.set(FILE_BALL_SPIN_CCW_TEX1, "../../media-tokamak/ball_blizzard01.tga");
	cfg_parser.set(FILE_BALL_SPIN_CCW_TEX2, "../../media-tokamak/ball_blizzard02.tga");
	cfg_parser.set(FILE_BALL_SPIN_CCW_TEX3, "../../media-tokamak/ball_blizzard03.tga");
	cfg_parser.set(FILE_BALL_SPIN_CCW_TEX4, "../../media-tokamak/ball_blizzard04.tga");
	cfg_parser.set(FILE_BALL_SPIN_CCW_TEX5, "../../media-tokamak/ball_blizzard05.tga");
	cfg_parser.set(FILE_BALL_SPIN_CCW_TEX6, "../../media-tokamak/ball_blizzard06.tga");
	cfg_parser.set(FILE_BALL_SPIN_CCW_TEX7, "../../media-tokamak/ball_blizzard07.tga");
	cfg_parser.set(FILE_BALL_SPIN_CCW_TEX8, "../../media-tokamak/ball_blizzard08.tga");

	cfg_parser.set(FILE_BALL_LEFTSHADOW, "../../media-tokamak/fireball.tga");
	cfg_parser.set(HIT_PREPARE_TIME, 200);
	
	cfg_parser.set(CHOP_HIGH2LOW_POSSI, 50);
    cfg_parser.set(SUPERHIT_RATE, 0.05);
    cfg_parser.set(NPC_SUPERHIT_RATE, 0.01);

	cfg_parser.set(CFG_FILE_CONNECTING, "../../media-tokamak/connecting.png", CFG_LOADING);
	cfg_parser.set(CFG_FILE_CONNECT_FAILED_1, "../../media-tokamak/connect_failed1.png", CFG_LOADING);
	cfg_parser.set(CFG_FILE_CONNECT_FAILED_2, "../../media-tokamak/connect_failed2.png", CFG_LOADING);
	cfg_parser.set(CFG_FILE_CONNECT_SUCCEED, "../../media-tokamak/connect_success.png", CFG_LOADING);
	//cfg_parser.set(CFG_FILE_CONNECT_SQUARE, "../../media-tokamak/connecting_square.png", CFG_LOADING);
	cfg_parser.set(CFG_MAX_CONNECT_TRIES, 3, CFG_LOADING);
	cfg_parser.set(CFG_SECONDS_BEFORE_EXIT, 30, CFG_LOADING);
	cfg_parser.set(CFG_SECONDS_BEFORE_RETRY, 10, CFG_LOADING);

	cfg_parser.set(CFG_ENERGY_MAX_CST, 0.5f, CFG_ENERGY);
	cfg_parser.set(CFG_ENERGY_MAX_ACC, 1400, CFG_ENERGY);

	cfg_parser.set(CFG_ENERGY_FILE_BACKGROUND, "../../media-tokamak/energy_consumed.png", CFG_ENERGY);
	cfg_parser.set(CFG_ENERGY_FILE_CALORIE, "../../media-tokamak/calorie.png", CFG_ENERGY);
	cfg_parser.set(CFG_ENERGY_FILE_CONTINUE, "../../media-tokamak/continue.png", CFG_ENERGY);

	cfg_parser.set(CFG_FILE_POWER_A, "../../media-tokamak/power_A.png");
	cfg_parser.set(CFG_FILE_POWER_B, "../../media-tokamak/power_B.png");
	cfg_parser.set(CFG_FILE_POWER_LEVEL, "../../media-tokamak/power_level.png");

    cfg_parser.set(ACC_HIGH_MODE_THRESHOLD, 600);
    cfg_parser.set(MAX_HIT_COUNT, 5);
    cfg_parser.set(MAX_SUPERHITRATE, 10);
    cfg_parser.set(END_TIME, 0.15f);
    cfg_parser.set(MAX_SUPERHITTIME_FACTOR, 0.05f);
    cfg_parser.set(MIN_SUPERHITTIME_FACTOR, 0.05f);
    cfg_parser.set(MAX_HIT_ACC, 1600);
    cfg_parser.set(MAX_CAM_XMOVEOFFSET, 50.f);
	cfg_parser.set(MIN_CAM_XMOVEOFFSET, -50.f);
    cfg_parser.set(CAM_ZMOVEOFFSET, 400.f);
    cfg_parser.set(CAM_ANIM_TIME, 200.f);

	cfg_parser.set(CFG_FILE_KEYPAD, "../../media-tokamak/keypad.png");
	cfg_parser.set(CFG_FILE_KEY_FRAME, "../../media-tokamak/key_frame.png");
	cfg_parser.set(CFG_FILE_INPUT_ARROW, "../../media-tokamak/arrow.png");
	cfg_parser.set(CFG_FILE_INPUT_PLAYER_NAME, "../../media-tokamak/input_player_name.png");
	cfg_parser.set(CFG_FONT_INPUT, "../../media-tokamak/fontcourier.bmp");
	cfg_parser.set(CFG_FILE_INPUT_HELP, "../../media-tokamak/input_help.png");

	cfg_parser.set(CFG_FILE_SPEED_BK, "../../media-tokamak/speed.png");
    
	cfg_parser.set(MIN_BALL_DISPLAYSPEED, 4.0f);
    cfg_parser.set(MAX_BALL_DISPLAYSPEED, 10.0f);
    cfg_parser.set(SUPERHIT_KEY, "A");
    cfg_parser.set(ACC_SPIN_THRESHOLD_1, 600);
    cfg_parser.set(ACC_SPIN_THRESHOLD_2, 800);
    
    cfg_parser.set(NPC_SPIN_HITBACK_POSSI, 50);
    cfg_parser.set(SPIN_HITBACK_STRENGTH, 900);
	cfg_parser.set(CFG_GAMELIST_BK, "../../media-tokamak/gamelist_bg.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_ARROW_UP, "../../media-tokamak/scroll_arrow_up.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_ARROW_DOWN, "../../media-tokamak/scroll_arrow_down.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_BUTTON_BACK, "../../media-tokamak/gamelist_button_back.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_BUTTON_BACK_FOCUSED, "../../media-tokamak/gamelist_button_back_focused.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_BUTTON_USERLIST, "../../media-tokamak/gamelist_button_userlist.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_BUTTON_USERLIST_FOCUSED, "../../media-tokamak/gamelist_button_userlist_focused.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_BUTTON_CREATE, "../../media-tokamak/gamelist_button_create.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_BUTTON_CREATE_FOCUSED, "../../media-tokamak/gamelist_button_create_focused.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_BUTTON_LIST, "../../media-tokamak/gamelist_button_list.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_BUTTON_LIST_FOCUSED, "../../media-tokamak/gamelist_button_list_focused.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_ICON_GAME_SELECTED, "../../media-tokamak/gamelist_game_selected.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_ICON_GAME_WAITING, "../../media-tokamak/gamelist_game_waiting.png", CFG_GAMELIST);
	cfg_parser.set(CFG_GAMELIST_ICON_ROOM, "../../media-tokamak/gamelist_icon_room.png", CFG_GAMELIST);

	cfg_parser.set(CFG_USERLIST_BK, "../../media-tokamak/userlist_bg.png", CFG_GAMELIST);
	cfg_parser.set(CFG_USERLIST_ICON_USER_SELECTED, "../../media-tokamak/userlist_selected.png", CFG_GAMELIST);
	cfg_parser.set(CFG_USERLIST_ICON_STATUS_WAITING, "../../media-tokamak/gamelist_game_waiting.png", CFG_GAMELIST);
	cfg_parser.set(CFG_USERLIST_ICON_STATUS_PLAYING, "../../media-tokamak/user_state_playing.png", CFG_GAMELIST);
	cfg_parser.set(CFG_USERLIST_ICON_STATUS_IDLE, "../../media-tokamak/user_state_idle.png", CFG_GAMELIST);

	cfg_parser.set(CFG_FILE_NETWORK_WAITING1, "../../media-tokamak/network_waiting01.png");
	cfg_parser.set(CFG_FILE_NETWORK_WAITING2, "../../media-tokamak/network_waiting02.png");


    cfg_parser.set("ACC_DELAY_TIMES", 2.0f);

	cfg_parser.set(CFG_GAME_SERVER_ADDR, "192.168.1.6");
	cfg_parser.set(CFG_GAME_SERVER_PORT, "10001");
	cfg_parser.set(CFG_CLIENT_PORT, "5000");

	cfg_parser.set(CFG_FILE_LOGIN_FAILED, "../../media-tokamak/login_failed.png", CFG_LOADING);
	cfg_parser.set(CFG_FILE_SERVER_CONNECTION_FAILED, "../../media-tokamak/server_connection_failed.png", CFG_LOADING);
	cfg_parser.set(CFG_FILE_NETWORK_DROPPED, "../../media-tokamak/network_dropped.png");
	cfg_parser.set(CFG_FILE_NETWORK_CONNECTING, "../../media-tokamak/network_connecting.png");
	cfg_parser.set(CFG_FILE_NETWORK_RECONNECTING, "../../media-tokamak/network_reconnecting.png");
	cfg_parser.set(CFG_FILE_DIALOG_BK512x128, "../../media-tokamak/512x128bg.png");
	cfg_parser.set(CFG_FILE_GAME_TERMINATED, "../../media-tokamak/game_terminated.png");

	cfg_parser.set(CFG_DEFAULT_USERNAME, "Wilson");
	cfg_parser.set(CFG_DEFAULT_PASSWORD, "Wilson");

	cfg_parser.set(CFG_FILE_REMOTE_RECONNECTING, "../../media-tokamak/remote_reconnecting.png");
	cfg_parser.set(CFG_FILE_REMOTE_RECONNECT_FAILED, "../../media-tokamak/remote_reconnect_failed.png");
	
	cfg_parser.set(CFG_CAMERA_CENTER_Y, 76.0f);
	cfg_parser.set(CFG_CAMERA_VECTOR0_Y, 450.0f);
	cfg_parser.set(CFG_CAMERA_VECTOR3_Y, 543.919f);//277.421f);
	cfg_parser.set(CFG_CAMERA_VECTOR3_Z, -1718.997);//-1547.103f);
	cfg_parser.set(CFG_CAMERA_DSTVECTOR_X, -423.183f);
	cfg_parser.set(CFG_CAMERA_DSTVECTOR_Y, 229.023f);

    cfg_parser.set("FILE_PLAYER_SHADOW", "../../media-tokamak/shadow.md2");
    cfg_parser.set("FILE_PLAYER_SHADOW_TEXTURE", "../../media-tokamak/shadow.tga");    

	cfg_parser.set(FILE_USERDETAIL_BK, "../../media-tokamak/user_op_bg.png", CFG_USERDETAIL);
	cfg_parser.set(FILE_USER_OP_INVITE, "../../media-tokamak/user_op_invite.png", CFG_USERDETAIL);
	cfg_parser.set(FILE_USER_OP_INVITE_DISABLED, "../../media-tokamak/user_op_invite_disabled.png", CFG_USERDETAIL);
	cfg_parser.set(FILE_USER_OP_JOIN, "../../media-tokamak/user_op_join.png", CFG_USERDETAIL);
	cfg_parser.set(FILE_USER_OP_JOIN_DISABLED, "../../media-tokamak/user_op_join_disabled.png", CFG_USERDETAIL);
	cfg_parser.set(FILE_USER_OP_WATCH, "../../media-tokamak/user_op_watch.png", CFG_USERDETAIL);
	cfg_parser.set(FILE_USER_OP_WATCH_DISABLED, "../../media-tokamak/user_op_watch_disabled.png", CFG_USERDETAIL);
	cfg_parser.set(FILE_USER_OP_BACK, "../../media-tokamak/user_op_back.png", CFG_USERDETAIL);
	cfg_parser.set(FILE_BUTTON_SPRITE, "../../media-tokamak/button_sprites.png", CFG_USERDETAIL);


	// Tips
	cfg_parser.set(FILE_TIPS_SERVEBALL1, "../../media-tokamak/tips_faqiu1.png");
	cfg_parser.set(FILE_TIPS_SERVEBALL2, "../../media-tokamak/tips_faqiu2.png");
	cfg_parser.set(FILE_TIPS_SERVEBALL3, "../../media-tokamak/tips_faqiu3.png");

	cfg_parser.set(FILE_TIPS_SWINGBALL1, "../../media-tokamak/tips_huipai1.png");
	cfg_parser.set(FILE_TIPS_SWINGBALL2, "../../media-tokamak/tips_huipai2.png");
	cfg_parser.set(FILE_TIPS_SWINGBALL3, "../../media-tokamak/tips_huipai3.png");

	cfg_parser.set(FILE_TIPS_SPINBALL1, "../../media-tokamak/zuoxuanzhuan1.png");
	cfg_parser.set(FILE_TIPS_SPINBALL2, "../../media-tokamak/zuoxuanzhuan2.png");
	cfg_parser.set(FILE_TIPS_SPINBALL3, "../../media-tokamak/youxuanzhuan2.png");

	cfg_parser.set(FILE_TIPS_BUTTON1, "../../media-tokamak/remote_button1.png");
	cfg_parser.set(FILE_TIPS_BUTTON2, "../../media-tokamak/remote_button2.png");
	cfg_parser.set(FILE_TIPS_PLUS, "../../media-tokamak/tips_plus.png");

	// Remote lib
	cfg_parser.set(FILE_REMOTE_LIB, "./libRemoteInput.so");
	cfg_parser.set(CFG_USE_WIIMOTE, 0);
}


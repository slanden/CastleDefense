#pragma once
#include <string>
//origin = Shelby Landen

//game window dimensions
const int g_screenW = 600;
const int g_screenH = 800;

//scale to screen dimensions
const int bgdScale = g_screenW - 128;
const int objScale = bgdScale / 16;

//Variable declarations
extern float g_leftBounds;
extern float g_rightBounds;
extern float g_castleLoc;

//player stats
extern int kills;	  //enemies killed
extern int lvl_kills; // enemies killed during current level
extern int level;	  //current level of progress in the game

//castle health
extern int g_castleHealth;

//game states
enum e_state
{
	e_menu,
	e_scores,
	e_controls,
	e_newgame,
	e_game,
	e_win,
	e_lose,
	e_pause,
	e_end,
	e_nameentry,
	e_exit
};

extern e_state g_currentState;

//controls
 extern bool m_pressed;
 extern bool m_tarPressed;

//game controls
 extern enum controls
 {
	 e_none, e_left = 'A', e_right = 'D', e_up = 'W', e_down = 'S', e_shoot = KEY_SPACE, e_back = 'Q', e_tar = 'F', e_enter = 'C'
 };

 extern float m_fDelay, m_fTimer, m_lvlTimer; // Firing controls

 /////////////////////////////////////////////////////////
 // IO
 ////////////////////////////////////////////////////////

 //textbox
 extern std::string g_playerName;
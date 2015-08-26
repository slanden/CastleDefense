#include "AIE.h"
#include <iostream>
#include <math.h>
#include "Decl.h"
#include "Player.h"
#include "Assets.h"
#include "Castle.h"
#include "Projectile.h"
#include "Enemy.h"
#include "ScoreData.h"
#include <Windows.h>
#include "Textbox.h"

//origin = AIE
//author = Shelby Landen

//variable definitions
float g_leftBounds;
float g_rightBounds;
float g_castleLoc;
int g_castleHealth;
int kills = 0;
int lvl_kills;
int level;
int g_enemyRanks;
int g_numEnemies;
std::string g_playerName = "Default";

e_state g_currentState = e_menu;

//check collision for menu buttons
float dist(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main( int argc, char* argv[] )
{	
	Initialise(g_screenW, g_screenH, false, "Castle Defense");


    SetBackgroundColour(SColour(0, 0, 0, 255));

	Asset::getInstance().Load("background", "./images/background_grass.png", g_screenW, g_screenH);
	Asset::getInstance().Load("castle", "./images/castle.png", bgdScale, bgdScale);
	Asset::getInstance().Load("player", "./images/cannon.png", objScale, objScale);
	Asset::getInstance().Load("cannonball", "./images/cannon_ball.png", bgdScale / 74, (bgdScale / 74));
	Asset::getInstance().Load("reticle", "./images/reticule.png", objScale, objScale);
	Asset::getInstance().Load("dead_1", "./images/enemy/enemy_dead1.png", objScale, objScale);
	Asset::getInstance().Load("dead_2", "./images/enemy/enemy_dead2.png", objScale, objScale);
	Asset::getInstance().Load("dead_3", "./images/enemy/enemy_dead3.png", objScale, objScale);
	Asset::getInstance().Load("dead_4", "./images/enemy/enemy_dead4.png", objScale, objScale);
	Asset::getInstance().Load("dead_1_xray", "./images/enemy/enemy_dead1_xray.png", objScale, objScale);
	Asset::getInstance().Load("dead_2_xray", "./images/enemy/enemy_dead2_xray.png", objScale, objScale);
	Asset::getInstance().Load("dead_3_xray", "./images/enemy/enemy_dead3_xray.png", objScale, objScale);
	Asset::getInstance().Load("dead_4_xray", "./images/enemy/enemy_dead4_xray.png", objScale, objScale);
	Asset::getInstance().Load("enemy_w1", "./images/enemy/enemy_walk1.png", objScale, objScale);
	Asset::getInstance().Load("enemy_w2", "./images/enemy/enemy_walk2.png", objScale, objScale);
	Asset::getInstance().Load("enemy_w3", "./images/enemy/enemy_walk3.png", objScale, objScale);
	Asset::getInstance().Load("enemy_w4", "./images/enemy/enemy_walk4.png", objScale, objScale);
	Asset::getInstance().Load("enemy_w1_xray", "./images/enemy/enemy_walk1_xray.png", objScale, objScale);
	Asset::getInstance().Load("enemy_w2_xray", "./images/enemy/enemy_walk2_xray.png", objScale, objScale);
	Asset::getInstance().Load("enemy_w3_xray", "./images/enemy/enemy_walk3_xray.png", objScale, objScale);
	Asset::getInstance().Load("enemy_w4_xray", "./images/enemy/enemy_walk4_xray.png", objScale, objScale);
	Asset::getInstance().Load("enemy_attack1", "./images/enemy/enemy_attack1.png", objScale, objScale);
	Asset::getInstance().Load("enemy_attack2", "./images/enemy/enemy_attack2.png", objScale, objScale);
	Asset::getInstance().Load("enemy_attack3", "./images/enemy/enemy_attack3.png", objScale, objScale);
	Asset::getInstance().Load("playerlives", "./images/player/man_idle.png", objScale, objScale);
	Asset::getInstance().Load("menu_play", "./images/menu/text_play.png", 128, 64);
	Asset::getInstance().Load("menu_scores", "./images/menu/text_scores.png", 128, 64);
	Asset::getInstance().Load("menu_controls", "./images/menu/text_controls.png", 128, 64);
	Asset::getInstance().Load("menu_exit", "./images/menu/text_exit.png", 128, 64);
	Asset::getInstance().Load("blood", "./images/blood1.png", objScale, objScale);
	Asset::getInstance().Load("tar", "./images/cannon_ball.png", bgdScale / 74, (bgdScale / 74));


	
	Castle castle(g_screenW / 2, g_screenH / 5);
	Player player(castle.getX(), castle.getY() + (bgdScale / 3.25));

	Textbox name_entry_textbox(g_screenW / 3, g_screenH / 1.5 - 2.5 * 40);

	//set player x bounderies
	g_leftBounds = castle.getX() - (bgdScale / 4);
	g_rightBounds = castle.getX() + (bgdScale / 4);

	//castle gate location
	g_castleLoc = castle.getY() + (bgdScale / 4);


	double mouseX, mouseY;

	ScoreDatabase::score().Open("HighScoreDatabase.db");

    do
    {
		ClearScreen();
		float dt = GetDeltaTime();

		switch (g_currentState)
		{
			case e_menu:
			{

				Asset::getInstance().Draw("menu_play", (g_screenW / 2), (g_screenH / 2) + bgdScale / 8);
				Asset::getInstance().Draw("menu_scores", (g_screenW / 2), (g_screenH / 2));
				Asset::getInstance().Draw("menu_controls", (g_screenW / 2), (g_screenH / 2) - bgdScale / 8);
				Asset::getInstance().Draw("menu_exit", (g_screenW / 2), (g_screenH / 2) - bgdScale / 4);
			


				if (GetMouseButtonDown(MOUSE_BUTTON_1))
				{
				
					GetMouseLocation(mouseX, mouseY);
					Asset::getInstance().Draw("reticle", mouseX, g_screenH - mouseY);
					if (GetMouseButtonDown(MOUSE_BUTTON_1))
					{

						if (dist(mouseX, g_screenH - mouseY, g_screenW / 2, (g_screenH / 2) + bgdScale / 8) < 32)
						{
							g_currentState = e_newgame;
						}

						if (dist(mouseX, g_screenH - mouseY, (g_screenW / 2), (g_screenH / 2)) < 32)
						{
							g_currentState = e_scores;
						}

						if (dist(mouseX, g_screenH - mouseY, (g_screenW / 2), (g_screenH / 2) - bgdScale / 8) < 32)
						{
							g_currentState = e_controls;
						}

						if (dist(mouseX, g_screenH - mouseY, (g_screenW / 2), (g_screenH / 2) - bgdScale / 4) < 32)
						{
							g_currentState = e_exit;
						}
					}
				}

			}break;

			case e_controls:
			{
				std::stringstream c;
				std::string key_shoot;
				
				if (e_shoot == KEY_SPACE)
					key_shoot = "space";

				DrawString("Press 'Q' to go back", 0, g_screenH);
				DrawString("Controls", g_screenW / 2.5, g_screenH / 1.1);

				char t[2] = {e_left,'\0'}; // char *t = "a";
				DrawString("move left", g_screenW / 40, g_screenH / 1.2 - 1 * 40);
				DrawString(t, g_screenW / 1.95, g_screenH / 1.2 - 1 * 40);

				t[0] = e_right; // t[0] = 'd';
				DrawString("move right", g_screenW / 40, g_screenH / 1.2 - 2 * 40);
				DrawString(t, g_screenW / 1.95, g_screenH / 1.2 - 2 * 40);

				DrawString("Charge cannon", g_screenW / 40, g_screenH / 1.2 - 3 * 40);
				DrawString(key_shoot.c_str(), g_screenW / 1.95, g_screenH / 1.2 - 3 * 40);

				t[0] = e_up;
				DrawString("Aim cannon up", g_screenW / 40, g_screenH / 1.2 - 4 * 40);
				c << t << "(while holding " << key_shoot << ")";
				DrawString(c.str().c_str(), g_screenW / 1.95, g_screenH / 1.2 - 4 * 40);
				c.str(std::string());											//sets stringstream string to empty string
				c.clear();														//clears end of file flag so that new data can be written in stream

				t[0] = e_down;
				DrawString("Aim cannon down", g_screenW / 40, g_screenH / 1.2 - 5 * 40);
				c << t << "(while holding " << key_shoot << ")";
				DrawString(c.str().c_str(), g_screenW / 1.95, g_screenH / 1.2 - 5 * 40);
				c.str(std::string());
				c.clear();

				DrawString("Fire", g_screenW / 40, g_screenH / 1.2 - 6 * 40);
				c << "release " << key_shoot;
				DrawString(c.str().c_str(), g_screenW / 1.95, g_screenH / 1.2 - 6 * 40);
				c.str(std::string());
				c.clear();


				if (IsKeyDown('Q'))
					g_currentState = e_menu;
			}break;

			case e_scores:
			{
				DrawString("Press 'Q' to go back", 0, g_screenH);
				DrawString("Scores", g_screenW/2.5, g_screenH/1.1);
				ScoreDatabase::score().DrawScores();

				if (IsKeyDown('Q'))
					g_currentState = e_menu;
			}break;
		

			case e_newgame:		
		
				Enemy::updateAll(dt);
				Enemy::SpawnEnemy(g_screenW / 2, g_screenH + bgdScale/4.5, -10, "enemy", 8, 3);
				//Enemy::SpawnEnemy(g_screenW / 2, g_screenH - bgdScale / 1, -10, "enemy", 8, 3); //spawn enemies close for debuggin'
				g_currentState = e_nameentry;

				castle = Castle(g_screenW / 2, g_screenH / 5);
				player = Player(castle.getX(), castle.getY() + (bgdScale / 3.25));
			
				g_castleHealth = 100;

				kills = 0;
				level = 1;

				name_entry_textbox.clear();
				break;
			case e_nameentry:
				
				name_entry_textbox.update(dt);
				name_entry_textbox.draw();

				DrawString("Enter your name", g_screenW / 3, g_screenH / 1.5 - 1 * 40);

				if (name_entry_textbox.isDone())
				{
					g_currentState = e_game;
					g_playerName = name_entry_textbox.getString();
				}
				break;
			case e_game:
			{
				Asset::getInstance().Draw("background", g_screenW / 2, g_screenH / 2);
				castle.Draw();
				//DrawLine(0, g_castleLoc , g_screenW, g_castleLoc);
				//DrawLine(0, g_castleLoc - 30, g_screenW, g_castleLoc - 30);

				Enemy::updateAll(dt);
				Enemy::drawAll();

				player.Draw();
				player.Update(dt);

				Projectile::updateAll(dt);
				Projectile::drawAll();

				if (IsKeyDown('Q'))
				{
					g_currentState = e_end;
				}
				if (g_castleHealth <= 0)
				{
					g_currentState = e_lose;
				}
			}break;

			case e_pause:
			{
				;
			}break;
			case e_win:
			{
				;
			}break;

			case e_lose:
			{
				Asset::getInstance().Draw("background", g_screenW / 2, g_screenH / 2);
				castle.Draw();
				Enemy::drawAll();
				Projectile::drawAll();
				DrawString("DEFEAT", g_screenW / 2.5, g_screenH / 1.1, SColour(235, 24, 1, 255));
				DrawString("Press 'Q' to go back to the menu", g_screenW / 6, g_screenH / 1.2, SColour(235, 24, 1, 255));

				if (IsKeyDown('Q'))
				{
					g_currentState = e_end;
				}
			}break;

			case e_end:
			{
				
				ScoreDatabase::score().AddScore(g_playerName.c_str(), level, kills);

				g_currentState = e_menu;
			}break;

			case e_exit:
			{
				Asset::getInstance().FreeAll(); //frees up the images out of memory
				Shutdown();

				return 0;
			}
		}
		
    } while(!FrameworkUpdate());


	Asset::getInstance().FreeAll(); //frees up the images out of memory
	ScoreDatabase::score().Close();
    Shutdown();

    return 0;
}

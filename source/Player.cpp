#include "Player.h"
#include "Assets.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Decl.h"
#include <iostream>

//origin = Shelby Landen
bool m_pressed;
bool m_tarPressed;

const int Player::m_maxLives = 3;

void Player::Draw()
{
	Entity::Draw(); //we still want to draw like normal

	// but also want to draw some extra (player lives sprite)
	for (int i = 0; i < m_lives; ++i)
	{
		Asset::getInstance().Draw("playerlives", (g_castleLoc + (bgdScale / 7.5)) + i * 25, g_castleLoc - (bgdScale / 8));
	}

	//draw player progress
	
	std::strcat((char*)str_kills.c_str(), " Enemies killed");
	//puts(str_kills.c_str());
	DrawString(str_kills.c_str(), g_screenW / 18, 0 + (g_screenH / 26), SColour(255, 201, 14, 150));

	std::strcat((char*)str_health.c_str(), " : Castle Health");
	//puts(str_health.c_str());
	DrawString(str_health.c_str(), g_screenW / 18, 0 + (g_screenH / 14), SColour(255, 201, 14, 150));
}



void Player::Update(float dt)
{
	m_speed = 50;
	m_fTimer += dt;

	//updates number of kills, castle health.
	str_kills = std::to_string(kills);
	str_health = std::to_string(g_castleHealth);

	//player movement
	if (IsKeyDown(e_left) && m_xPos > g_leftBounds)
	{
		m_xPos += m_speed * dt * -1;
	}
	if (IsKeyDown(e_right) && m_xPos < g_rightBounds)
	{
		m_xPos += m_speed * dt;
	}

	
	//player cannon
	if (IsKeyDown(e_shoot))
		{		
			//cannon movement
			m_pressed = true;
			Asset::getInstance().Draw("reticle", m_xPos, m_retY);

			if (IsKeyDown('W'))
			{
				m_retY += (m_speed * 2) * dt;	//we can update the variable to make changes
			}
			if (IsKeyDown('S'))
			{
				m_retY += (m_speed * 2) * dt *-1;	//we can update the variable to make changes
			}	
		}

	// Fire the cannon
	if (!IsKeyDown(e_shoot) && m_pressed)
	{
		Projectile::SpawnProjectile(m_xPos, m_yPos, 500, m_retY, 1, 2, "cannonball");
		m_pressed = false;
	}

	//player tar
	if (IsKeyDown(e_tar) && !m_tarPressed)
	{
		m_tarPressed = true;
	}

	// Drop the tar
	if (!IsKeyDown(e_tar) && m_tarPressed)
	{
		Projectile::SpawnProjectile(m_xPos, m_yPos, 100, g_castleLoc - 35, 2, 2, "tar");
		m_tarPressed = false;
	}

	//level progression
	if (lvl_kills == g_numEnemies)
	{
		m_lvlTimer += dt;

		DrawString("Level Up!", g_screenW / 2.5, g_screenH / 1.1, SColour(255, 201, 14, 150));
		if (m_lvlTimer > m_fDelay*3)
		{
			Player::lvlUp();
			m_lvlTimer = 0;
			level++;
			lvl_kills = 0;
		}
	}
}

void Player::lvlUp()
{
	g_enemyRanks += 1;
	Enemy::SpawnEnemy(g_screenW / 2, g_screenH + bgdScale / 4.5, -10, "enemy", 8, g_enemyRanks);
}
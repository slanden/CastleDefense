#include "Enemy.h"
#include "Assets.h"
#include "Decl.h"

//origin = Shelby Landen
//author = Mr. Marco

Enemy *Enemy::enemies[max_enemies];

//updates all enemies, deleting them from memory when target destination is reached or if they're killed
void Enemy::updateAll(float dt)
{
	for (int i = 0; i < max_enemies; ++i)
		if (enemies[i] != nullptr)
		{
			enemies[i]->Update(dt);

			if (enemies[i] != nullptr && ( g_currentState != e_game))
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
}

//draws updated enemies to screen
void Enemy::drawAll()
{
	for (int i = 0; i < max_enemies; ++i)
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
}

//spawns an enemy or number of enemies with given characteristics
void Enemy::SpawnEnemy(float x, float y, float speed, const char *spritename, int n_spawn, int ranks)
{

	for (int q = 0; q < ranks; q++)
	{
		//space enemies evenly from the center
		int j = 0;
		int spacing = 30;
		int space = x - spacing * ((n_spawn - 1) / 2.0f);

		for (int i = 0; i < max_enemies && j < n_spawn; ++i)
			if (enemies[i] == nullptr)
			{
			j++;
			enemies[i] = new Enemy(space, y, speed, spritename);
			space += spacing;
			}

		y -= 40;
	}
	//keep track of # of enemies
	g_numEnemies = n_spawn * ranks;
	g_enemyRanks = ranks;
}

//draws individual enemy information (alive,dead, etc.)
void Enemy::Draw()
{
	//draws the alive enemy walk animation sprites
	if (m_alive)
	{
		//xray vision of live enemies at the castle wall
		if (m_yPos <= g_castleLoc - (bgdScale / 4) + bgdScale / 3.13)
		{
			//enemies at the gate attack the castle
			if (m_yPos <= g_castleLoc - 30)
			{
				switch (live_sprite)
				{
				case 1:	Asset::getInstance().Draw("enemy_attack1", m_xPos, m_yPos); break;
				case 2:	Asset::getInstance().Draw("enemy_attack2", m_xPos, m_yPos); break;
				case 3:	Asset::getInstance().Draw("enemy_attack3", m_xPos, m_yPos); break;
				case 4:	Asset::getInstance().Draw("enemy_attack2", m_xPos, m_yPos); break;
				}
			}
			//not at the gate yet
			else
			{
				switch (live_sprite)
				{
				case 1:	Asset::getInstance().Draw("enemy_w1_xray", m_xPos, m_yPos); break;
				case 2:	Asset::getInstance().Draw("enemy_w2_xray", m_xPos, m_yPos); break;
				case 3:	Asset::getInstance().Draw("enemy_w3_xray", m_xPos, m_yPos); break;
				case 4:	Asset::getInstance().Draw("enemy_w4_xray", m_xPos, m_yPos); break;
				}
			}

		}
		//regular view of live enemies
		else
		{
			switch (live_sprite)
			{
			case 1:	Asset::getInstance().Draw("enemy_w1", m_xPos, m_yPos); break;
			case 2:	Asset::getInstance().Draw("enemy_w2", m_xPos, m_yPos); break;
			case 3:	Asset::getInstance().Draw("enemy_w3", m_xPos, m_yPos); break;
			case 4:	Asset::getInstance().Draw("enemy_w4", m_xPos, m_yPos); break;
			}
		}
	}
	//draws random dead sprites
	else
	{
		//xray vision of dead enemies at castle wall
		if (m_yPos <= g_castleLoc - (bgdScale / 4) + bgdScale / 3.13)
		{
			switch (dead_sprite)
			{
			case 1:	Asset::getInstance().Draw("dead_1_xray", m_xPos, m_yPos); break;
			case 2:	Asset::getInstance().Draw("dead_2_xray", m_xPos, m_yPos); break;
			case 3:	Asset::getInstance().Draw("dead_3_xray", m_xPos, m_yPos); break;
			case 4:	Asset::getInstance().Draw("dead_4_xray", m_xPos, m_yPos); break;
			}
		}
		//regular view of dead enemies
		else
		{
			switch (dead_sprite)
			{
			case 1:	Asset::getInstance().Draw("blood", m_xPos, m_yPos); Asset::getInstance().Draw("dead_1", m_xPos, m_yPos); break;
			case 2:	Asset::getInstance().Draw("blood", m_xPos, m_yPos); Asset::getInstance().Draw("dead_2", m_xPos, m_yPos); break;
			case 3:	Asset::getInstance().Draw("blood", m_xPos, m_yPos); Asset::getInstance().Draw("dead_3", m_xPos, m_yPos); break;
			case 4:	Asset::getInstance().Draw("blood", m_xPos, m_yPos); Asset::getInstance().Draw("dead_4", m_xPos, m_yPos); break;
			}
		}
	}
}

//updates individual enemy for movement, alive or dead state, damage dealt to castle
void Enemy::Update(float dt)
{
	
	timing += dt;
	h_timer += dt;
	if (timing > 0.16f)
	{
		live_sprite %= 4;
		live_sprite++;
		timing = 0;
	}
	//move enemies forward
	if (m_yPos > g_castleLoc - 35 && m_alive)
	{
		m_yPos += m_speed * dt;
	}

	if (!m_alive && !m_recentlyDied)
	{
		m_recentlyDied = true;
		dead_sprite = rand() % 4 + 1;
	}

	//deal damage to castle when at the gate
	if (m_yPos <= g_castleLoc -35 && m_alive && g_castleHealth >=1 && h_timer > 1.0f)
	{
		g_castleHealth -= 1;
			
		h_timer = 0;
	}
}
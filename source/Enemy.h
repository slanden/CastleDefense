#pragma once
#include "Entity.h"
#include "AIE.h"
#include "Decl.h"

//origin = Shelby Landen

const int max_enemies = 128;
extern int g_numEnemies;
extern int g_enemyRanks;

class Enemy : public Entity
{
	bool m_recentlyDied;
	int dead_sprite;
	int live_sprite;
	float timing;
	float h_timer;

public:
	
	int rankPos;
	static Enemy *enemies[];
	static void updateAll(float dt);
	static void drawAll();

	// characteristics of enemy being spawned and their formation(how many in a rank, number of ranks)
	static void SpawnEnemy(float x, float y, float speed, const char *spritename = "enemy", int n_spawn = 8, int ranks = 1);
	
	
	void Draw();
	
	// characteristics of an individual enemy
	Enemy(float a_xPos, float a_yPos, float a_speed, const char *spritename) : Entity(spritename)
	{
		m_recentlyDied = false;
		m_xPos = a_xPos;
		m_yPos = a_yPos;
		m_speed = a_speed;
		timing = 0;
		h_timer = 0;
	}

	void Update(float dt);
};
#pragma once
#include "Entity.h"
#include "AIE.h"

//origin = Shelby Landen

class Projectile : public Entity
{

public:
	static std::vector<Projectile*> projectiles;
	static std::vector<Projectile*> Projectile::tar;
	//static Projectile *projectiles[];
	//static std::vector<Projectile*> projectiles;
	static void updateAll(float dt);
	static void drawAll();

	// And to the spawning function
	static void SpawnProjectile(float x, float y, float speed, float a_killzone, int a_type, float a_drag = 2, const char *spritename = "cannonball");

	float m_killzone;
	float m_drag;
	int m_type;

	// characteristics of a projectile
	Projectile(float a_xPos, float a_yPos, float a_speed, float a_killzone, int a_type, float a_drag, const char *spritename) : Entity(spritename)
	{
		m_killzone = a_killzone;
		m_xPos = a_xPos;
		m_yPos = a_yPos;
		m_speed = a_speed;
		m_drag = a_drag;
		m_type = a_type;
	}

	//bool collision(const char *sprite1, const char *sprite2);
	void Update(float dt);
};
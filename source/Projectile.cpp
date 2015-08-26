#include "Projectile.h"
#include "Assets.h"
#include "Decl.h"
#include "Enemy.h"
#include <cmath>

//origin = Shelby Landen
//author = Mr. Marco

std::vector<Projectile*> Projectile::projectiles(128);
std::vector<Projectile*> Projectile::tar(128);


//updates all projectiles, deleting them from memory when target area is reached
void Projectile::updateAll(float dt)
{

	for (auto it = projectiles.begin(); it != projectiles.end(); it++)
	{
		if ((*it) != nullptr)
		{
			(*it)->Update(dt);

			if ((*it)->m_yPos > (*it)->m_killzone && (*it)->m_type == 1 )
			{
				delete (*it);
				(*it) = nullptr;
			}
		}
	}

	for (auto it = tar.begin(); it != tar.end(); it++)
	{
		if ((*it) != nullptr)
		{
			(*it)->Update(dt);

			if ((*it)->m_yPos < (*it)->m_killzone && (*it)->m_type == 2)
			{
				delete(*it);
				(*it) = nullptr;
			}
		}
	}
}

//draws projectile state that was updated in update function
void Projectile::drawAll()
{
	for (int i = 0; i < 128; ++i)
	{
		if (projectiles[i] != nullptr)
			projectiles[i]->Draw();

		if (tar[i] != nullptr)
			tar[i]->Draw();
	}
}

//add new projectile to memory from array of maximum projectiles
void Projectile::SpawnProjectile(float x, float y, float speed, float killzone, int type, float drag, const char *spritename)
{
	for (int i = 0; i < 128; ++i)
	{
		if (projectiles[i] == nullptr && spritename == "cannonball")
		{
			projectiles[i] = new Projectile(x, y, speed, killzone, type, drag, spritename);
			return;
		}

		if (tar[i] == nullptr && spritename == "tar")
		{
			tar[i] = new Projectile(x, y, speed, killzone, type, drag, spritename);
			return;
		}
	}
}

//updates individual projectile. Position,movement, point of death checks (cannonball killzone)
void Projectile::Update(float dt)
{
	//change size of projectile in-game for trajectory effect
	m_w = Asset::getInstance().GetWidth("cannonball");
	m_h = Asset::getInstance().GetHeight("cannonball");

	//m_speed -= m_drag * dt; have the drag act against the speed.

	if (m_w < 64 && m_h < 64)
	{
		++m_w;
		++m_w;
	}
	else if (m_w > 16 && m_h > 16)
	{
		--m_w;
		--m_h;
	}


	//move projectile forward
	 if (m_yPos < m_killzone && m_drag < m_speed)
	{
		//m_drag++;
		//m_speed -= 2;
		m_yPos += m_speed * dt;
	}

	 //move tar
	 if (m_yPos > m_killzone && m_type == 2)
	 {
		 m_yPos -= m_speed * dt;
	 }
	
	for (int i = 0; i < max_enemies; ++i)
	{
		//checks to see if cannonball has reached the target area before greeting the enemy with instant death.
		if (m_yPos >= m_killzone - Asset::getInstance().GetWidth("enemy_w1") / 2 && m_yPos <= m_killzone + Asset::getInstance().GetWidth("enemy_w1") / 2)
		{
			//kill enemies!
			if (Enemy::enemies[i] != nullptr && Enemy::enemies[i]->m_alive && collides(Enemy::enemies[i]))
			{
				Enemy::enemies[i]->m_alive = false;
				m_alive = false;
				kills++;
				lvl_kills++;
			}
		}
	}
}
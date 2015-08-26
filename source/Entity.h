#pragma once
#include <string>
#include <vector>

//origin = Shelby Landen

class Entity
{
protected:

	float m_xPos, m_yPos;
	float m_w, m_h;
	float m_speed;
	std::string m_name;

public:

	bool m_alive;
	Entity(const char *a_name)
	{
		m_alive = true;
		m_name = a_name;
	}

	virtual void Draw();

	float getY() { return m_yPos; }
	float getX() { return m_xPos; }
	float getW() { return m_w; }
	float getH() { return m_h; }

	virtual void Update(float dt) = 0;


	bool collides(const Entity *e);
};
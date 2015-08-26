#pragma once
#include "Entity.h"
#include "AIE.h"
#include "Decl.h"

//origin = Shelby Landen

class Player : public Entity
{
private:
	bool m_released;
	float m_retY; // reticule 'y' position
	std::string str_kills; //string of enemies killed
	std::string str_health; //health of the castle
protected:

	//game controls
	enum controls
	{
		e_none, e_left = 'A', e_right = 'D', e_shoot = KEY_SPACE, e_back = 'Q', e_tar = 'F'
	} action = e_none;

	float m_fDelay, m_fTimer, m_lvlTimer; // Firing controls

public:
	std::string str_player;
	static const int m_maxLives;
	int m_lives;

	static void updateAll(float dt);
	

	Player(float a_xPos, float a_yPos) : Entity("player") 
	{ 
		m_xPos = a_xPos, m_yPos = a_yPos;
		m_lives = m_maxLives;
		m_fDelay = 1.25f;
		m_fTimer = 0.0f;
		m_lvlTimer = 0.0f;
		m_pressed = false;
		m_tarPressed = false;
		m_retY = m_yPos + (bgdScale / 10);
	}

	void SetControls(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_shoot);
	void lvlUp(/*int a_kills*/);
	
	void Draw(); //overrides or replaces the draw in entity.h
	void Update(float dt);

};
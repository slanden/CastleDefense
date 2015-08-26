#pragma once
#include "Entity.h"
#include "AIE.h"
#include "Decl.h"

//origin = Shelby Landen

class Castle : public Entity
{
	int m_health;

public:

	//castle object so the position can be used in the main function for object scale, position, etc.
	Castle(float a_xPos, float a_yPos) : Entity("castle")
	{
		m_xPos = a_xPos, m_yPos = a_yPos;
	}

	void Update(float dt);

};
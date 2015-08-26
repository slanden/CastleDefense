#include "Entity.h"	
#include "Assets.h"

//origin = Shelby Landen

//draws an asset at given x,y positions
void Entity::Draw()
{
	Asset::getInstance().Draw(m_name.c_str(), m_xPos, m_yPos);
}

//checks to see if any two enteties collide
bool Entity::collides(const Entity *e)
{
	int sp1_rad = Asset::getInstance().GetWidth(m_name.c_str());
	int sp2_rad = Asset::getInstance().GetWidth(e->m_name.c_str());

	float base_x = e->m_xPos - m_xPos;
	float base_y = e->m_yPos - m_yPos;

	float dist = sqrt((base_x * base_x) + (base_y * base_y));

	return dist < sp1_rad + sp2_rad;
}
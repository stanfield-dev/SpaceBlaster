#include "Background.h"
#include "Manager.h"

Background::Background(int type, float x, float y, float z)
	: Entity(type, x, y, z)
{
	Manager::addEntity(this);
}

Background::~Background()
{
}

void Background::scrollBackground()
{
	m_vertexArray[3]  += 0.002f;				// LLx
	m_vertexArray[8]  += 0.002f;				// LRx
	m_vertexArray[13] += 0.002f;				// URx
	m_vertexArray[18] += 0.002f;				// ULx
}

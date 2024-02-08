#include "Entity.h"

Entity::Entity(int type, float x, float y, float z)
	: m_type(type), m_positionX(x), m_positionY(y), m_positionZ(z)
{
}

Entity::~Entity()
{
}

float Entity::getPositionX() const
{
	return m_positionX;
}

float Entity::getPositionY() const
{
	return m_positionY;
}

float Entity::getGunPosition() const
{
	return m_positionY + (m_positionYOffset / 2);
}

void Entity::setPositionX(float x)
{
	m_positionX = x;
}

void Entity::setPositionY(float y)
{
	m_positionY = y;
}

float* Entity::updateVertexArray()
{
	float newPosX = getPositionX();
	float newPosY = getPositionY();

	m_vertexArray[0] = newPosX;							// quad LL
	m_vertexArray[1] = newPosY;
	m_vertexArray[2] = m_spriteX;						// texture LL
	m_vertexArray[3] = m_spriteY;

	m_vertexArray[5] = newPosX + m_positionXOffset;		// LR
	m_vertexArray[6] = newPosY;
	m_vertexArray[7] = m_spriteX + m_spriteXOffset;
	m_vertexArray[8] = m_spriteY;

	m_vertexArray[10] = newPosX + m_positionXOffset;	// UR
	m_vertexArray[11] = newPosY + m_positionYOffset;
	m_vertexArray[12] = m_spriteX + m_spriteXOffset;
	m_vertexArray[13] = m_spriteY + m_spriteYOffset;

	m_vertexArray[15] = newPosX;						// UL
	m_vertexArray[16] = newPosY + m_positionYOffset;
	m_vertexArray[17] = m_spriteX;
	m_vertexArray[18] = m_spriteY + m_spriteYOffset;

	return m_vertexArray;
}

void Entity::fireEngines()
{
	if (m_spriteX + m_spriteXOffset >= 1.0f) {
		m_spriteX = 0.0f;
	}
	else {
		m_spriteX += m_spriteXOffset;
	}

	m_vertexArray[2] = m_spriteX;						// LLx
	m_vertexArray[7] = m_spriteX + m_spriteXOffset;		// LRx
	m_vertexArray[12] = m_spriteX + m_spriteXOffset;	// URx
	m_vertexArray[17] = m_spriteX;						// ULx
}

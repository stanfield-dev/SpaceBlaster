#include "Explosion.h"
#include "EntityManager.h"

Explosion::Explosion(int type, float x, float y, float z)
	: Entity(type, x, y, z)
{
	m_displayWidth = EXPLOSIONWIDTH;
	m_displayHeight = EXPLOSIONHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_spriteSheetWidth = 1664.0f;
	m_spriteSheetHeight = 128.0f;
	m_spriteWidth = 128.0f;
	m_spriteHeight = 128.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	updateVertexArray();

	EntityManager::addEntityToRegistry(this);
}

Explosion::~Explosion()
{
}


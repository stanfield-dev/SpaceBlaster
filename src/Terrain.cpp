#include "Terrain.h"
#include "EntityManager.h"

Terrain::Terrain(int type, float x, float y, float z)
	: Entity(type, x, y, z)
{
	m_displayWidth = SCREENWIDTH;
	m_displayHeight = 128.0f;
	m_positionXOffset = (m_displayWidth / SCREENWIDTH) * 2;
	m_positionYOffset = (m_displayHeight / SCREENHEIGHT) * 2;

	m_spriteSheetWidth = 2048.0f;
	m_spriteSheetHeight = 1536.0f;
	m_spriteWidth = 2048.0f;
	m_spriteHeight = 1536.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	updateVertexArray();

	EntityManager::addEntityToRegistry(this);
}

Terrain::~Terrain()
{
}

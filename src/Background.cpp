#include "Background.h"
#include "EntityManager.h"

Background::Background(int type, float x, float y, float z, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	m_displayWidth = SCREENWIDTH;
	m_displayHeight = SCREENHEIGHT;
	m_positionXOffset = (m_displayWidth / SCREENWIDTH) * 2;
	m_positionYOffset = (m_displayHeight / SCREENHEIGHT) * 2;

	m_spriteSheetWidth = 2048.0f;
	m_spriteSheetHeight = 1536.0f;
	m_spriteWidth = 2048.0f;
	m_spriteHeight = 1536.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	updateVertexArray();

	entityManager->addEntityToRegistry(this);
}

Background::~Background()
{
}

void Background::animateScreen()
{
	m_vertexArray[3]  += 0.002f;				// LLx
	m_vertexArray[9]  += 0.002f;				// LRx
	m_vertexArray[15] += 0.002f;				// URx
	m_vertexArray[21] += 0.002f;				// ULx
}

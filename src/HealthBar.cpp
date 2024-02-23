#include "HealthBar.h"

HealthBar::HealthBar(int type, float x, float y, float z, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	m_displayWidth = HEALTHBARWIDTH;
	m_displayHeight = HEALTHBARHEIGHT;
	m_positionXOffset = (m_displayWidth / SCREENWIDTH) * 2;
	m_positionYOffset = (m_displayHeight / SCREENHEIGHT) * 2;

	m_spriteSheetWidth = 3000.0f;
	m_spriteSheetHeight = 116.0f;
	m_spriteWidth = 1000.0f;
	m_spriteHeight = 116.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	updateVertexArray();

	entityManager->addEntityToRegistry(this);
}

HealthBar::~HealthBar()
{
}

void HealthBar::updateLives(int x)
{
	m_livesRemaining += x;

	if (m_livesRemaining < 1) { // TODO remove top half of if/else, it's just for testing
		m_livesRemaining = 3;
		m_spriteX = 0.0f;
	}
	else {
		m_spriteX = (1 - (m_livesRemaining * m_spriteXOffset));
	}

	m_vertexArray[3] = m_spriteX;						// LLx
	m_vertexArray[9] = m_spriteX + m_spriteXOffset;		// LRx
	m_vertexArray[15] = m_spriteX + m_spriteXOffset;	// URx
	m_vertexArray[21] = m_spriteX;						// ULx

	updateVertexArray();
}

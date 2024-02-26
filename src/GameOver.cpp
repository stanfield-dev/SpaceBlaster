#include "GameOver.h"

GameOver::GameOver(int type, float x, float y, float z, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	m_displayWidth = GAMEOVERWIDTH;
	m_displayHeight = GAMEOVERHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_spriteSheetWidth = 1046.0f;
	m_spriteSheetHeight = 286.0f;
	m_spriteWidth = 1046.0f;
	m_spriteHeight = 143.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	updateVertexArray();

	entityManager->addEntityToRegistry(this);
}

GameOver::~GameOver()
{
}

void GameOver::animateScreen() {
	if (m_frame > 20) {
		if (m_spriteY + m_spriteYOffset >= 1.0f) {
			m_spriteY = 0.0f;
		}
		else {
			m_spriteY += m_spriteYOffset;
		}

		m_vertexArray[4]  = m_spriteY;						// LLx
		m_vertexArray[10] = m_spriteY + m_spriteYOffset;	// LRx
		m_vertexArray[16] = m_spriteY + m_spriteYOffset;	// URx
		m_vertexArray[22] = m_spriteY;						// ULx

		updateVertexArray();

		m_frame = 0;
	}

	m_frame++;
}






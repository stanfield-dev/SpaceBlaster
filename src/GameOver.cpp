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

void GameOver::incrementTimer()
{
	m_timer++;
}

int GameOver::getTimer() const
{
	return m_timer;
}






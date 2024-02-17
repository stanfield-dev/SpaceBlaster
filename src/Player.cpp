#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Player.h"

Player::Player(int type, float x, float y, float z, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	m_displayWidth = PLAYERWIDTH;
	m_displayHeight = PLAYERHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_spriteSheetWidth = 4096.0f;
	m_spriteSheetHeight = 512.0f;
	m_spriteWidth = 512.0f;
	m_spriteHeight = 512.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	updateVertexArray();

	entityManager->addEntityToRegistry(this);
}

Player::~Player()
{
}







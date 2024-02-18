#include "Explosion.h"

Explosion::Explosion(int type, float x, float y, float z, EntityManager* entityManager)
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

	entityManager->addEntityToRegistry(this);
}

Explosion::~Explosion()
{
}

void Explosion::animateExplosion()
{
	m_explosionFrame++;

	if (m_spriteX + m_spriteXOffset >= 1.0f) {
		m_spriteX = 0.0f;
	}
	else {
		m_spriteX += m_spriteXOffset;
	}

	m_vertexArray[3] = m_spriteX;						// LLx
	m_vertexArray[9] = m_spriteX + m_spriteXOffset;		// LRx
	m_vertexArray[15] = m_spriteX + m_spriteXOffset;	// URx
	m_vertexArray[21] = m_spriteX;						// ULx

	updateVertexArray();
}

int Explosion::getExplosionFrame() const
{
	return m_explosionFrame;
}


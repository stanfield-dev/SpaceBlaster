#include "Countdown.h"

Countdown::Countdown(int type, float x, float y, float z, int source, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	m_displayWidth = COUNTDOWNWIDTH;
	m_displayHeight = COUNTDOWNHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_spriteSheetWidth = 288.0f;
	m_spriteSheetHeight = 96.0f;
	m_spriteWidth = 96.0f;
	m_spriteHeight = 96.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	m_countdownSource = source;

	updateVertexArray();

	entityManager->addEntityToRegistry(this);
}

Countdown::~Countdown()
{
}

void Countdown::animateCountdown()
{
	float three = 0.0f;
	float two = m_spriteXOffset;
	float one = (2 * m_spriteXOffset);

	if (m_countdownFrame < 100) {
		m_spriteX = three;
	}
	else if (m_countdownFrame < 200) {
		m_spriteX = two;
	}
	else {
		m_spriteX = one;
	}

	m_countdownFrame++;

	m_vertexArray[3] = m_spriteX;						// LLx
	m_vertexArray[9] = m_spriteX + m_spriteXOffset;		// LRx
	m_vertexArray[15] = m_spriteX + m_spriteXOffset;	// URx
	m_vertexArray[21] = m_spriteX;						// ULx

	updateVertexArray();

	// TODO respawn enemy/player when countdown expires
}

int Countdown::getCountdownFrame() const
{
	return m_countdownFrame;
}


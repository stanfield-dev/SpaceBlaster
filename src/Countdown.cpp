#include "Countdown.h"

Countdown::Countdown(int type, float x, float y, float z, int source, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	m_startTime = std::chrono::steady_clock::now();

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
	m_endTime = std::chrono::steady_clock::now();
	m_elapsedTime = (m_endTime - m_startTime);

	if (m_elapsedTime.count() > 1.0) {
		m_startTime = std::chrono::steady_clock::now();
		m_frame--;
		switch (m_frame) {
			case 2:
				m_spriteX = m_spriteXOffset;
				break;
			case 1:
				m_spriteX = 2 * m_spriteXOffset;
				break;
			default:
				break;
		}

		m_vertexArray[3] = m_spriteX;						// LLx
		m_vertexArray[9] = m_spriteX + m_spriteXOffset;		// LRx
		m_vertexArray[15] = m_spriteX + m_spriteXOffset;	// URx
		m_vertexArray[21] = m_spriteX;						// ULx

		updateVertexArray();
	}
}

int Countdown::getCountdownFrame() const
{
	return m_frame;
}


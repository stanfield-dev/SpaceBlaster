#include "Enemy.h"

#include <math.h>
#include <time.h>

Enemy::Enemy(int type, float x, float y, float z, EntityManager* entityManager)
	: Entity(type, x, y, z)
{
	m_displayWidth = ENEMYWIDTH;
	m_displayHeight = ENEMYHEIGHT;
	m_positionXOffset = m_displayWidth / SCREENWIDTH;
	m_positionYOffset = m_displayHeight / SCREENHEIGHT;

	m_spriteSheetWidth = 4096.0f;
	m_spriteSheetHeight = 512.0f;
	m_spriteWidth = 512.0f;
	m_spriteHeight = 512.0f;
	m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	srand((unsigned int)time(0));
	int randomStart = rand() % m_destinations.size();
	
	srand((unsigned int)time(0));
	int randomDest  = rand() % m_destinations.size();

	m_positionX = m_destinations[randomStart].x;
	m_positionY = m_destinations[randomStart].y;

	m_destinationX = m_destinations[randomDest].x;
	m_destinationY = m_destinations[randomDest].y;

	// avoid having the enemy start without a remote destination to move to
	while ((m_positionX == m_destinationX) && (m_positionY == m_destinationY)) {
		randomDest = rand() % m_destinations.size();

		m_destinationX = m_destinations[randomDest].x;
		m_destinationY = m_destinations[randomDest].y;
	}

	m_vectorSourceToTarget[0] = m_destinationX - m_positionX;
	m_vectorSourceToTarget[1] = m_destinationY - m_positionY;

	updateVertexArray();

	entityManager->addEntityToRegistry(this);
}

Enemy::~Enemy()
{
}

void Enemy::animateShip()
{
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

void Enemy::moveEnemy()
{
	float approxEqualX = std::abs(m_positionX - m_destinationX);
	float approxEqualY = std::abs(m_positionY - m_destinationY);

	// close enough to destination so pick a new one
	if ((approxEqualX < 0.01f) && (approxEqualY < 0.01f)) {
		srand((unsigned int)time(0));
		int randomDest = rand() % m_destinations.size();

		m_destinationX = m_destinations[randomDest].x;
		m_destinationY = m_destinations[randomDest].y;

		m_vectorSourceToTarget[0] = m_destinationX - m_positionX;
		m_vectorSourceToTarget[1] = m_destinationY - m_positionY;
	}

	// heading out of bounds, so pick a new destination and change course
	if ((m_positionY + m_positionYOffset > 1.0f) || (m_positionY - m_positionYOffset < -0.9f)) {
		srand((unsigned int)time(0));
		int randomDest = rand() % m_destinations.size();

		m_destinationX = m_destinations[randomDest].x;
		m_destinationY = m_destinations[randomDest].y;

		m_vectorSourceToTarget[0] = m_destinationX - m_positionX;
		m_vectorSourceToTarget[1] = m_destinationY - m_positionY;
	}

	m_positionX += (m_vectorSourceToTarget[0] * m_enemyVelocity);
	m_positionY += (m_vectorSourceToTarget[1] * m_enemyVelocity);

	updateVertexArray();
}

void Enemy::increaseDifficulty(float difficulty)
{
	m_enemyVelocity += difficulty;
}

float Enemy::getDifficultyLevel()
{
	return m_enemyVelocity;
}





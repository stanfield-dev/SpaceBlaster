#pragma once

#include "defines.h"

static class Projectile
{
private:
	const float m_laserSpriteSheetWidth = 4096.0f;
	const float m_laserSpriteSheetHeight = 512.0f;
	const float m_laserSpriteWidth = 512.0f;
	const float m_laserSpriteHeight = 512.0f;

	float m_spriteXOrigin = 0.0f;
	float m_spriteXOffset = m_laserSpriteWidth / m_laserSpriteSheetWidth;
	float m_spriteYOrigin = 0.0f;
	float m_spriteYOffset = m_laserSpriteHeight / m_laserSpriteSheetHeight;

	float m_projectileVertices[20] = {
		0.0f, 0.0f,
		m_spriteXOrigin, m_spriteYOrigin,
		(float)LASER,

		0.0f, 0.0f,
		m_spriteXOrigin + m_spriteXOffset, m_spriteYOrigin,
		(float)LASER,

		0.0f, 0.0f,
		m_spriteXOrigin + m_spriteXOffset, m_spriteYOrigin + m_spriteYOffset,
		(float)LASER,

		0.0f, 0.0f,
		m_spriteXOrigin, m_spriteYOrigin + m_spriteYOffset,
		(float)LASER,
	};

public:
	static void launchProjectile(int, float*);
};
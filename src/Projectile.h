#pragma once

#include "Entity.h"

class Projectile : public Entity
{
private:
	const float m_spriteSheetWidth = 4096.0f;
	const float m_spriteSheetHeight = 512.0f;
	const float m_spriteWidth = 512.0f;
	const float m_spriteHeight = 512.0f;

	float m_displayWidth = 128.0f;
	float m_displayHeight = 11.0f;

public:
	Projectile(int, float, float, float);
	~Projectile();

	void updateXPosition(float);
};
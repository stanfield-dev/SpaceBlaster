#pragma once

#include "Entity.h"

class Enemy : public Entity
{
private:
	const float m_spriteSheetWidth = 4096.0f;
	const float m_spriteSheetHeight = 512.0f;
	const float m_spriteWidth = 512.0f;
	const float m_spriteHeight = 512.0f;

	float m_displayWidth = 128.0f;
	float m_displayHeight = 128.0f;

public:
	Enemy(int, float, float, float);
	~Enemy();

	void updateXPosition(float);
	void updateYPosition(float);
};


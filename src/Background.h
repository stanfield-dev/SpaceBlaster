#pragma once

#include "Entity.h"

class Background : public Entity
{
private:
	const float m_spriteSheetWidth = 2048.0f;
	const float m_spriteSheetHeight = 1536.0f;
	const float m_spriteWidth = 2048.0f;
	const float m_spriteHeight = 1536.0f;

	float m_displayWidth = SCREENWIDTH;
	float m_displayHeight = SCREENHEIGHT;

public:
	Background(int, float, float, float);
	~Background();

	void scrollBackground();
};

#pragma once

#include "defines.h"

class Entity
{
private:

protected:

	const float m_spriteSheetWidth = 0.0f;
	const float m_spriteSheetHeight = 0.0f;
	const float m_spriteWidth = 0.0f;
	const float m_spriteHeight = 0.0f;

	float m_displayWidth = 0.0f;
	float m_displayHeight = 0.0f;

	float m_positionX = 0.0f;
	float m_positionY = 0.0f;
	float m_positionZ = 0.0f;
	float m_positionXOffset = m_displayWidth / SCREENWIDTH;;
	float m_positionYOffset = m_displayHeight / SCREENHEIGHT;;

	float m_spriteX = 0.0f;
	float m_spriteXOffset = m_spriteWidth / m_spriteSheetWidth;
	float m_spriteY = 0.0f;
	float m_spriteYOffset = m_spriteHeight / m_spriteSheetHeight;

	int m_type;

	float m_vertexArray[24] = {
		m_positionX, m_positionY, m_positionZ,
		m_spriteX, m_spriteY,
		(float)m_type,

		m_positionX + m_positionXOffset, m_positionY, m_positionZ,
		m_spriteX + m_spriteXOffset, m_spriteY,
		(float)m_type,

		m_positionX + m_positionXOffset, m_positionY + m_positionYOffset, m_positionZ,
		m_spriteX + m_spriteXOffset, m_spriteY + m_spriteYOffset,
		(float)m_type,

		m_positionX, m_positionY + m_positionYOffset, m_positionZ,
		m_spriteX, m_spriteY + m_spriteYOffset,
		(float)m_type
	};

public:
	Entity(int, float, float, float);
	~Entity();

	float getPositionX() const;
	float getPositionY() const;
	float getGunPosition() const;

	void setPositionX(float);
	void setPositionY(float);

	float* updateVertexArray();

	void fireEngines();

};
#pragma once

#include <GL/glew.h>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "sb_defines.h"

class Entity
{
private:

protected:
	typedef struct
	{
		float x;
		float y;
	} m_gunPosition;

	float m_spriteSheetWidth = 0.0f;
	float m_spriteSheetHeight = 0.0f;
	float m_spriteWidth = 0.0f;
	float m_spriteHeight = 0.0f;

	float m_displayWidth = 0.0f;
	float m_displayHeight = 0.0f;

	float m_positionX = 0.0f;
	float m_positionY = 0.0f;
	float m_positionZ = 0.0f;
	float m_positionXOffset = 0.0f;
	float m_positionYOffset = 0.0f;

	float m_spriteX = 0.0f;
	float m_spriteXOffset = 0.0f;
	float m_spriteY = 0.0f;
	float m_spriteYOffset = 0.0f;

	int m_type;

	int m_countdownSource = 2;
	int m_projectileSource = 2;
	float m_projectileSourceCoordinates[2] = { 0.0f, 0.0f };
	float m_projectileTargetCoordinates[2] = { 0.0f, 0.0f };
	float m_vectorSourceToTarget[2] = { 0.0f, 0.0f };

	float m_radiansSourceToTarget = 0.0f;

	int m_countdownFrame = 0;
	int m_explosionFrame = 0;

	unsigned int m_VAO, m_vertexbufferID, m_indexbufferID;

	unsigned int m_iboIndices[6] = {
		0, 1, 2, 2, 3, 0
	};

	float m_vertexArray[24] = {
		m_positionX, 
		m_positionY, 
		m_positionZ,
		m_spriteX, 
		m_spriteY,
		(float)m_type,

		m_positionX + m_positionXOffset, 
		m_positionY, 
		m_positionZ,
		m_spriteX + m_spriteXOffset, 
		m_spriteY,
		(float)m_type,

		m_positionX + m_positionXOffset, 
		m_positionY + m_positionYOffset, 
		m_positionZ,
		m_spriteX + m_spriteXOffset, 
		m_spriteY + m_spriteYOffset,
		(float)m_type,

		m_positionX, 
		m_positionY + m_positionYOffset, 
		m_positionZ,
		m_spriteX, 
		m_spriteY + m_spriteYOffset,
		(float)m_type
	};

public:
	Entity(int, float, float, float);
	virtual ~Entity();

	int getType() const;

	// Animation functions
	virtual void animateScreen();
	virtual void animateShip();

	int getCountdownSource() const;
	virtual void animateCountdown();
	virtual int getCountdownFrame() const;

	virtual void animateExplosion();
	virtual int getExplosionFrame() const;


	// Combat and Collision functions
	m_boundingBox boundingBox() const;

	virtual void increaseDifficulty(float);
	virtual float getDifficultyLevel();

	// Health Bar functions
	virtual void updateHealthBarLives(int);

	// Positioning functions
	void setPositionX(float);
	void setPositionY(float);

	float getPositionX() const;
	float getPositionY() const;
	float getPositionZ() const;
	
	void updatePositionY(float);
	void updatePositionX(float);

	virtual void moveEnemy();

	// Projectile functions
	int getProjectileSource() const;
	virtual void moveProjectile();

	m_gunPosition getGunPosition() const;

	float* getProjectileTargetPosition();
	float* getProjectileSourcePosition();

	// Score functions
	virtual void updateScore();

	// Vertex functions
	virtual void generateBuffers();
	virtual float* updateVertexArray();
	virtual void updateVertexBuffer();

	void bindVAO();
	void unbindVAO();
	virtual void bindIBO();
};
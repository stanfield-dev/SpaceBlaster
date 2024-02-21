#pragma once

#include "EntityManager.h"
#include "Entity.h"

class Enemy : public Entity
{
private:
	typedef struct
	{
		float x;
		float y;

	} coordinates;

	// a bunch of destinations the enemy ship can move between
	std::vector<coordinates> m_destinations 
	{
		{0.7f, 0.7f},
		{0.7f, 0.6f},
		{0.7f, 0.4f},
		{0.7f, 0.2f},
		{0.7f, 0.1f},
		{0.7f, -0.2f},
		{0.7f, -0.4f},
		{0.7f, -0.6f},
		{0.7f, -0.65f},

		{0.6f, 0.62f},
		{0.6f, 0.5f},
		{0.6f, 0.3f},
		{0.6f, 0.1f},
		{0.6f, 0.0f},
		{0.6f, -0.1f},
		{0.6f, -0.3f},
		{0.6f, -0.5f},
		{0.6f, -0.63f},
	};

	float m_enemyVelocity = 0.01f;

	float m_destinationX = 0.0f;
	float m_destinationY = 0.0f;

public:

	Enemy(int, float, float, float, EntityManager*);
	~Enemy();

	void moveEnemy();
};


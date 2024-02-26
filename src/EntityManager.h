#pragma once	

#include <vector>

#include "sb_defines.h"
#include "Entity.h"

#include "miniaudio.h"

class EntityManager
{
private:
	ma_engine* m_soundEngine;

	std::vector<Entity*> m_entityRegistry;

	int m_playerLivesRemaining = 3;

	float m_enemyDifficulty = 0.0f;

public:
	EntityManager(ma_engine*);
	~EntityManager();

	Entity* spawnEntity(int, float, float, float, int, float*, float*);

	void addEntityToRegistry(Entity*);
	void removeEntityFromRegistry(Entity*);

	std::vector<Entity*> getEntityRegistry();

	Entity* getEntity(int);

	void resetPlayerLivesRemaining();
	void updatePlayerLivesRemaining(int);
	int getPlayerLivesRemaining() const;

	void updateVertexBuffers();

	Entity* respawnEnemy();
	Entity* respawnPlayer();

	void resetEnemyDifficulty();
};

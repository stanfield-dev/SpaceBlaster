#pragma once	

#include <vector>

#include "defines.h"
#include "Entity.h"

#include "miniaudio.h"

class EntityManager
{
private:
	ma_engine* m_soundEngine;
	std::vector<Entity*> m_entityRegistry;

	Entity* countdownEntity = nullptr;
	Entity* playerEntity = nullptr;

	int m_playerLivesRemaining = 3;

public:
	EntityManager(ma_engine*);
	~EntityManager();

	Entity* spawnEntity(int, float, float, float, int, float*, float*);

	void addEntityToRegistry(Entity*);
	void removeEntityFromRegistry(Entity*);

	std::vector<Entity*> getEntityRegistry();

	Entity* getCountdownEntity();
	Entity* getPlayerEntity();

	void setLivesRemaining(int);
	int getLivesRemaining() const;

	void updateScore();

	void updateVertexBuffers();

	void checkCollisions();

	Entity* respawnEnemy();

	Entity* respawnPlayer();
};

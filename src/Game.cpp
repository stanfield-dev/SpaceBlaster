#include "Game.h"

Game::Game(EntityManager* entityManager, ma_engine* soundEngine)
{
	m_gameStatus = NEW;

	m_soundEngine = soundEngine;

	entityManager->spawnEntity(BACKGROUND, -1.0f, -1.0f, 0.0f, BACKGROUND, nullptr, nullptr);
	entityManager->spawnEntity(HEALTHBAR, -(HEALTHBARWIDTH / SCREENWIDTH), -1.0f, 0.0f, HEALTHBAR, nullptr, nullptr);
	entityManager->spawnEntity(SCORE, -((SCORETOTALWIDTH / 2) / SCREENWIDTH), -0.955f, 0.0f, SCORE, nullptr, nullptr);
	entityManager->spawnEntity(PLAYER, -0.9f, 0.0f, 0.0f, PLAYER, nullptr, nullptr);
	entityManager->spawnEntity(ENEMY, 0.7f, 0.0f, 0.0f, ENEMY, nullptr, nullptr);
	entityManager->spawnEntity(STARTSCREEN, -1.0f, -1.0f, 0.0f, STARTSCREEN, nullptr, nullptr);
	entityManager->spawnEntity(HELPSCREEN, -1.0f, -1.0f, 0.0f, HELPSCREEN, nullptr, nullptr);
}

Game::~Game()
{
}

int Game::gameState() const
{
	return m_gameStatus;
}

void Game::setGameState(int state)
{
	m_gameStatus = state;
}

void Game::update(int state, EntityManager* entityManager)
{
	switch (state) {
		case NEW		:	{
							Entity* startscreen = entityManager->getEntity(STARTSCREEN);
							startscreen->animateScreen();
							}
							break;
		case RUNNING	:	animateBackground(entityManager);
							animateCountdown(entityManager);
							animateEnemy(entityManager);
							fireEnemyProjectile(entityManager);
							animateExplosions(entityManager);
							animatePlayer(entityManager);
							animateProjectiles(entityManager);
							checkCollisions(entityManager);
							break;
		case STARTSCREEN:	{
							Entity* startscreen = entityManager->getEntity(STARTSCREEN);
							startscreen->animateScreen();
							}
							break;
		case HELPSCREEN	:	{
							Entity* startscreen = entityManager->getEntity(STARTSCREEN);
							startscreen->animateScreen();
							}
							break;
		case GAMEOVER	:	{
							Entity* gameover = entityManager->getEntity(GAMEOVER);
							gameover->animateScreen();
							}
							break;
	}
}

void Game::animateBackground(EntityManager* entityManager)
{
	if (m_backgroundEntity == nullptr) {
		m_backgroundEntity = entityManager->getEntity(BACKGROUND);
	}

	if(m_backgroundEntity != nullptr) {
		m_backgroundEntity->animateScreen();
	}
}

void Game::animateCountdown(EntityManager* entityManager)
{
	if (m_countdownEntity == nullptr) {
		m_countdownEntity = entityManager->getEntity(COUNTDOWN);
	}

	if (m_countdownEntity != nullptr) {
		m_countdownEntity->animateCountdown();
	}
}

void Game::animateEnemy(EntityManager* entityManager)
{
	if (m_enemyEntity == nullptr) {
		m_enemyEntity = entityManager->getEntity(ENEMY);
	}

	if (m_enemyEntity != nullptr) {
		m_enemyEntity->animateShip();
		m_enemyEntity->moveEnemy();
	}
}

void Game::animateExplosions(EntityManager* entityManager)
{
	std::vector<Entity*> entityRegistry = entityManager->getEntityRegistry();

	for (auto entity : entityRegistry) {
		if (entity->getType() == EXPLOSION) {
			m_projectileEntity->animateExplosion();
		}
	}
}

void Game::animatePlayer(EntityManager* entityManager)
{
	if (m_playerEntity == nullptr) {
		m_playerEntity = entityManager->getEntity(PLAYER);
	}

	if (m_playerEntity != nullptr) {
		m_playerEntity->animateShip();
	}
}

void Game::animateProjectiles(EntityManager* entityManager)
{
	std::vector<Entity*> entityRegistry = entityManager->getEntityRegistry();

	for (auto entity : entityRegistry) {
		if (entity->getType() == PROJECTILE) {
			m_projectileEntity->moveProjectile();
		}
	}
}

void Game::fireEnemyProjectile(EntityManager* entityManager)
{
	if (m_enemyEntity == nullptr) {
		m_enemyEntity = entityManager->getEntity(ENEMY);
	}

	if (m_enemyEntity != nullptr) {
		Entity* target = entityManager->getEntity(PLAYER);
		if (target != nullptr) {
			float firingFrequency = m_enemyEntity->getDifficultyLevel();

			if (firingFrequency > 0.5f) {
				firingFrequency = 0.5f;
			}

			if (rand() % 1000 < (1000 * firingFrequency)) {
				entityManager->spawnEntity(
					PROJECTILE, 
					m_enemyEntity->getGunPositionX(), 
					m_enemyEntity->getGunPositionY(), 
					0.0f, 
					ENEMY,
					m_enemyEntity->getProjectileSourcePosition(), 
					target->getProjectileTargetPosition()
				);
			}
		}
	}
}

void Game::checkCollisions(EntityManager* entityManager)
{
	std::vector<Entity*> entityRegistry = entityManager->getEntityRegistry();

	for (auto projectile : entityRegistry) {
		if (projectile->getType() == PROJECTILE) {
			switch (projectile->getProjectileSource()) {

				// player shooting at enemy
				case PLAYER:	{
									Entity* enemy = entityManager->getEntity(ENEMY);
									if (enemy != nullptr) {
										if (directHit(projectile, enemy)) {

											entityManager->removeEntityFromRegistry(projectile);
											projectile->~Entity();
											delete projectile;

											entityManager->spawnEntity(
												EXPLOSION,
												enemy->getPositionX(),
												enemy->getPositionY(),
												enemy->getPositionZ(),
												EXPLOSION, nullptr, nullptr
											);
											ma_engine_play_sound(m_soundEngine, EXPLOSION_SOUND.c_str(), NULL);

											entityManager->removeEntityFromRegistry(enemy);
											enemy->~Entity();
											delete enemy;

											updateScore(entityManager);
											setGameState(INTERMISSION);
											// TODO respawn enemy and change state back to running after explosion delete
										}
									}
								}
								break;

				// enemy shooting at player
				case ENEMY	:	{
									Entity* player = entityManager->getEntity(PLAYER);
									if (player != nullptr) {
										if (directHit(projectile, player)) {

											entityManager->removeEntityFromRegistry(projectile);
											projectile->~Entity();
											delete projectile;

											entityManager->spawnEntity(
												EXPLOSION,
												player->getPositionX(),
												player->getPositionY(),
												player->getPositionZ(),
												EXPLOSION, nullptr, nullptr
											);
											ma_engine_play_sound(m_soundEngine, EXPLOSION_SOUND.c_str(), NULL);

											entityManager->removeEntityFromRegistry(player);
											player->~Entity();
											delete player;

											entityManager->updateLivesRemaining(-1);
											setGameState(INTERMISSION);
											launchCountdown(entityManager);
											// TODO call newRound() after countdown expires
										}
									}
								}
								break;
				// projectile moved offscreen and is destroyed
				default		:	if (projectile->getPositionX() < -1.0f || projectile->getPositionX() > 1.0f) {
									entityManager->removeEntityFromRegistry(projectile);
									projectile->~Entity();
									delete projectile;
								}
			}
		}
	}
}

bool Game::directHit(Entity* projectile, Entity* target)
{
	// enemy is hit
	if (target->getType() == ENEMY) {
		if ((projectile->getRightEdge() > target->getLeftEdge()) &&
			(projectile->getRightEdge() < target->getRightEdge()) &&
			(projectile->getTopEdge() > target->getBottomEdge()) &&
			(projectile->getTopEdge() < target->getTopEdge()))
		{
			return true;
		}
	}

	// player is hit
	if (target->getType() == PLAYER) {
		if ((projectile->getLeftEdge() < target->getRightEdge()) &&
			(projectile->getLeftEdge() > target->getLeftEdge()) &&
			(projectile->getTopEdge() > target->getBottomEdge()) &&
			(projectile->getTopEdge() < target->getTopEdge()))
		{
			return true;
		}
	}

	return false;
}

void Game::updateScore(EntityManager* entityManager)
{
	if (m_scoreEntity == nullptr) {
		m_scoreEntity = entityManager->getEntity(SCORE);
	}

	if(m_scoreEntity != nullptr) {
		m_scoreEntity->updateScore();
	}
}

void Game::launchCountdown(EntityManager* entityManager)
{
	entityManager->spawnEntity(
		COUNTDOWN,
		0.0f - ((COUNTDOWNWIDTH / SCREENWIDTH) / 2),
		0.0f,
		0.0f,
		COUNTDOWN,
		nullptr,
		nullptr
	);
}

void Game::newRound(EntityManager* entityManager)
{
	/*
		a new round means the player has to respawn
		the enemy may or may not have been blown up by a stray laser after the fact

		enemy death alone doesnt change game state, just respawn the enemy and carry on

		REWRITE ALL THIS
	*/
	//Entity* enemy = entityManager->getEntity(ENEMY);

	//entityManager->spawnEntity(
	//	COUNTDOWN,
	//	0.0f - ((COUNTDOWNWIDTH / SCREENWIDTH) / 2),
	//	0.0f,
	//	0.0f,
	//	COUNTDOWN,
	//	nullptr,
	//	nullptr
	//);

	//// TODO how to wait for countdown to expire before spanwing new player/enemy
	//Entity* countdown = entityManager->getEntity(COUNTDOWN);

	//if (player == nullptr) {
	//	entityManager->respawnPlayer();
	//}

	//if (enemy == nullptr) {
	//	entityManager->respawnEnemy();
	//}
}



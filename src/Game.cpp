#include "Game.h"
#include <iostream>

Game::Game(EntityManager* entityManager, SoundEngine *soundEngine)
{
	m_gameStatus = STARTSCREENst;
	m_lastGameStatus = NEWGAMEst;

	entityManager->spawnEntity(BACKGROUND, -1.0f, -1.0f, 0.0f, BACKGROUND, nullptr, nullptr);
	entityManager->spawnEntity(ENEMY, 0.7f, 0.0f, 0.0f, ENEMY, nullptr, nullptr);
	entityManager->spawnEntity(GAMEOVER, -((GAMEOVERWIDTH / 2) / SCREENWIDTH), -((GAMEOVERHEIGHT / 2) / SCREENHEIGHT), 0.0f, GAMEOVER, nullptr, nullptr);
	entityManager->spawnEntity(HEALTHBAR, -(HEALTHBARWIDTH / SCREENWIDTH), -1.0f, 0.0f, HEALTHBAR, nullptr, nullptr);
	entityManager->spawnEntity(HELPSCREEN, -1.0f, -1.0f, 0.0f, HELPSCREEN, nullptr, nullptr);
	entityManager->spawnEntity(PLAYER, -0.9f, 0.0f, 0.0f, PLAYER, nullptr, nullptr);
	entityManager->spawnEntity(SCORE, -((SCORETOTALWIDTH / 2) / SCREENWIDTH), -0.955f, 0.0f, SCORE, nullptr, nullptr);
	entityManager->spawnEntity(STARTSCREEN, -1.0f, -1.0f, 0.0f, STARTSCREEN, nullptr, nullptr);

	m_soundEngine = soundEngine;
}

Game::~Game()
{
}

int Game::gameState() const
{
	return m_gameStatus;
}

int Game::lastGameState() const
{
	return m_lastGameStatus;
}

void Game::setGameState(int state, int lastState)
{
	m_gameStatus = state;
	m_lastGameStatus = lastState;
}

void Game::update(int state, EntityManager* entityManager)
{
	switch (state) {
		case COMBATst:
			{
				//std::cout << "COMBAT STATE" << std::endl;
				animateBackground(entityManager);
				animateEnemy(entityManager);
				fireEnemyProjectile(entityManager);
				animateExplosions(entityManager);
				animatePlayer(entityManager);
				animateProjectiles(entityManager);
				checkCollisions(entityManager);
			}
			break;
		case COUNTDOWNst:
			{
				//std::cout << "COUNTDOWN STATE" << std::endl;
				animateBackground(entityManager);
				animateCountdown(entityManager);
				animateExplosions(entityManager);
				animateProjectiles(entityManager);
				animateEnemy(entityManager);
				animatePlayer(entityManager);
			}
			break;
		case GAMEOVERst:	
			{
				//std::cout << "GAMEOVER STATE" << std::endl;
				animateBackground(entityManager);
				animateExplosions(entityManager);
				animateProjectiles(entityManager);
				animateEnemy(entityManager);
				animateGameover(entityManager);
			}
			break;
		case HELPSCREENst:	
			{
				//std::cout << "HELPSCREEN STATE" << std::endl;
				Entity* helpscreen = entityManager->getEntity(HELPSCREEN);
				helpscreen->animateScreen();
			}
			break;
		case NEWGAMEst:
			{
				//std::cout << "NEWGAME STATE" << std::endl;
				newGame(entityManager);
			}
			break;
		case RESPAWNst:
			{
				//std::cout << "RESPAWN STATE" << std::endl;
				respawnContestants(entityManager);
			}
			break;
		case STARTSCREENst:	
			{
				//std::cout << "STARTSCREEN STATE" << std::endl;
				Entity* startscreen = entityManager->getEntity(STARTSCREEN);
				startscreen->animateScreen();
			}
			break;
	}
}

void Game::newGame(EntityManager* entityManager)
{
	// clean up any dynamic objects just in case
	std::vector<Entity*> entityRegistry = entityManager->getEntityRegistry();

	for (auto entity : entityRegistry) {
		if ((entity->getType() == ENEMY) || (entity->getType() == EXPLOSION) ||
			(entity->getType() == PROJECTILE) || (entity->getType() == PLAYER) ||
			(entity->getType() == HEALTHBAR) || (entity->getType() == SCORE)) {
			entityManager->removeEntityFromRegistry(entity);
			entity->~Entity();
			delete entity;
		}
	}

	// reset the score sprite
	entityManager->spawnEntity(SCORE, -((SCORETOTALWIDTH / 2) / SCREENWIDTH), -0.955f, 0.0f, SCORE, nullptr, nullptr);
	m_scoreEntity = entityManager->getEntity(SCORE);

	// reset the healthbar sprite
	entityManager->spawnEntity(HEALTHBAR, -(HEALTHBARWIDTH / SCREENWIDTH), -1.0f, 0.0f, HEALTHBAR, nullptr, nullptr);
	m_healthbarEntity = entityManager->getEntity(HEALTHBAR);

	// spawn new contestants
	entityManager->resetPlayerLivesRemaining();
	entityManager->spawnEntity(PLAYER, -0.9f, 0.0f, 0.0f, PLAYER, nullptr, nullptr);
	m_playerEntity = entityManager->getEntity(PLAYER);

	entityManager->resetEnemyDifficulty();
	entityManager->spawnEntity(ENEMY, 0.7f, 0.0f, 0.0f, ENEMY, nullptr, nullptr);
	m_playerEntity = entityManager->getEntity(PLAYER);

	// start the game
	setGameState(STARTSCREENst, NEWGAMEst);
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
		entityManager->spawnEntity(
			COUNTDOWN,
			-((COUNTDOWNWIDTH / 2) / SCREENWIDTH),
			-((COUNTDOWNHEIGHT / 2) / SCREENHEIGHT),
			0.0f,
			COUNTDOWN,
			nullptr,
			nullptr
		);
	}
	m_countdownEntity = entityManager->getEntity(COUNTDOWN);

	if (m_countdownEntity != nullptr) {
		if (m_countdownEntity->getCountdownFrame() == 0) {
			entityManager->removeEntityFromRegistry(m_countdownEntity);
			m_countdownEntity->~Entity();
			delete m_countdownEntity;
			setGameState(RESPAWNst, COUNTDOWNst);
		}
		else {
			m_countdownEntity->animateCountdown();
		}
	}
}

void Game::animateEnemy(EntityManager* entityManager)
{
	m_enemyEntity = entityManager->getEntity(ENEMY);

	if (m_enemyEntity != nullptr) {
		m_enemyEntity->animateShip();
		m_enemyEntity->moveEnemy();
	}
}

void Game::animateGameover(EntityManager* entityManager)
{
	m_gameoverEntity = entityManager->getEntity(GAMEOVER);

	if (m_gameoverEntity != nullptr) {
		m_gameoverEntity->animateScreen();
	}
}

void Game::animatePlayer(EntityManager* entityManager)
{
	m_playerEntity = entityManager->getEntity(PLAYER);

	if (m_playerEntity != nullptr) {
		m_playerEntity->animateShip();
	}
}

void Game::animateExplosions(EntityManager* entityManager)
{
	std::vector<Entity*> entityRegistry = entityManager->getEntityRegistry();

	for (auto entity : entityRegistry) {
		if (entity->getType() == EXPLOSION) {
			if (entity->getExplosionFrame() > 25) {
				entityManager->removeEntityFromRegistry(entity);
				entity->~Entity();
				delete entity;

				if (entityManager->getPlayerLivesRemaining() == 0) {
					setGameState(GAMEOVERst, COMBATst);
				}
				else {
					setGameState(COUNTDOWNst, COMBATst);
				}
			}
			else {
				entity->animateExplosion();
			}
		}
	}
}

void Game::animateProjectiles(EntityManager* entityManager)
{
	std::vector<Entity*> entityRegistry = entityManager->getEntityRegistry();

	for (auto entity : entityRegistry) {
		if (entity->getType() == PROJECTILE) {
			entity->moveProjectile();
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
					m_enemyEntity->getGunPosition().x, 
					m_enemyEntity->getGunPosition().y, 
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
	int lastState = lastGameState();

	for (auto projectile : entityRegistry) {
		if (projectile->getType() == PROJECTILE) {
			switch (projectile->getProjectileSource()) {

				// player shooting at enemy
				case PLAYER:	
					{
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
								m_soundEngine->playSound(EXPLOSION_SOUND);

								entityManager->removeEntityFromRegistry(enemy);
								enemy->~Entity();
								delete enemy;

								updateScore(entityManager);
							}
						}
					}
					break;

				// enemy shooting at player
				case ENEMY:	
					{
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
								m_soundEngine->playSound(EXPLOSION_SOUND);

								entityManager->removeEntityFromRegistry(player);
								player->~Entity();
								delete player;

								entityManager->updatePlayerLivesRemaining(-1);
							}
						}
					}
					break;

				// projectile moved offscreen and is destroyed
				default:
					{
						if (projectile->getPositionX() < -1.0f || projectile->getPositionX() > 1.0f) {
							entityManager->removeEntityFromRegistry(projectile);
							projectile->~Entity();
							delete projectile;
						}
					}
			}
		}
	}
}

bool Game::directHit(Entity* projectile, Entity* target)
{
	m_boundingBox projectileBox = projectile->boundingBox();
	m_boundingBox targetBox = target->boundingBox();

	// enemy is hit
	if (target->getType() == ENEMY) {
		if ((projectileBox.right > targetBox.left) &&
			(projectileBox.right < targetBox.right) &&
			(projectileBox.top   > targetBox.bottom) &&
			(projectileBox.top   < targetBox.top))
		{
			return true;
		}
	}

	// player is hit
	if (target->getType() == PLAYER) {
		if ((projectileBox.left < targetBox.right) &&
			(projectileBox.left > targetBox.left) &&
			(projectileBox.top	> targetBox.bottom) &&
			(projectileBox.top	< targetBox.top))
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

void Game::respawnContestants(EntityManager* entityManager)
{
	if (entityManager->getPlayerLivesRemaining() > 0) {
		if (m_enemyEntity == nullptr) {
			m_enemyEntity = entityManager->respawnEnemy();
		}

		if (m_playerEntity == nullptr) {
			m_playerEntity = entityManager->respawnPlayer();
		}

		setGameState(COMBATst, RESPAWNst);
	}
}



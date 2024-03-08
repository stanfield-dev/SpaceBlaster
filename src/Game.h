#pragma once

#include "sb_defines.h"
#include "EntityManager.h"
#include "SoundEngine.h"

class Game
{
private:
	int m_gameStatus = STARTSCREENst;
	int m_lastGameStatus = NEWGAMEst;

	Entity* m_backgroundEntity	= nullptr;
	Entity* m_countdownEntity	= nullptr;
	Entity* m_enemyEntity		= nullptr;
	Entity* m_explosionEntity	= nullptr;
	Entity* m_gameoverEntity	= nullptr;
	Entity* m_healthbarEntity	= nullptr;
	Entity* m_helpscreenEntity	= nullptr;
	Entity* m_playerEntity		= nullptr;
	Entity* m_projectileEntity	= nullptr;
	Entity* m_scoreEntity		= nullptr;
	Entity* m_startscreenEntity = nullptr;

	SoundEngine* m_soundEngine = nullptr;

	bool directHit(Entity*, Entity*);

public:
	Game(EntityManager*, SoundEngine*);
	~Game();

	int gameState() const;
	int lastGameState() const;
	void setGameState(int, int);

	void newGame(EntityManager*);

	void update(int, EntityManager*);

	void animateBackground(EntityManager*);
	void animateCountdown(EntityManager*);
	void animateEnemy(EntityManager*);
	void animateGameover(EntityManager*);
	void animateExplosions(EntityManager*);
	void animatePlayer(EntityManager*);
	void animateProjectiles(EntityManager*);

	void fireEnemyProjectile(EntityManager*);

	void checkCollisions(EntityManager*);

	void updateScore(EntityManager*);

	void respawnContestants(EntityManager*);

};
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

void Renderer::init(unsigned int shaderProgram)
{
	glClearColor(0.0f, 0.2f, 0.1f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void Renderer::drawEntities(unsigned int shaderProgram, EntityManager* entityManager)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto entity : entityManager->getEntityRegistry()) {
		if ((entity->getType() != GAME_MENU) && (entity->getType() != HELP_MENU) && (entity->getType() != SCORE)) {
			entity->bindVAO();
			entity->bindIBO();

			// background animation
			if (entity->getType() == BACKGROUND) {
				entity->scrollBackground();
			}

			// engine animation
			if (entity->getType() == PLAYER || entity->getType() == ENEMY) {
				entity->fireEngines();
			}

			// move enemy ship
			if (entity->getType() == ENEMY) {
				entity->moveEnemy();
			}

			// enemy fire at player
			if (entity->getType() == ENEMY && entityManager->getPlayerEntity() != nullptr) {
				Entity* player = entityManager->getPlayerEntity();

				float firingFrequency = entity->getDifficultyLevel();

				if (firingFrequency > 0.5f) {
					firingFrequency = 0.5f;
				}

				if (rand() % 1000 < (1000 * firingFrequency)) {
					entityManager->spawnEntity(PROJECTILE, entity->getGunPositionX(), entity->getGunPositionY(), 0.0f, ENEMY,
						entity->getProjectileSourcePosition(), player->getProjectileTargetPosition());
				}
			}

			// move projectile across screen
			if (entity->getType() == PROJECTILE) {
				if (entity->getProjectileSource() == PLAYER) { // horizontal only
					entity->updatePositionX(0.03f);
				}
				else {
					entity->moveProjectile();
				}
			}

			// explosion animation
			if (entity->getType() == EXPLOSION) {
				if (entity->getExplosionFrame() > 24) {
					entityManager->removeEntityFromRegistry(entity);
					entity->~Entity();
				}
				else {
					entity->animateExplosion();
				}
			}

			// countdown animation
			if (entity->getType() == COUNTDOWN) {
				if (entity->getCountdownFrame() > 400) {
					if (entity->getCountdownSource() == ENEMY) {
						entityManager->respawnEnemy();
					}
					entityManager->removeEntityFromRegistry(entity);
					entity->~Entity();
				}
				else {
					entity->animateCountdown();
				}
			}

			entity->updateVertexBuffer();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			entity->unbindVAO();
		}
	}
}

void Renderer::drawGameMenu(unsigned int shaderProgram, EntityManager* entityManager)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto entity : entityManager->getEntityRegistry()) {
		if (entity->getType() == GAME_MENU) {
			entity->bindVAO();
			entity->bindIBO();

			// game menu animation
			entity->animateMenu();

			entity->updateVertexBuffer();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			entity->unbindVAO();
		}
	}
}

void Renderer::drawHelpMenu(unsigned int shaderProgram, EntityManager* entityManager)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto entity : entityManager->getEntityRegistry()) {
		if (entity->getType() == HELP_MENU) {
			entity->bindVAO();
			entity->bindIBO();

			// help menu animation
			entity->animateMenu();

			entity->updateVertexBuffer();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			entity->unbindVAO();
		}
	}
}

void Renderer::drawScore(unsigned int shaderProgram, EntityManager* entityManager)
{
	/*glClear(GL_COLOR_BUFFER_BIT);*/

	for (auto entity : entityManager->getEntityRegistry()) {
		if (entity->getType() == SCORE) {
			entity->bindVAO();
			entity->bindIBO();
			entity->updateVertexBuffer();
			glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
			entity->unbindVAO();
		}
	}
}
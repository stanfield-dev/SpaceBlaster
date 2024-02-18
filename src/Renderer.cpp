#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

void Renderer::init(unsigned int shaderProgram)
{
	glClearColor(0.0f, 0.2f, 0.1f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	m_projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	
	m_projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
	m_viewMatrixLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
	m_modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");

	glUniformMatrix4fv(m_projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
	glUniformMatrix4fv(m_viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
}

void Renderer::drawEntities(unsigned int shaderProgram, EntityManager* entityManager)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto entity : entityManager->getEntityRegistry()) {
		entity->bindVAO();
		entity->bindIBO();

		glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(entity->getModelMatrix()));

		// background animation
		if (entity->getType() == BACKGROUND) {
			entity->scrollBackground();
		}

		// engine animation
		if (entity->getType() == PLAYER || entity->getType() == ENEMY) {
			entity->fireEngines();
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

		entity->updateVertexBuffer();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		entity->unbindVAO();
	}
}

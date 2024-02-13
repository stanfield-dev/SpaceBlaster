#include "Renderer.h"
#include "Shader.h"

#include <iostream>

void Renderer::init()
{
	glClearColor(0.0f, 0.2f, 0.1f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void Renderer::drawEntities(unsigned int shaderProgram, std::vector<Entity*> entityRegistry)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto entity : entityRegistry) {
		entity->bindVAO();
		entity->bindIBO();
		if (entity->getType() == PLAYER || entity->getType() == ENEMY) {
			entity->fireEngines();
		}
		if (entity->getType() == PROJECTILE) {
			if (entity->getProjectileSource() == PLAYER) {
				entity->updatePositionX(0.03f);
			}
			else {
				entity->updatePositionX(-0.03f);
			}
		}
		entity->updateVertexBuffer();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		entity->unbindVAO();
	}
}

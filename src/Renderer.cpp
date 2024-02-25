#include "Renderer.h"

#include <iostream>

void Renderer::init(unsigned int shaderProgram)
{
	glClearColor(0.0f, 0.2f, 0.1f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void Renderer::drawEntities(int gameState, unsigned int shaderProgram, EntityManager* entityManager)
{
	auto entityRegistry = entityManager->getEntityRegistry();
	switch (gameState) {

		case NEW:
			{
				Entity* gameMenu = entityManager->getEntity(STARTSCREEN);
				drawInfoScreen(gameMenu, shaderProgram);
			}
			break;
		case RUNNING:
			{
				drawGameScreen(entityManager, shaderProgram);
			}
			break;
		case STARTSCREEN:
			{
				Entity* gameMenu = entityManager->getEntity(STARTSCREEN);
				drawInfoScreen(gameMenu, shaderProgram);
			}
			break;
		case HELPSCREEN:
			{
				Entity* helpMenu = entityManager->getEntity(STARTSCREEN);
				drawInfoScreen(helpMenu, shaderProgram);
			}
			break;
		case INTERMISSION:
			break;
		case NEWROUND:
			break;
		case GAMEOVER:
			break;
	}
}

void Renderer::drawInfoScreen(Entity* entity, unsigned int shaderProgram)
{
	entity->bindVAO();
	entity->bindIBO();
	entity->updateVertexBuffer();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	entity->unbindVAO();
}

void Renderer::drawGameScreen(EntityManager* entityManager, unsigned int shaderProgram)
{
	std::vector<Entity*> entityRegistry = entityManager->getEntityRegistry();

	for (auto entity : entityRegistry) {  
		if ((entity->getType() != STARTSCREEN) && (entity->getType() != HELPSCREEN) && 
			(entity->getType() != SCORE) && (entity->getType() != COUNTDOWN) ) {
				entity->bindVAO();
				entity->bindIBO();
				entity->updateVertexBuffer();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				entity->unbindVAO();
		}
	}

	Entity* score = entityManager->getEntity(SCORE);
	score->bindVAO();
	score->bindIBO();
	score->updateVertexBuffer();
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	score->unbindVAO();

}


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

		case COMBATst:
			{
				drawGameScreen(entityManager, shaderProgram);
			}
			break;
		case COUNTDOWNst:
			{
				drawGameCountdownScreen(entityManager, shaderProgram);
			}
			break;
		case GAMEOVERst:
			{
				drawGameOverScreen(entityManager, shaderProgram);
			}
			break;
		case HELPSCREENst:
			{
				Entity* helpScreen = entityManager->getEntity(HELPSCREEN);
				drawInfoScreen(helpScreen, shaderProgram);
			}
			break;
		case NEWGAMEst:
			{
				Entity* startScreen = entityManager->getEntity(STARTSCREEN);
				drawInfoScreen(startScreen, shaderProgram);
			}
			break;
		case RESPAWNst:
			{
				drawGameScreen(entityManager, shaderProgram);
			}
			break;
		case STARTSCREENst:
			{
				Entity* gameMenu = entityManager->getEntity(STARTSCREEN);
				drawInfoScreen(gameMenu, shaderProgram);
			}
			break;
	}
}

// ====================================================================================
//
// Draw collections of entities based on the state of the game
//
// Score is handled separately due to the different index buffer size and my lazy
// avoidance of passing it around as a parameter
//
// ====================================================================================

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
			(entity->getType() != SCORE) && (entity->getType() != COUNTDOWN) &&
			(entity->getType() != GAMEOVER)) {
				entity->bindVAO();
				entity->bindIBO();
				entity->updateVertexBuffer();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				entity->unbindVAO();
		}
	}

	drawScore(entityManager, shaderProgram);
}

void Renderer::drawGameCountdownScreen(EntityManager* entityManager, unsigned int shaderProgram)
{
	std::vector<Entity*> entityRegistry = entityManager->getEntityRegistry();

	for (auto entity : entityRegistry) {
		if ((entity->getType() != STARTSCREEN) && (entity->getType() != HELPSCREEN) &&
			(entity->getType() != SCORE) && (entity->getType() != GAMEOVER)) {
			entity->bindVAO();
			entity->bindIBO();
			entity->updateVertexBuffer();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			entity->unbindVAO();
		}
	}

	drawScore(entityManager, shaderProgram);
}

void Renderer::drawGameOverScreen(EntityManager* entityManager, unsigned int shaderProgram)
{
	std::vector<Entity*> entityRegistry = entityManager->getEntityRegistry();

	for (auto entity : entityRegistry) {
		if ((entity->getType() != STARTSCREEN) && (entity->getType() != HELPSCREEN) &&
			(entity->getType() != SCORE) && (entity->getType() != COUNTDOWN) &&
			(entity->getType() != PLAYER)) {
				entity->bindVAO();
				entity->bindIBO();
				entity->updateVertexBuffer();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				entity->unbindVAO();
		}
	}

	drawScore(entityManager, shaderProgram);
}

void Renderer::drawScore(EntityManager* entityManager, unsigned int shaderProgram)
{
	Entity* score = entityManager->getEntity(SCORE);
	score->bindVAO();
	score->bindIBO();
	score->updateVertexBuffer();
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	score->unbindVAO();
}

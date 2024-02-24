#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "miniaudio.h"

#include "defines.h"
#include "Background.h"
#include "EntityManager.h"
#include "Renderer.h"
#include "Shader.h"
#include "Terrain.h"
#include "Textures.h"

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <time.h>

bool newGame = true;
float musicVolume = 0.5f;

std::map<int, bool> keyIsPressed 
{
	{GLFW_KEY_DOWN, false},
	{GLFW_KEY_ENTER, false},
	{GLFW_KEY_ESCAPE, false},
	{GLFW_KEY_EQUAL, false},
	{GLFW_KEY_F1, false},
	{GLFW_KEY_MINUS, false},
	{GLFW_KEY_S, false},
	{GLFW_KEY_SPACE, false},
	{GLFW_KEY_UP, false},
	{GLFW_KEY_W, false}
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_DOWN		:	keyIsPressed[GLFW_KEY_DOWN] = true;
										break;
			case GLFW_KEY_ENTER		:	keyIsPressed[GLFW_KEY_ENTER] = true;
										break;
			case GLFW_KEY_ESCAPE	:	keyIsPressed[GLFW_KEY_ESCAPE] = true;
										break;
			case GLFW_KEY_EQUAL		:	keyIsPressed[GLFW_KEY_EQUAL] = true;
										break;
			case GLFW_KEY_F1:			keyIsPressed[GLFW_KEY_F1] = true;
										break;
			case GLFW_KEY_MINUS		:	keyIsPressed[GLFW_KEY_MINUS] = true;
										break;
			case GLFW_KEY_Q			:	glfwSetWindowShouldClose(window, 1);
										break;
			case GLFW_KEY_S			:	keyIsPressed[GLFW_KEY_S] = true;
										break;
			case GLFW_KEY_SPACE		:	keyIsPressed[GLFW_KEY_SPACE] = true;
										break;
			case GLFW_KEY_UP		:	keyIsPressed[GLFW_KEY_UP] = true;			
										break;
			case GLFW_KEY_W			:	keyIsPressed[GLFW_KEY_W] = true;
										break;
		}
	}

	if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_DOWN		:	keyIsPressed[GLFW_KEY_DOWN] = false;
										break;
			case GLFW_KEY_ENTER		:	keyIsPressed[GLFW_KEY_ENTER] = false;
										break;
			case GLFW_KEY_ESCAPE	:	keyIsPressed[GLFW_KEY_ESCAPE] = false;
										break;
			case GLFW_KEY_EQUAL		:	keyIsPressed[GLFW_KEY_EQUAL] = false;
										break;
			case GLFW_KEY_F1		:	keyIsPressed[GLFW_KEY_F1] = false;
										break;
			case GLFW_KEY_MINUS		:	keyIsPressed[GLFW_KEY_MINUS] = false;
										break;
			case GLFW_KEY_S			:	keyIsPressed[GLFW_KEY_S] = false;
										break;
			case GLFW_KEY_SPACE		:	keyIsPressed[GLFW_KEY_SPACE] = false;
										break;
			case GLFW_KEY_UP		:	keyIsPressed[GLFW_KEY_UP] = false;
										break;
			case GLFW_KEY_W			:	keyIsPressed[GLFW_KEY_W] = false;
										break;
		}
	}

}

void loadHelpMenu(EntityManager* entityManager, GLFWwindow* window, unsigned int shaderProgram)
{
	Entity* helpMenu = entityManager->spawnEntity(HELPSCREEN, -1.0f, -1.0f, 0.0f, HELPSCREEN, nullptr, nullptr);

	while (keyIsPressed[GLFW_KEY_ENTER] == false) {
		entityManager->updateVertexBuffers();
		Renderer::drawHelpMenu(shaderProgram, entityManager);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	entityManager->removeEntityFromRegistry(helpMenu);
	helpMenu->~Entity();
	delete helpMenu;

	newGame = false;
}

void loadGameMenu(EntityManager* entityManager, GLFWwindow* window, unsigned int shaderProgram)
{
	Entity* gameMenu = entityManager->spawnEntity(STARTSCREEN, -1.0f, -1.0f, 0.0f, STARTSCREEN, nullptr, nullptr);

	while (keyIsPressed[GLFW_KEY_ENTER] == false) {
		if (keyIsPressed[GLFW_KEY_F1] == true) {
			loadHelpMenu(entityManager, window, shaderProgram);
		}
		entityManager->updateVertexBuffers();
		Renderer::drawGameMenu(shaderProgram, entityManager);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	entityManager->removeEntityFromRegistry(gameMenu);
	gameMenu->~Entity();
	delete gameMenu;

	newGame = false;
}

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow((int)SCREENWIDTH, (int)SCREENHEIGHT, "Space Battle!", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialization failure!" << std::endl;
	}

	// miniaudio setup
	ma_result result;
	ma_engine soundEngine;
	ma_engine_config soundEngineConfig;

	soundEngineConfig = ma_engine_config_init();

	result = ma_engine_init(NULL, &soundEngine);
	if (result != MA_SUCCESS) {
		return result;
	}

	ma_sound backgroundMusic;
	result = ma_sound_init_from_file(&soundEngine, GAME_MUSIC.c_str(), 0, NULL, NULL, &backgroundMusic);
	if (result != MA_SUCCESS) {
		return result;
	}

	ma_sound_set_looping(&backgroundMusic, true);
	ma_sound_set_volume(&backgroundMusic, musicVolume);
	ma_sound_start(&backgroundMusic);

	EntityManager *entityManager = new EntityManager(&soundEngine);

	unsigned int shaderProgram = Shader::createShader(Shader::getVertexShader(), Shader::getFragmentShader());
	Shader::useShader(shaderProgram); 
	
	Renderer::init(shaderProgram);

	Textures::init(shaderProgram);

	Entity* background = entityManager->spawnEntity(BACKGROUND, -1.0f, -1.0f, 0.0f, BACKGROUND, nullptr, nullptr);
	Entity* healthbar = entityManager->spawnEntity(HEALTHBAR, -(HEALTHBARWIDTH/SCREENWIDTH), -1.0f, 0.0f, HEALTHBAR, nullptr, nullptr);
	Entity* score = entityManager->spawnEntity(SCORE, -((SCORETOTALWIDTH / 2) / SCREENWIDTH), -0.955f, 0.0f, SCORE, nullptr, nullptr);
	Entity* player = entityManager->spawnEntity(PLAYER, -0.9f, 0.0f, 0.0f, PLAYER, nullptr, nullptr);
	Entity* enemy = entityManager->spawnEntity(ENEMY, 0.7f, 0.0f, 0.0f, ENEMY, nullptr, nullptr);

	srand((unsigned int)time(0));

	while (!glfwWindowShouldClose(window)) {

		if (keyIsPressed[GLFW_KEY_MINUS] == true) {
			if (musicVolume > 0.0) {
				musicVolume -= 0.05f;
				ma_sound_set_volume(&backgroundMusic, musicVolume);
			}
		}

		if (keyIsPressed[GLFW_KEY_EQUAL] == true) {
			if (musicVolume < 1.0) {
				musicVolume += 0.05f;
				ma_sound_set_volume(&backgroundMusic, musicVolume);
			}
		}

		if ( (entityManager->getPlayerEntity() == 0) && (entityManager->getCountdownEntity() == 0)) {
			player = entityManager->respawnPlayer();
		}

		if (newGame) {
			loadGameMenu(entityManager, window, shaderProgram);
		}

		else {
			if (entityManager->getPlayerEntity() != 0) {

				if (keyIsPressed[GLFW_KEY_W] == true || keyIsPressed[GLFW_KEY_UP] == true) {
					entityManager->getPlayerEntity()->updatePositionY((1.0f / SCREENHEIGHT) * 8.0f);
				}

				if (keyIsPressed[GLFW_KEY_S] == true || keyIsPressed[GLFW_KEY_DOWN] == true) {
					entityManager->getPlayerEntity()->updatePositionY(-(1.0f / SCREENHEIGHT) * 8.0f);
				}

				if (keyIsPressed[GLFW_KEY_SPACE] == true) {
					entityManager->spawnEntity(PROJECTILE, player->getGunPositionX(), player->getGunPositionY(), 0.0f,
						PLAYER, nullptr, nullptr);
					keyIsPressed[GLFW_KEY_SPACE] = false; // prevent bullet spam
				}
			}

			if (keyIsPressed[GLFW_KEY_ESCAPE] == true) {
				loadGameMenu(entityManager, window, shaderProgram);
			}

			if (keyIsPressed[GLFW_KEY_F1] == true) {
				loadHelpMenu(entityManager, window, shaderProgram);
			}

			entityManager->updateVertexBuffers();
			entityManager->checkCollisions();
		
			Renderer::drawEntities(shaderProgram, entityManager);
			Renderer::drawScore(shaderProgram, entityManager);

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}

	Shader::deleteShader(shaderProgram);

	glfwTerminate();
	return 0;
}

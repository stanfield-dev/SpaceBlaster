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

std::map<int, bool> keyIsPressed 
{
	{GLFW_KEY_W, false},
	{GLFW_KEY_UP, false},

	{GLFW_KEY_DOWN, false},
	{GLFW_KEY_S, false},

	{GLFW_KEY_SPACE, false}
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE	:	glfwSetWindowShouldClose(window, 1);
										break;
			case GLFW_KEY_Q			:	glfwSetWindowShouldClose(window, 1);
										break;

			case GLFW_KEY_W			:	keyIsPressed[GLFW_KEY_W] = true;
										break;
			case GLFW_KEY_UP		:	keyIsPressed[GLFW_KEY_UP] = true;			
										break;
			case GLFW_KEY_DOWN		:	keyIsPressed[GLFW_KEY_DOWN] = true;
										break;
			case GLFW_KEY_S			:	keyIsPressed[GLFW_KEY_S] = true;
										break;
			case GLFW_KEY_SPACE		:	keyIsPressed[GLFW_KEY_SPACE] = true;
										break;
		}
	}

	if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_W			:	keyIsPressed[GLFW_KEY_W] = false;
										break;
			case GLFW_KEY_UP		:	keyIsPressed[GLFW_KEY_UP] = false;
										break;
			case GLFW_KEY_DOWN		:	keyIsPressed[GLFW_KEY_DOWN] = false;
										break;
			case GLFW_KEY_S			:	keyIsPressed[GLFW_KEY_S] = false;
										break;
			case GLFW_KEY_SPACE		:	keyIsPressed[GLFW_KEY_SPACE] = false;
										break;
		}
	}

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
	window = glfwCreateWindow((int)SCREENWIDTH, (int)SCREENHEIGHT, "Test Game", NULL, NULL);
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

	// TODO add volume controls
	ma_sound_set_looping(&backgroundMusic, true);
	ma_sound_start(&backgroundMusic);

	EntityManager *entityManager = new EntityManager(&soundEngine);

	unsigned int shaderProgram = Shader::createShader(Shader::getVertexShader(), Shader::getFragmentShader());
	Shader::useShader(shaderProgram); 
	
	Renderer::init(shaderProgram);

	Textures::init(shaderProgram);

	Entity* background = entityManager->spawnEntity(BACKGROUND, -1.0f, -1.0f, 0.0f, BACKGROUND, nullptr, nullptr);
	Entity* terrain = entityManager->spawnEntity(TERRAIN, -1.0f, -1.0f, 0.0f, TERRAIN, nullptr, nullptr);
	Entity* player = entityManager->spawnEntity(PLAYER, -0.9f, 0.0f, 0.0f, PLAYER, nullptr, nullptr);
	Entity* enemy = entityManager->spawnEntity(ENEMY, 0.7f, 0.0f, 0.0f, ENEMY, nullptr, nullptr);

	srand(time(0));

	while (!glfwWindowShouldClose(window)) {

		if (keyIsPressed[GLFW_KEY_W] == true || keyIsPressed[GLFW_KEY_UP] == true) {
			player->updatePositionY((1.0f / SCREENHEIGHT) * 8.0f);
		}

		if (keyIsPressed[GLFW_KEY_S] == true || keyIsPressed[GLFW_KEY_DOWN] == true) {
			player->updatePositionY(-(1.0f / SCREENHEIGHT) * 8.0f);
		}

		if (keyIsPressed[GLFW_KEY_SPACE] == true) {
			entityManager->spawnEntity(PROJECTILE, player->getGunPositionX(), player->getGunPositionY(), 0.0f, 
										PLAYER, nullptr, nullptr);
			keyIsPressed[GLFW_KEY_SPACE] = false; // prevent bullet spam
		}

		// TODO move this into the enemy entity somehow and call from manager(?)
		if (rand() % 1000 < 10) {
			entityManager->spawnEntity(PROJECTILE, enemy->getGunPositionX(), enemy->getGunPositionY(), 0.0f, ENEMY,
				enemy->getProjectileSourcePosition(), player->getProjectileTargetPosition());
		}

		entityManager->updateVertexBuffers();
		entityManager->checkCollisions();

		Renderer::drawEntities(shaderProgram, entityManager);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	Shader::deleteShader(shaderProgram);

	glfwTerminate();
	return 0;
}

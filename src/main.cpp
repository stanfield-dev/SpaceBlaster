#include "sb_defines.h"
#include "Background.h"
#include "Game.h"
#include "EntityManager.h"
#include "Renderer.h"
#include "Shader.h"
#include "SoundEngine.h"
#include "Terrain.h"
#include "Textures.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>

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

// for update tick
std::chrono::steady_clock::time_point m_startTime, m_endTime;
std::chrono::duration<double,std::ratio<1, 1000>> elapsedTime;

int main(void) {
	GLFWwindow* window;
	int hibernationState = 0;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

	unsigned int shaderProgram = Shader::createShader(Shader::getVertexShader(), Shader::getFragmentShader());
	Shader::useShader(shaderProgram); 

	Textures::init(shaderProgram);
	Renderer::init(shaderProgram);

	SoundEngine* soundEngine = new SoundEngine();
	EntityManager *entityManager = new EntityManager(soundEngine);
	Game* game = new Game(entityManager, soundEngine);

	m_startTime = std::chrono::steady_clock::now();

	soundEngine->playSound(BACKGROUND_MUSIC);

	while (!glfwWindowShouldClose(window)) {

		int gameState = game->gameState();
		int lastState = game->lastGameState();

		if (keyIsPressed[GLFW_KEY_MINUS] == true) {
			soundEngine->changeVolume(-0.05f);
			keyIsPressed[GLFW_KEY_MINUS] = false;
		}

		if (keyIsPressed[GLFW_KEY_EQUAL] == true) {
			soundEngine->changeVolume(0.05f);
			keyIsPressed[GLFW_KEY_EQUAL] = false;
		}

		if (keyIsPressed[GLFW_KEY_ESCAPE] == true) {
			if (gameState == COMBATst) {
				game->setGameState(STARTSCREENst, COMBATst);
				gameState = STARTSCREENst;
			}
			keyIsPressed[GLFW_KEY_ESCAPE] = false;
		}

		if (keyIsPressed[GLFW_KEY_F1] == true && gameState != GAMEOVERst) {
			if (gameState == STARTSCREENst) {
				hibernationState = game->lastGameState();
			}
			game->setGameState(HELPSCREENst, gameState);
			keyIsPressed[GLFW_KEY_F1] = false;
		}

		if (keyIsPressed[GLFW_KEY_ENTER] == true) {
			if (gameState == STARTSCREENst) {
				if (lastState == NEWGAMEst) {
					game->setGameState(COMBATst, gameState);
					gameState = COMBATst;
				}
				else if (lastState == COMBATst) {
					game->setGameState(lastState, gameState);
					gameState = COMBATst;
				}
			}

			if (gameState == HELPSCREENst) {
				if (lastState == STARTSCREENst) {
					game->setGameState(STARTSCREENst, hibernationState);
				}
				else {
					game->setGameState(lastState, HELPSCREENst);
				}
			}

			if (gameState == GAMEOVERst) {
				game->setGameState(NEWGAMEst, gameState);
				gameState = NEWGAMEst;
			}
			keyIsPressed[GLFW_KEY_ENTER] = false;
		}

		m_endTime = std::chrono::steady_clock::now();
		elapsedTime = (m_endTime - m_startTime);

		if (elapsedTime.count() > 16) {  // 16ms, 60fps

			Entity* player = entityManager->getEntity(PLAYER);
			if (player != nullptr) {

				if (keyIsPressed[GLFW_KEY_W] == true || keyIsPressed[GLFW_KEY_UP] == true) {
					player->updatePositionY((1.0f / SCREENHEIGHT) * 25.0f);
				}

				if (keyIsPressed[GLFW_KEY_S] == true || keyIsPressed[GLFW_KEY_DOWN] == true) {
					player->updatePositionY(-(1.0f / SCREENHEIGHT) * 25.0f);
				}

				if (keyIsPressed[GLFW_KEY_SPACE] == true) {
					entityManager->spawnEntity(
						PROJECTILE,
						player->getGunPosition().x,
						player->getGunPosition().y,
						0.0f,
						PLAYER,
						nullptr,
						nullptr
					);
					keyIsPressed[GLFW_KEY_SPACE] = false; // prevent bullet spam
				}
			}

			game->update(gameState, entityManager);
			glfwPollEvents();
			m_startTime = std::chrono::steady_clock::now();
		}

		glClear(GL_COLOR_BUFFER_BIT);

		Renderer::drawEntities(gameState, shaderProgram, entityManager);

		glfwSwapBuffers(window);

	}

	Shader::deleteShader(shaderProgram);

	glfwTerminate();

	return 0;
}

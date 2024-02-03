#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <time.h>

#include "defines.h"
#include "Background.h"
#include "Renderer.h"
#include "Enemy.h"
#include "Terrain.h"
#include "Player.h"
#include "Shader.h"
#include "Textures.h"
#include "VertexBuffers.h"

Player playerOne;
Enemy enemyOne;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
			case GLFW_KEY_ESCAPE	:	glfwSetWindowShouldClose(window, 1);
										break;
			case GLFW_KEY_Q			:	glfwSetWindowShouldClose(window, 1);
										break;
			case GLFW_KEY_W			:	[[fallthrough]];
			case GLFW_KEY_UP		:	playerOne.updatePosY( (1.0f / SCREENHEIGHT) * 20 );
										playerOne.updatePlayerVertices(playerOne.calculatePlayerPosition());
										break;
			case GLFW_KEY_A			:	[[fallthrough]];
			case GLFW_KEY_LEFT		:	playerOne.updatePosX(-(1.0f / SCREENWIDTH) * 20);
										playerOne.updatePlayerVertices(playerOne.calculatePlayerPosition());
										break;
			case GLFW_KEY_DOWN		:	[[fallthrough]];
			case GLFW_KEY_S			:	playerOne.updatePosY(-(1.0f / SCREENHEIGHT) * 20);
										playerOne.updatePlayerVertices(playerOne.calculatePlayerPosition());
										break;
			case GLFW_KEY_RIGHT		:	[[fallthrough]];
			case GLFW_KEY_D			:	playerOne.updatePosX((1.0f / SCREENWIDTH) * 20);
										playerOne.updatePlayerVertices(playerOne.calculatePlayerPosition());
										break;
		}
	}
}

int main(void) {
	GLFWwindow* window;
	Renderer renderEngine;

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

	unsigned int shaderProgram = Shader::createShader(Shader::getVertexShader(), Shader::getFragmentShader());
	Shader::useShader(shaderProgram);

	VertexBuffers::init();
	Background::init();
	Terrain::init();
	enemyOne.init();
	playerOne.init();
	renderEngine.init();
	Textures::init(shaderProgram);

	int frame = 0;

	while (!glfwWindowShouldClose(window)) {

		if (frame == 5) {
			Background::scrollBackground();
			frame = 0;
		}


		renderEngine.draw(shaderProgram);

		glfwSwapBuffers(window);

		glfwPollEvents();

		frame++;
	}

	Shader::deleteShader(shaderProgram);

	glfwTerminate();
	return 0;
}

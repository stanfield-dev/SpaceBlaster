#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "defines.h"
#include "Renderer.h"
#include "Player.h"
#include "Shader.h"
#include "Texture.h"

Renderer renderEngine;
Player playerOne;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_ESCAPE	:	glfwSetWindowShouldClose(window, 1);
									break;
		case GLFW_KEY_Q			:	glfwSetWindowShouldClose(window, 1);
									break;
		case GLFW_KEY_W			:	playerOne.updatePosY( (1.0f / SCREENHEIGHT) * 20 );
									break;
		case GLFW_KEY_A			:	playerOne.updatePosX(-(1.0f / SCREENWIDTH) * 20);
									break;
		case GLFW_KEY_S			:	playerOne.updatePosY(-(1.0f / SCREENHEIGHT) * 20);
									break;
		case GLFW_KEY_D			:	playerOne.updatePosX( (1.0f / SCREENWIDTH) * 20);
									break;
		}
	}
}

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

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

	renderEngine.init();

	unsigned int shaderProgram = Shader::createShader(Shader::getVertexShader(), Shader::getFragmentShader());
	Shader::useShader(shaderProgram);

	renderEngine.renderBackground(shaderProgram);

	playerOne.setShaderID(shaderProgram);

	//playerOne.updatePlayerVertices(PlayerOne.calculatePlayerPosition());

	
	//Texture::loadTexture(PLAYER_SPRITE, GL_TEXTURE_2D, shaderProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//playerOne.updatePlayerVertices(PlayerOne.calculatePlayerPosition());

		renderEngine.draw();
		//glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	Shader::deleteShader(shaderProgram);

	glfwTerminate();
	return 0;
}

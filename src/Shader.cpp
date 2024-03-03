#include <GL/glew.h>

#include "sb_defines.h"
#include "Shader.h"

#include <iostream>
#include <fstream>

int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int programID = glCreateProgram();
	unsigned int vsID = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fsID = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(programID, vsID);
	glAttachShader(programID, fsID);
	glLinkProgram(programID);
	glValidateProgram(programID);

	glDeleteShader(vsID);
	glDeleteShader(fsID);

	setShaderID(programID);

	return programID;
}

void Shader::setShaderID(unsigned int id)
{
	m_shaderID = id;
}

unsigned int Shader::getShaderID()
{
	return m_shaderID;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);

	setShaderID(id);

	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") <<
			" SHADER COMPILATION FAILURE!!!" << std::endl;
		std::cout << message << std::endl;
		free(message);
		glDeleteShader(id);
		return 0;
	}
	
	return id;
}

void Shader::useShader(unsigned int shaderProgram)
{
	glUseProgram(shaderProgram);
}

void Shader::deleteShader(unsigned int shaderProgram)
{
	glDeleteProgram(shaderProgram);
}


std::string Shader::getVertexShader()
{
	//std::string temp, vertShaderText;

	//std::ifstream file(VSHADER_PATH);
	//while (std::getline(file, temp)) {
	//	if (!file.eof() && !file.fail()) {
	//		vertShaderText.append(temp);
	//		vertShaderText.append("\n");
	//	}
	//}



	//
	// barebones shaders which I don't want to include as separate files with the exe, so...
	//
	std::string vertShaderText = 
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec3  a_objectCoord;\n"
		"layout(location = 1) in vec2  a_textureCoord;\n"
		"layout(location = 2) in float a_textureID;\n"
		"\n"
		"out vec2 v_textureCoord;\n"
		"out float v_textureID;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(a_objectCoord, 1.0);\n"
		"	v_textureCoord = a_textureCoord;\n"
		"	v_textureID = a_textureID;\n"
		"}\n";

	return vertShaderText;
}

std::string Shader::getFragmentShader()
{
	//std::string temp, fragShaderText; 
	//
	//std::ifstream file(FSHADER_PATH);
	//while (std::getline(file, temp)) {
	//	if (!file.eof() && !file.fail()) {
	//		fragShaderText.append(temp);
	//		fragShaderText.append("\n");
	//	}
	//}



	//
	// barebones shaders which I don't want to include as separate files with the exe, so...
	//
	std::string fragShaderText =
		"#version 330 core\n"
		"\n"
		"in vec2 v_textureCoord;\n"
		"in float v_textureID;\n"
		"\n"
		"out vec4 texColor;\n"
		"\n"
		"uniform sampler2D u_textures[11];\n"
		"\n"
		"void main()\n"
		"{\n"
		"	int index = int(v_textureID);\n"
		"	texColor = texture(u_textures[index], v_textureCoord);\n"
		"}\n";

	return fragShaderText;
}



#include <GL/glew.h>

#include "defines.h"
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
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") <<
			" SHADER COMPILATION FAILURE!!!" << std::endl;
		std::cout << message << std::endl;
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
	std::string temp, vertShaderText;

	std::ifstream file(VSHADER_PATH);
	while (std::getline(file, temp)) {
		if (!file.eof() && !file.fail()) {
			vertShaderText.append(temp);
			vertShaderText.append("\n");
		}
	}

	return vertShaderText;
}

std::string Shader::getFragmentShader()
{
	std::string temp, fragShaderText; 
	
	std::ifstream file(FSHADER_PATH);
	while (std::getline(file, temp)) {
		if (!file.eof() && !file.fail()) {
			fragShaderText.append(temp);
			fragShaderText.append("\n");
		}
	}

	return fragShaderText;
}



#include <iostream>
#include <string>

#include <GL/glew.h>

#include "stb_image.h"

#include "Textures.h"
#include "Shader.h"


Textures::Textures()
{
}

Textures::~Textures()
{
}

void Textures::init(unsigned int shaderProgram)
{
	unsigned int loc;
	
	glGenTextures(1, &m_backgroundTextureID);
	glGenTextures(1, &m_playerTextureID);
	glGenTextures(1, &m_enemyTextureID);
	glGenTextures(1, &m_terrainTextureID);

	m_backgroundTextureID = loadTexture(BACKGROUND);
	glBindTextureUnit(BACKGROUND, m_backgroundTextureID);

	m_playerTextureID = loadTexture(PLAYER);
	glBindTextureUnit(PLAYER, m_playerTextureID);

	//m_enemyTextureID = loadTexture(ENEMY);
	//glBindTextureUnit(ENEMY, m_enemyTextureID);
	//m_terrainTextureID = loadTexture(TERRAIN);
	//glBindTextureUnit(TERRAIN, m_terrainTextureID);

	loc = glGetUniformLocation(shaderProgram, "u_textures");

	int samplers[4] = { 0, 1, 2, 3 };
	glUniform1iv(loc, 4, samplers);
}

unsigned int Textures::loadTexture(int type)
{ 
	std::string desc, path;
	unsigned int textureID;
	int target;

	switch (type) {
		case BACKGROUND	:	path = BACKGROUND_IMAGE;
							target = GL_TEXTURE_2D;
							break;
		case PLAYER		:	path = PLAYER_SPRITE;
							target = GL_TEXTURE_2D;
							break;
		case ENEMY		:	path = BACKGROUND_IMAGE;
							target = GL_TEXTURE_2D;
							break;
		case TERRAIN	:	path = BACKGROUND_IMAGE;
							target = GL_TEXTURE_2D;
							break;
	}

	loadImage(path);

	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(target, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

	if (m_textureData) {
		stbi_image_free(m_textureData);
	}

	return textureID;
}

void Textures::loadImage(const std::string& path)
{
	stbi_set_flip_vertically_on_load(1);
	m_textureData = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	if (m_textureData == nullptr)
		std::cout << "FAILED TO LOAD TEXTURE FILE: " << stbi_failure_reason() << std::endl;
}





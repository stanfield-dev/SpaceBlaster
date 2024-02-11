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
	unsigned int loc0;

	loadTexture(PLAYER);
	loadTexture(ENEMY);
	loadTexture(PROJECTILE);
	loadTexture(TERRAIN);
	loadTexture(BACKGROUND);

	loc0 = glGetUniformLocation(shaderProgram, "u_textures");
	int samplers[5] = { 0, 1, 2, 3, 4 }; 
	glUniform1iv(loc0, 5, samplers);
}

void Textures::loadTexture(int type)
{ 
	if (type == BACKGROUND) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_backgroundTextureID);
		glBindTexture(GL_TEXTURE_2D, m_backgroundTextureID);

		loadImage(BACKGROUND_IMAGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(0, m_backgroundTextureID);
	}

	if (type == PLAYER) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_playerTextureID);
		glBindTexture(GL_TEXTURE_2D, m_playerTextureID);

		loadImage(PLAYER_SPRITE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(1, m_playerTextureID);
	}

	if (type == ENEMY) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_enemyTextureID);
		glBindTexture(GL_TEXTURE_2D, m_enemyTextureID);

		loadImage(ENEMY_SPRITE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(2, m_enemyTextureID);
	}

	if (type == TERRAIN) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_terrainTextureID);
		glBindTexture(GL_TEXTURE_2D, m_terrainTextureID);

		loadImage(TERRAIN_SPRITE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(3, m_terrainTextureID);
	}

	if (type == PROJECTILE) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_projectileTextureID);
		glBindTexture(GL_TEXTURE_2D, m_projectileTextureID);

		loadImage(PROJECTILE_SPRITE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(4, m_projectileTextureID);
	}

	if (m_textureData) {
		stbi_image_free(m_textureData);
	}
}

void Textures::loadImage(const std::string& path)
{
	stbi_set_flip_vertically_on_load(1);
	m_textureData = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	if (m_textureData == nullptr)
		std::cout << "FAILED TO LOAD TEXTURE FILE: " << path << " " << stbi_failure_reason() << std::endl;
}





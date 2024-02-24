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
	loadTexture(EXPLOSION);
	loadTexture(STARTSCREEN);
	loadTexture(HELPSCREEN);
	loadTexture(COUNTDOWN);
	loadTexture(SCORE);
	loadTexture(HEALTHBAR);
	loadTexture(BACKGROUND);

	loc0 = glGetUniformLocation(shaderProgram, "u_textures");
	int samplers[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
	glUniform1iv(loc0, 11, samplers);
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

		glBindTextureUnit(BACKGROUND, m_backgroundTextureID);
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

		glBindTextureUnit(PLAYER, m_playerTextureID);
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

		glBindTextureUnit(ENEMY, m_enemyTextureID);
	}

	if (type == PROJECTILE) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_projectileTextureID);
		glBindTexture(GL_TEXTURE_2D, m_projectileTextureID);

		loadImage(PROJECTILE_SPRITE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(PROJECTILE, m_projectileTextureID);
	}

	if (type == EXPLOSION) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_explosionTextureID);
		glBindTexture(GL_TEXTURE_2D, m_explosionTextureID);

		loadImage(EXPLOSION_SPRITE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(EXPLOSION, m_explosionTextureID);
	}

	if (type == STARTSCREEN) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_menuTextureID);
		glBindTexture(GL_TEXTURE_2D, m_menuTextureID);

		loadImage(STARTSCREEN_IMAGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(STARTSCREEN, m_menuTextureID);
	}

	if (type == HELPSCREEN) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_helpTextureID);
		glBindTexture(GL_TEXTURE_2D, m_helpTextureID);

		loadImage(HELPSCREEN_IMAGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(HELPSCREEN, m_helpTextureID);
	}

	if (type == COUNTDOWN) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_countdownTextureID);
		glBindTexture(GL_TEXTURE_2D, m_countdownTextureID);

		loadImage(COUNTDOWN_IMAGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(COUNTDOWN, m_countdownTextureID);
	}

	if (type == SCORE) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_numbersTextureID);
		glBindTexture(GL_TEXTURE_2D, m_numbersTextureID);

		loadImage(NUMBERS_IMAGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(SCORE, m_numbersTextureID);
	}

	if (type == HEALTHBAR) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_healthbarTextureID);
		glBindTexture(GL_TEXTURE_2D, m_healthbarTextureID);

		loadImage(HEALTHBAR_IMAGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(HEALTHBAR, m_healthbarTextureID);
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





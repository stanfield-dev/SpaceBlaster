#include <iostream>
#include <string>

#include <GL/glew.h>

#include "stb_image.h"

#include "Texture.h"

void Texture::loadImage(const std::string& path)
{
	stbi_set_flip_vertically_on_load(1);
	m_textureData = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	if (m_textureData == nullptr)
		std::cout << "FAILED TO LOAD TEXTURE FILE: " << stbi_failure_reason() << std::endl;
}

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::loadTexture(const std::string& path, GLenum texType, unsigned int shaderID)
{
	loadImage(path);

	glGenTextures(1, &m_textureID);
	glBindTexture(texType, m_textureID);
	glActiveTexture(GL_TEXTURE0 + 0);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexImage2D(texType, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

	unsigned int uloc = glGetUniformLocation(shaderID, "shipTexture");
	glProgramUniform1i(shaderID, uloc, 0);

	if (m_textureData) {
		stbi_image_free(m_textureData);
	}
}

void Texture::Bind(GLenum texType)
{
	glBindTexture(texType, 0);
	std::cout << glGetError() << std::endl;
}

void Texture::unBind()
{
}




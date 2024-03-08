#include <iostream>

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

	loc0 = glGetUniformLocation(shaderProgram, "u_textures");
	int samplers[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; 
	glUniform1iv(loc0, 11, samplers);

	libzippp::ZipArchive zf("spaceblaster.dat");
	zf.open(libzippp::ZipArchive::ReadOnly);

	loadTextures(&zf);

	zf.close();
}

void Textures::loadTextures(libzippp::ZipArchive *zf)
{ 
	for (std::vector<m_gameTexture>::iterator::value_type texture : m_gameTextures) {
		int size = 0;
		void* data = nullptr;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID[texture.textureID]);
		glBindTexture(GL_TEXTURE_2D, m_textureID[texture.textureID]);

		libzippp::ZipEntry zipFile = zf->getEntry(texture.path);
		size = zipFile.getSize();
		data = zipFile.readAsBinary();
		loadImage(size, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (texture.textureID == 0) { // background needs to repeat as it scrolls
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

		glBindTextureUnit(texture.textureID, m_textureID[texture.textureID]);

	}

	if (m_textureData) {
		stbi_image_free(m_textureData);
	}
}

void Textures::loadImage(int size, void* data)
{
	stbi_set_flip_vertically_on_load(1);

	m_textureData = (unsigned char*)stbi_load_from_memory((unsigned char*)data, size, &m_width, &m_height, &m_bpp, 4);

	if (m_textureData == nullptr)
		std::cout << "FAILED TO LOAD TEXTURE FILE!" << stbi_failure_reason() << std::endl;
}





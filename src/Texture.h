#pragma once

#include <GL/glew.h>
#include <string>

static class Texture {
private:
	inline static int m_width = 0;
	inline static int m_height = 0;
	inline static int m_bpp = 0;
	inline static unsigned int m_textureID = 0;
	inline static unsigned char* m_textureData = nullptr;

	void static loadImage(const std::string&);

public:
	Texture();
	~Texture();

	static void loadTexture(const std::string&, GLenum, unsigned int);
	static void Bind(GLenum);
	static void unBind();
};


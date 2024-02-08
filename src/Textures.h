#pragma once

#include "defines.h"
#include <string>

static class Textures {
private:
	inline static int m_width = 0;
	inline static int m_height = 0;
	inline static int m_bpp = 0;

	inline static unsigned int m_backgroundTextureID;
	inline static unsigned int m_enemyTextureID;
	inline static unsigned int m_playerTextureID;
	inline static unsigned int m_projectileTextureID;
	inline static unsigned int m_terrainTextureID;

	inline static unsigned char* m_textureData = nullptr;

	void static loadImage(const std::string&);

public:
	Textures();
	~Textures();

	static void init(unsigned int);
	static void loadTexture(int);
};


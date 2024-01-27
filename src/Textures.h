#pragma once

#include "defines.h"
#include <string>

static class Textures {
private:
	inline static int m_width = 0;
	inline static int m_height = 0;
	inline static int m_bpp = 0;

	inline static float m_textureVertices[8] = {
		-1.0f, -1.0f,	//  LL
		-1.0f,  1.0f,	//  LR
		 1.0f,  1.0f,	//  UR
		 1.0f, -1.0f,	//  UL
	};

	inline static unsigned int m_backgroundTextureID;
	inline static unsigned int m_playerTextureID;
	inline static unsigned int m_enemyTextureID;
	inline static unsigned int m_terrainTextureID;

	inline static unsigned int m_samplerID = 0;
	inline static unsigned char* m_textureData = nullptr;

	void static loadImage(const std::string&);

public:
	Textures();
	~Textures();

	static void init(unsigned int);
	static unsigned int loadTexture(int);
};


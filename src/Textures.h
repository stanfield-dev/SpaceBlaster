#pragma once

#include "sb_defines.h"
#include <string>

class Textures {
private:
	inline static int m_width = 0;
	inline static int m_height = 0;
	inline static int m_bpp = 0;

	inline static unsigned int m_backgroundTextureID;
	inline static unsigned int m_countdownTextureID;
	inline static unsigned int m_enemyTextureID;
	inline static unsigned int m_explosionTextureID;
	inline static unsigned int m_gameoverTextureID;
	inline static unsigned int m_healthbarTextureID;
	inline static unsigned int m_helpscreenTextureID;
	inline static unsigned int m_startscreenTextureID;
	inline static unsigned int m_numbersTextureID;
	inline static unsigned int m_playerTextureID;
	inline static unsigned int m_projectileTextureID;

	inline static unsigned char* m_textureData = nullptr;

	void static loadImage(const std::string&);

public:
	Textures();
	~Textures();

	static void init(unsigned int);
	static void loadTexture(int);
};


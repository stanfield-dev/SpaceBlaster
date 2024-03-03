#pragma once

#include "sb_defines.h"

#include "libzippp.h"
#include <string>

class Textures {
private:
	inline static int m_width = 0;
	inline static int m_height = 0;
	inline static int m_bpp = 0;

	struct m_gameTexture
	{
		int textureID;
		std::string path;
	};

	inline static std::vector<m_gameTexture> gameTextures =
	{
		{PLAYER, "textures/player-ship-spritesheet.png"},
		{ENEMY, "textures/enemy-ship-spritesheet.png"},
		{PROJECTILE, "textures/projectiles.png"},
		{EXPLOSION, "textures/explosion.png"},
		{STARTSCREEN, "textures/startscreen.png"},
		{HELPSCREEN, "textures/helpscreen.png"},
		{COUNTDOWN, "textures/countdown.png"},
		{SCORE, "textures/numbers.png"},
		{HEALTHBAR, "textures/healthbar.png"},
		{GAMEOVER, "textures/gameover.png"},
		{BACKGROUND, "textures/background.png"}
	};

	inline static unsigned int m_textureID[11];
	inline static unsigned char* m_textureData = nullptr;

	void static loadImage(int size, void*);

public:
	Textures();
	~Textures();

	static void init(unsigned int);
	static void loadTextures(libzippp::ZipArchive*);
};


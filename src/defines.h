#pragma once
#include <string>

// fixed window resolution
const float SCREENWIDTH = 1024.0f;
const float SCREENHEIGHT = 768.0f;

// dimensions of player and enemy objects in pixels
const float PLAYERWIDTH = 128.0f;
const float PLAYERHEIGHT = 128.0f;
const float ENEMYWIDTH = 128.0f;
const float ENEMYHEIGHT = 128.0f;

// shader paths
const std::string VSHADER_PATH = "src/resources/shaders/vertexShader.vert";
const std::string FSHADER_PATH = "src/resources/shaders/fragmentShader.frag";

// sprites
const std::string BACKGROUND_IMAGE = "src/resources/textures/background.png";
const std::string PLAYER_SPRITE = "src/resources/textures/player-ship-spritesheet.png";
const std::string ENEMY_SPRITE = "src/resources/textures/enemy-ship-spritesheet.png";
const std::string TERRAIN_SPRITE = "src/resources/textures/terrain.png";
const std::string PROJECTILE_SPRITE = "src/resources/textures/projectiles.png";

// friendly names
enum objectType : int
{
	BACKGROUND = 0,
	PLAYER,
	ENEMY,
	TERRAIN,
	PROJECTILE
};
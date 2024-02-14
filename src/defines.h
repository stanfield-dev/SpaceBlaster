#pragma once
#include <string>

// fixed window resolution
const float SCREENWIDTH = 1024.0f;
const float SCREENHEIGHT = 768.0f;

// dimensions of game objects in screen pixels
const float PLAYERWIDTH = 128.0f;
const float PLAYERHEIGHT = 128.0f;

const float ENEMYWIDTH = 128.0f;
const float ENEMYHEIGHT = 128.0f;

const float PROJECTILEWIDTH = 64.0f;
const float PROJECTILEHEIGHT = 32.0f;

const float EXPLOSIONWIDTH = 128.0f;
const float EXPLOSIONHEIGHT = 128.0f;

// shader paths
const std::string VSHADER_PATH = "src/resources/shaders/vertexShader.vert";
const std::string FSHADER_PATH = "src/resources/shaders/fragmentShader.frag";

// spritesheet sources
const std::string BACKGROUND_IMAGE = "src/resources/textures/background.png";
const std::string PLAYER_SPRITE = "src/resources/textures/player-ship-spritesheet.png";
const std::string ENEMY_SPRITE = "src/resources/textures/enemy-ship-spritesheet.png";
const std::string TERRAIN_SPRITE = "src/resources/textures/terrain.png";
const std::string PROJECTILE_SPRITE = "src/resources/textures/projectiles.png";
const std::string EXPLOSION_SPRITE = "src/resources/textures/explosion.png";

// friendly names
enum objectType : int
{
	BACKGROUND = 0,
	PLAYER,
	ENEMY,
	TERRAIN,
	PROJECTILE,
	EXPLOSION
};
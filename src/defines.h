#pragma once
#include <string>

#define DEBUGGERY 0

// fixed window resolution
const float SCREENWIDTH = 1920.0f;
const float SCREENHEIGHT = 1080.0f;

// dimensions of player sprite in pixels
const float PLAYERWIDTH = 128.0f;
const float PLAYERHEIGHT = 128.0f;

// shader paths
const std::string VSHADER_PATH = "src/resources/shaders/vertexShader.vert";
const std::string FSHADER_PATH = "src/resources/shaders/fragmentShader.frag";

// sprites
const std::string PLAYER_SPRITE = "src/resources/textures/playerShip1_blue.png";
const std::string BACKGROUND_IMAGE = "src/resources/textures/space-background.jpg";

// VBO identifiers
enum objectType : int
{
	BACKGROUND = 0,
	PLAYER,
	ENEMY,
	TERRAIN
};
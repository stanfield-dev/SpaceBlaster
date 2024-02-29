#pragma once

#include <string>

#include "sb_datatypes.h"

// fixed window resolution
const float SCREENWIDTH = 1024.0f;
const float SCREENHEIGHT = 768.0f;

// dimensions of game objects in screen pixels
const float COUNTDOWNWIDTH = 192.0f;
const float COUNTDOWNHEIGHT = 192.0f;

const float ENEMYWIDTH = 192.0f;
const float ENEMYHEIGHT = 192.0f;

const float EXPLOSIONWIDTH = 192.0f;
const float EXPLOSIONHEIGHT = 192.0f;

const float GAMEOVERWIDTH = 1000.0f;
const float GAMEOVERHEIGHT = 400.0f;

const float HEALTHBARWIDTH = 700.0f;
const float HEALTHBARHEIGHT = 81.2f;

const float PLAYERWIDTH = 192.0f;
const float PLAYERHEIGHT = 192.0f;

const float PROJECTILEWIDTH = 128.0f;
const float PROJECTILEHEIGHT = 64.0f;

const float SCOREWIDTH = 96.0f;
const float SCOREHEIGHT = 96.0f;
const float SCORETOTALWIDTH = 3 * SCOREWIDTH;


// shader paths
const std::string VSHADER_PATH = "resources/shaders/vertexShader.vert";
const std::string FSHADER_PATH = "resources/shaders/fragmentShader.frag";

// spritesheet sources
const std::string BACKGROUND_IMAGE =		"resources/textures/background.png";
const std::string COUNTDOWN_IMAGE =			"resources/textures/countdown.png";
const std::string ENEMY_SPRITE =			"resources/textures/enemy-ship-spritesheet.png";
const std::string EXPLOSION_SPRITE =		"resources/textures/explosion.png";
const std::string GAMEOVER_IMAGE =			"resources/textures/gameover.png";
const std::string HEALTHBAR_IMAGE =			"resources/textures/healthbar.png";
const std::string HELPSCREEN_IMAGE =		"resources/textures/helpscreen.png";
const std::string NUMBERS_IMAGE =			"resources/textures/numbers.png";
const std::string PLAYER_SPRITE =			"resources/textures/player-ship-spritesheet.png";
const std::string PROJECTILE_SPRITE =		"resources/textures/projectiles.png";
const std::string STARTSCREEN_IMAGE =		"resources/textures/startscreen.png";

// audio sources
const std::string EXPLOSION_SOUND =		"resources/sounds/explosion.mp3";
const std::string GAME_MUSIC =			"resources/sounds/gamemusic.mp3";
const std::string PROJECTILE_SOUND =	"resources/sounds/projectile.mp3";


#pragma once
#include <string>

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

const float GAMEOVERWIDTH = 900.0f;
const float GAMEOVERHEIGHT = 123.0f;

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
const std::string VSHADER_PATH = "src/resources/shaders/vertexShader.vert";
const std::string FSHADER_PATH = "src/resources/shaders/fragmentShader.frag";

// spritesheet sources
const std::string BACKGROUND_IMAGE =		"src/resources/textures/background.png";
const std::string COUNTDOWN_IMAGE =			"src/resources/textures/countdown.png";
const std::string ENEMY_SPRITE =			"src/resources/textures/enemy-ship-spritesheet.png";
const std::string EXPLOSION_SPRITE =		"src/resources/textures/explosion.png";
const std::string GAMEOVER_IMAGE =			"src/resources/textures/gameover.png";
const std::string HEALTHBAR_IMAGE =			"src/resources/textures/healthbar.png";
const std::string HELPSCREEN_IMAGE =		"src/resources/textures/help.jpg";
const std::string NUMBERS_IMAGE =			"src/resources/textures/numbers.png";
const std::string PLAYER_SPRITE =			"src/resources/textures/player-ship-spritesheet.png";
const std::string PROJECTILE_SPRITE =		"src/resources/textures/projectiles.png";
const std::string STARTSCREEN_IMAGE =		"src/resources/textures/menu.jpg";

// audio sources
const std::string EXPLOSION_SOUND =		"src/resources/sounds/explosion.mp3";
const std::string GAME_MUSIC =			"src/resources/sounds/gamemusic.mp3";
const std::string PROJECTILE_SOUND =	"src/resources/sounds/projectile.mp3";

// friendly names
enum objectType : int
{
	BACKGROUND = 0,
	PLAYER,
	ENEMY,
	PROJECTILE,
	EXPLOSION,
	STARTSCREEN,
	HELPSCREEN,
	COUNTDOWN,
	SCORE,
	HEALTHBAR,
	GAMEOVER
};
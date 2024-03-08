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


// shader paths (loading via string to avoid dealing with separate files for no reason)
//const std::string VSHADER_PATH = "resources/shaders/vertexShader.vert";
//const std::string FSHADER_PATH = "resources/shaders/fragmentShader.frag";




#pragma once

#include "soloud.h"
#include "soloud_wav.h"
#include "libzippp.h"

#include "sb_defines.h"

#include <string>

class SoundEngine
{
private:
	// SoLoud objects
	SoLoud::Soloud m_soloudEngine;

	SoLoud::Wav m_bgSound;
	SoLoud::handle m_bgSoundHandle;

	SoLoud::Wav m_exSound;
	SoLoud::Wav m_prSound;

	float m_soundVolume = 1.0f;

	// audio files in spaceblaster.dat
	std::unordered_map<int, std::string> m_gameSounds =
	{
		{BACKGROUND_MUSIC, "sounds/gamemusic.mp3"},
		{EXPLOSION_SOUND,  "sounds/explosion.mp3"},
		{PROJECTILE_SOUND, "sounds/projectile.mp3"}
	};

	void* m_bgSoundData = nullptr;
	void* m_exSoundData = nullptr;
	void* m_prSoundData = nullptr;

	void loadGameSounds(libzippp::ZipArchive*);

public:
	SoundEngine();
	~SoundEngine();

	void playSound(int);
	void changeVolume(float);
};
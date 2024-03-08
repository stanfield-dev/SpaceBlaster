#include "SoundEngine.h"

#include <iostream>

SoundEngine::SoundEngine()
{
	m_soloudEngine.init();

	libzippp::ZipArchive zf("spaceblaster.dat");
	zf.open(libzippp::ZipArchive::ReadOnly);

	loadGameSounds(&zf);

	zf.close();
}

SoundEngine::~SoundEngine()
{
	m_soloudEngine.deinit();
}

void SoundEngine::loadGameSounds(libzippp::ZipArchive* zf)
{
	libzippp::ZipEntry zipFile;
	int size;

	zipFile = zf->getEntry(m_gameSounds[BACKGROUND_MUSIC]);
	m_bgSoundData = zipFile.readAsBinary();
	size = zipFile.getSize();
	m_bgSound.loadMem((unsigned char*)m_bgSoundData, size);

	zipFile = zf->getEntry(m_gameSounds[EXPLOSION_SOUND]);
	m_exSoundData = zipFile.readAsBinary();
	size = zipFile.getSize();
	m_exSound.loadMem((unsigned char*)m_exSoundData, size);

	zipFile = zf->getEntry(m_gameSounds[PROJECTILE_SOUND]);
	m_prSoundData = zipFile.readAsBinary();
	size = zipFile.getSize();
	m_prSound.loadMem((unsigned char*)m_prSoundData, size);
}

void SoundEngine::playSound(int sound)
{
	switch (sound) {
		case BACKGROUND_MUSIC:
			{
				m_bgSoundHandle = m_soloudEngine.play(m_bgSound);
				m_soloudEngine.setLooping(m_bgSoundHandle, 1);
			}
			break;
		case EXPLOSION_SOUND:
			{
				m_soloudEngine.play(m_exSound);
			}
			break;
		case PROJECTILE_SOUND:
			{
				m_soloudEngine.play(m_prSound);
			}
			break;
	}
}

void SoundEngine::changeVolume(float soundVolume)
{
	m_soundVolume += soundVolume;

	if (m_soundVolume < 0) {
		m_soundVolume = 0;
	}
	m_soloudEngine.setGlobalVolume(m_soundVolume);
}

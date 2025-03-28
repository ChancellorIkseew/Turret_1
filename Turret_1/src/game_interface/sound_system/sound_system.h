#pragma once
#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <SFML/Audio.hpp>
#include "sound_enum.h"
#include "sound_on_tile.h"
#include "game_interface/gameplay/gameplay_util/camera.h"

class SoundSystem
{
private:
	static inline sf::Music soundTreak1;
	static inline sf::SoundBuffer autocannon;
	static inline std::list<sf::Sound> sounds;
	static inline std::vector<SoundOnTile> preSounds;

	static inline float soundsVolumeModifier = 20.0f;

	static void pushNewSounds(const Camera& camera);
	static void removeFinishedSounds();
	static sf::Sound createSound(const SoundType type);

public:
	static void loadSounds();
	static void setVolumeBySettings();
	static void startMusic();

	static void pushSound(const SoundType type, const TileCoord tile);
	static void updateSounds(const Camera& camera);
	static void clearSounds();

};

#endif // SOUND_SYSTEM_H
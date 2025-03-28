
#include "sound_system.h"
#include <mutex>

static std::mutex soundsMutex;

void SoundSystem::loadSounds()
{
	soundTreak1.openFromFile("sounds/neutral_music.mp3");
	soundTreak1.setVolume(5);


	autocannon.loadFromFile("sounds/combat/autocannon.mp3");
}

void SoundSystem::startMusic()
{
	soundTreak1.setLooping(true);
	soundTreak1.play();
}

void SoundSystem::pushSound(const SoundType type, const TileCoord tile)
{
	std::lock_guard<std::mutex> guard(soundsMutex);
	preSounds.emplace_back(type, tile);
}

void SoundSystem::pushNewSounds(const Camera& camera)
{
	std::lock_guard<std::mutex> guard(soundsMutex);
	std::unordered_set<SoundType> newSounds;
	for (const auto& it : preSounds)
	{
		if (!camera.contains(it.tile) || newSounds.count(it.type))
			continue;	
		newSounds.insert(it.type);
		sounds.push_back(SoundSystem::createSound(it.type));
		sounds.back().play();
	}
	preSounds.clear();
}

void SoundSystem::removeFinishedSounds()
{
	for (auto it = sounds.begin(); it != sounds.end();)
	{
		sf::Sound& sound = *it;
		if (sound.getStatus() == sf::SoundSource::Status::Stopped)
			it = sounds.erase(it);
		else
			++it;
	}
}

void SoundSystem::updateSounds(const Camera& camera)
{
	removeFinishedSounds();
	pushNewSounds(camera);
}

void SoundSystem::clearSounds()
{
	preSounds.clear();
	sounds.clear();
}

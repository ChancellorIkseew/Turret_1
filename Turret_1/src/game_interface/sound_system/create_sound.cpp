
#include "sound_system.h"

sf::Sound SoundSystem::createSound(const SoundType type)
{
	switch (type)
	{
	case SoundType::AC_SHOOT:
		return sf::Sound(autocannon);
	default:
		std::cout << "Sound_type does not exist. Type: " << static_cast<uint16_t>(type) << ".\n";
		return sf::Sound(autocannon);
	}
}

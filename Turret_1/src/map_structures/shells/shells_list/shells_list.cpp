
#include <iostream>
#include <cereal/types/memory.hpp>
#include <cereal/types/list.hpp>
#include "game_interface/gameplay/gameplay_util/camera.h"
#include "game_interface/sound_system/sound_system.h"

#include "shells_list.h"


void ShellsList::save(cereal::BinaryOutputArchive& archive) const {
	archive(shellsList);
}
void ShellsList::load(cereal::BinaryInputArchive& archive) {
	archive(shellsList);
}


void ShellsList::spawnShell(const ShellType type, const PixelCoord coord, const float angleRad, Team* team)
{
	auto shell = Shell::createShell(type, coord, angleRad, team);
	if (shell == nullptr)
		return;
	shellsList.push_back(std::move(shell));
	SoundSystem::pushSound(SoundType::AC_SHOOT, t1::be::tile(coord));
}


void ShellsList::interact()
{
	for (auto it = shellsList.begin(); it != shellsList.end();)
	{
		Shell& shell = **it;
		shell.motion();
		shell.tryHitting();

		if (shell.getIsWasted())
		{
			shell.explosion();
			it = shellsList.erase(it);
		}
		else
			++it;
	}
}


void ShellsList::draw(sf::RenderWindow& window, const Camera& camera)
{
	for (auto& shell : shellsList)
	{
		const TileCoord tile = t1::be::tile(shell->getCoord());
		if (camera.contains(tile))
			shell->draw(window);
	}
}

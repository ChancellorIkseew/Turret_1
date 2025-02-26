
#include <iostream>
#include <cereal/types/memory.hpp>
#include <cereal/types/list.hpp>
#include "game_interface/gameplay/gameplay_util/camera.h"

#include "shells_list.h"


void ShellsList::save(cereal::BinaryOutputArchive& archive) const {
	archive(shellsList);
}
void ShellsList::load(cereal::BinaryInputArchive& archive) {
	archive(shellsList);
}


void ShellsList::spawnShell(const ShellType type, const PixelCoord coord, float angleRad, float angleDeg, Team* const team)
{
	try
	{
		shellsList.emplace_back(Shell::createShell(type, coord, angleRad, angleDeg, team));
	}
	catch (std::exception)
	{
		std::cout << "Shell_type does not exist. Type: " << static_cast<uint16_t>(type) << ".\n";
	}
}


void ShellsList::interact()
{
	for (auto it = shellsList.begin(); it != shellsList.end();)
	{
		(*it)->motion();
		(*it)->tryHitting();

		if ((*it)->getIsWasted())
		{
			(*it)->explosion();
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
		const TileCoord start = camera.getStartTile();
		const TileCoord end = camera.getEndTile();
		if (tile.x >= start.x && tile.x <= end.x && tile.y >= start.y && tile.y <= end.y)
			shell->draw(window);
	}
}

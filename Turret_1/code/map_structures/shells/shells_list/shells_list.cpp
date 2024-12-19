
#include <iostream>
#include <cereal/types/memory.hpp>
#include <cereal/types/list.hpp>

#include "shells_list.h"


void ShellsList::save(cereal::BinaryOutputArchive& archive) const
{
	archive(shellsList);
}

void ShellsList::load(cereal::BinaryInputArchive& archive)
{
	archive(shellsList);
}

void ShellsList::spawnShell(const uint16_t type, const PixelCoord coord, float angleRad, float angleDeg, Team* const team)
{
	try
	{
		shellsList.emplace_back(Shell::createShell(type, coord, angleRad, angleDeg, team));
	}
	catch (std::exception)
	{
		std::cout << "shell_type does not exist. type: " << type << '\n';
	}
}


void ShellsList::move()
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


void ShellsList::draw(sf::RenderWindow& window)
{
	for (auto it = shellsList.begin(); it != shellsList.end(); ++it)
	{
		(*it)->draw(window);

	}
}


void ShellsList::clean() noexcept
{
	shellsList.clear();
}

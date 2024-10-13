
#include "iostream"

#include "shells_list.h"

<<<<<<< Updated upstream
#include "map_structures/shells/shell/shell.h"


void ShellsList::save(const std::string& folder)
{

}

void ShellsList::load(const std::string& folder)
=======

ShellsList::ShellsList()
>>>>>>> Stashed changes
{

}

<<<<<<< Updated upstream
void ShellsList::spawnShell(short type, const PixelCoord coord, float angleRad, float angleDeg)
{
	shellsList.emplace_back(Shell::createShell(type, coord, angleRad, angleDeg));
}


void ShellsList::move()
{
	for (auto it = shellsList.begin(); it != shellsList.end();)
	{
=======

void ShellsList::save(const std::string& folder)
{

}

void ShellsList::load(const std::string& folder)
{

}

void ShellsList::spawnShell(short type, const PixelCoord coord, float angleRad, float angleDeg, Team* team)
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
>>>>>>> Stashed changes
		(*it)->motion();
		(*it)->tryShellsHitting();

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

#pragma once
#ifndef SHELLS_LIST_H
#define SHELLS_LIST_H

#include <fstream>
#include <SFML\Graphics.hpp>
#include <list>

#include "map_structures/shells/shell/shell.h"

namespace t1::sh
{
	extern std::list<std::unique_ptr<Shell>> playerShellsList;
	extern std::list<std::unique_ptr<Shell>> enemyShellsList;

	void saveShellsList(const std::string& folder);
	void loadShellsList(const std::string& folder);

	void moveShellsList();

	void drawShellsList(sf::RenderWindow& window);

	void cleanShellsList();
}

#endif // SHELLS_LIST_H

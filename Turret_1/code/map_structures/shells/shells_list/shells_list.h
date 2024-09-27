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

	void cleanShellsList();

	void moveShellsList(int time);
	void checkShellsHitting();

	void loadShellsList(int saveFileNumber);
	void saveShellsList(int saveFileNumber);

	void drawShellsList(sf::RenderWindow& window, int time);
}

#endif // SHELLS_LIST_H

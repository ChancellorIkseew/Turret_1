#pragma once
#ifndef SHELLS_LIST_H
#define SHELLS_LIST_H

#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/shells/shell/shell.h"


class ShellsList
{
private:
	std::list<std::unique_ptr<Shell>> shellsList;
	
public:
	ShellsList();
	~ShellsList() = default;

	void save(const std::string& folder);
	void load(const std::string& folder);

	void spawnShell(short type, const PixelCoord coord, float angleRad, float angleDeg, Team* team);
	void move();

	void draw(sf::RenderWindow& window);

	void clean() noexcept;

};

#endif // SHELLS_LIST_H

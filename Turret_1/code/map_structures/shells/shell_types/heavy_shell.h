#pragma once
#ifndef HEAVY_SHELL_H
#define HEAVY_SHELL_H

#include <SFML\Graphics.hpp>

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/shells/shells.h"


class HeavyShell : public Shell
{
public:

	HeavyShell(int type, float coordX, float coordY, float angleRad, float angleDeg);
	~HeavyShell() = default;

	void tryPlayerShellsHitting(BuildingsMap& buildingsMap1) override final;
	void tryEnemyShellsHitting(BuildingsMap& buildingsMap1) override final;
	void explosion(BuildingsMap& buildingsMap1) override final;

	void draw(sf::RenderWindow& window, int time) override final;

};

#endif // HEAVY_SHELL_H

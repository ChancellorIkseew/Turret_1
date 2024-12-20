#pragma once
#ifndef HEAVY_SHELL_H
#define HEAVY_SHELL_H

#include <SFML\Graphics.hpp>

#include "map_structures/shells/shell/shell.h"


class HeavyShell : public Shell
{
public:
	HeavyShell(const uint16_t type, PixelCoord coord, float angleRad, float angleDeg, Team* const team);
	~HeavyShell() = default;

	void explosion() override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // HEAVY_SHELL_H

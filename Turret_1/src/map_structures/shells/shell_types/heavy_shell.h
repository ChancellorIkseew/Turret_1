#pragma once
#ifndef HEAVY_SHELL_H
#define HEAVY_SHELL_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/shells/shell/shell.h"

class HeavyShell : public Shell
{
public:
	HeavyShell(const PixelCoord coord, const float angleRad, Team* const team);
	HeavyShell() = default;
	~HeavyShell() = default;

	ShellType getType() override final { return ShellType::HEAVY_SHELL; }
	float getDirectDamage() override final { return 20.0f; }

	void explosion() override final;

	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(HeavyShell)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Shell, HeavyShell)

#endif // HEAVY_SHELL_H

#pragma once
#ifndef AC_SHELL_H
#define AC_SHELL_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/shells/shell/shell.h"

class AutocannonShell : public Shell
{
public:
	AutocannonShell(const PixelCoord coord, const float angleRad, Team* team);
	AutocannonShell() = default;
	~AutocannonShell() = default;

	ShellType getType() override final { return ShellType::AC_SHELL; }
	float getDirectDamage() override final { return 1.0f; }

	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(AutocannonShell)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Shell, AutocannonShell)

#endif // AC_SHELL_H

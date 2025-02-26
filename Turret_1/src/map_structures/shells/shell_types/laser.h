#pragma once
#ifndef LASER_H
#define LASER_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/shells/shell/shell.h"

class Laser : public Shell
{
public:
	Laser(PixelCoord coord, float angleRad, float angleDeg, Team* const team);
	Laser() = default;
	~Laser() = default;

	ShellType getType() override final { return ShellType::LASER; }
	float getDirectDamage() override final { return 1.0f; }

	void tryHitting() override final;

	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(Laser)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Shell, Laser)

#endif // LASER_H

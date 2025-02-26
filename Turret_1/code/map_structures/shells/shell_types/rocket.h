#pragma once
#ifndef ROCKET_H
#define ROCKET_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/shells/shell/shell.h"

class Rocket : public Shell
{
public:
	Rocket(PixelCoord coord, float angleRad, float angleDeg, Team* const team);
	Rocket() = default;
	~Rocket() = default;

	ShellType getType() override final { return ShellType::ROCKET; }
	float getDirectDamage() override final { return 0.0f; }

	void tryHitting() override final;
	void explosion() override final;

	void draw(sf::RenderWindow& window) override final;
		
};

CEREAL_REGISTER_TYPE(Rocket)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Shell, Rocket)

#endif // ROCKETS_H

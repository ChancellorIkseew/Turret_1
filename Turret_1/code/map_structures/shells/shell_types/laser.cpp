
#include "laser.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

constexpr float SPEED = 8.0f;

Laser::Laser(PixelCoord coord, float angleRad, float angleDeg, Team* const team) :
	Shell(coord, angleRad, angleDeg, team)
{
	damage = 1;
	maxLifeTime = 40;
	lineMotion.x = sin(angleRad) * SPEED;
	lineMotion.y = cos(angleRad) * SPEED;
}


void Laser::tryHitting()
{
	Shell::tryHitting();

	for (auto& team : world->getTeams())
	{
		if (this->team->getID() != team.first)
		{
			for (auto& shell : team.second->getShells().getList())
			{
				if (shell->getType() == ShellType::ROCKET)
					shell->setWasted();
			}
		}
	}
}


void Laser::draw(sf::RenderWindow& window)
{
	shellSprite.setTextureRect(sf::IntRect(2, 0, 3, 7));
	shellSprite.setOrigin(2, 1);
	shellSprite.setPosition(coord.x, coord.y);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}

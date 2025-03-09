
#include "laser.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

constexpr float SPEED = 12.0f;
constexpr uint16_t MAX_LIFI_TIME = 20;

Laser::Laser(const PixelCoord coord, const float angleRad, Team* team) :
	Shell(coord, angleRad, team)
{
	restLifeTime = MAX_LIFI_TIME;
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
				if (shell->getType() == ShellType::ROCKET && abs(shell->getCoord().x - coord.x) < 5 && abs(shell->getCoord().y - coord.y) < 5)
				{
					shell->setWasted();
					isWasted = true;
				}
			}
		}
	}
}


void Laser::draw(sf::RenderWindow& window)
{
	shellSprite.setTextureRect(sf::IntRect({ 0, 6 }, { 3, 12 }));
	shellSprite.setOrigin({ 2, 1 });
	shellSprite.setPosition({ coord.x, coord.y });
	shellSprite.setRotation(sf::radians(PI - angleRad));
	window.draw(shellSprite);
}

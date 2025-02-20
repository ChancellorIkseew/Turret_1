
#include "heavy_shell.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/shells/damage/damage.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

constexpr int EXP_RADIUS = 1; // radius in tiles
constexpr int16_t EXP_DAMAGE = 10;
constexpr float SPEED = 1.6f;

HeavyShell::HeavyShell(PixelCoord coord, float angleRad, float angleDeg, Team* const team) :
	Shell(coord, angleRad, angleDeg, team)
{
	damage = 20;
	maxLifeTime = 500;
	lineMotion.x = sin(angleRad) * SPEED;
	lineMotion.y = cos(angleRad) * SPEED;
}


void HeavyShell::explosion()
{
	Damage::createBurst(coord, EXP_RADIUS, EXP_DAMAGE, 0.0f, *world);
	world->getParticles().spawnParticle(1, coord);
}


void HeavyShell::draw(sf::RenderWindow& window)
{
	shellSprite.setTextureRect(sf::IntRect(2, 0, 3, 7));
	shellSprite.setOrigin(2, 1);
	shellSprite.setPosition(coord.x, coord.y);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}


#include "heavy_shell.h"

#include "map_structures/shells/damage/damage.h"
#include "map_structures/world/world.h"

constexpr int EXP_RADIUS = 1; // radius in tiles
constexpr float EXP_DAMAGE = 10.0f;
constexpr float SPEED = 1.6f;
constexpr uint16_t MAX_LIFI_TIME = 500;

HeavyShell::HeavyShell(const PixelCoord coord, const float angleRad, Team* team) :
	Shell(coord, angleRad, team)
{
	restLifeTime = MAX_LIFI_TIME;
	lineMotion.x = sin(angleRad) * SPEED;
	lineMotion.y = cos(angleRad) * SPEED;
}


void HeavyShell::explosion()
{
	Damage::createExplosion(coord, EXP_RADIUS, EXP_DAMAGE, 0.0f, *world);
	world->getParticles().spawnParticle(1, coord);
}


void HeavyShell::draw(sf::RenderWindow& window)
{
	shellSprite.setTextureRect(sf::IntRect({ 2, 0 }, { 3, 7 }));
	shellSprite.setOrigin({ 2, 1 });
	shellSprite.setPosition({ coord.x, coord.y });
	shellSprite.setRotation(sf::radians(PI - angleRad));
	window.draw(shellSprite);
}

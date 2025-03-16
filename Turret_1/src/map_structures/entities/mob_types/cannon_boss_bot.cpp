#include "cannon_boss_bot.h"

#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

constexpr int TILE_RANGE = 20;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];

CannonBossBot::CannonBossBot(Team* team) : Entity(team)
{
	durability = 270 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void CannonBossBot::shoot()
{
	if (!aimCoord.valid())
		return;
	shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);

	if (reloadTimer > 0)
		return;
	float correctionX = cos(shootingAngleRad) * 15.0f;
	float correctionY = sin(shootingAngleRad) * 15.0f;
	team->spawnShell(ShellType::HEAVY_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad);
	team->spawnShell(ShellType::HEAVY_SHELL, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad);
	reloadTimer = 30;
}

void CannonBossBot::shootByOwnAI()
{
	Entity::aim(SPYRAL_RANGE, PIXEL_RANGE);
	shoot();
}


void CannonBossBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect({ 0, 18 }, { 43, 43 }));
	entitySprite.setOrigin({ 22, 22 });

	if (aimCoord.valid())
		entitySprite.setRotation(sf::radians(PI - shootingAngleRad));
	else
		entitySprite.setRotation(sf::radians(PI - motionAngleRad));

	entitySprite.setPosition({ coord.x, coord.y });
	window.draw(entitySprite);

	if (durability < 150)    //Boss_energy_shield
		return;
	shieldSprite.setPosition({ coord.x, coord.y });
	window.draw(shieldSprite);
}

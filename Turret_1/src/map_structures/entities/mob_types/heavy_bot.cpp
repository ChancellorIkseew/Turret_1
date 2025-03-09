
#include "heavy_bot.h"

#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"
#include "t1_system/events/events_handler.h"

constexpr int TILE_RANGE = 7;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];

HeavyBot::HeavyBot(Team* const team) : Entity(team)
{
	durability = 50 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void HeavyBot::shoot()
{
	if (!aimCoord.valid())
		return;
	shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);

	if (reloadTimer > 0)
		return;
	float correctionX = cos(shootingAngleRad) * 8.0f;
	float correctionY = sin(shootingAngleRad) * 8.0f;
	team->spawnShell(ShellType::AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad);
	team->spawnShell(ShellType::AC_SHELL, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad);
	reloadTimer = 15;
}

void HeavyBot::shootByOwnAI()
{
	Entity::aim(SPYRAL_RANGE, PIXEL_RANGE);
	shoot();
}


void HeavyBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect({ 17, 0 }, { 24, 18 }));
	entitySprite.setOrigin({ 12, 9 });

	if (aimCoord.valid())
		entitySprite.setRotation(sf::radians(PI - shootingAngleRad));
	else
		entitySprite.setRotation(sf::radians(PI - motionAngleRad));

	entitySprite.setPosition({ coord.x, coord.y });
	window.draw(entitySprite);
}

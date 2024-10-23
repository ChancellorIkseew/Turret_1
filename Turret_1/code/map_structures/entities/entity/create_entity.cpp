
#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/entity/mob_enum.h"

#include "map_structures/entities/mob_types/standard_bot.h"
#include "map_structures/entities/mob_types/heavy_bot.h"
#include "map_structures/entities/mob_types/rocket_bot.h"
#include "map_structures/entities/mob_types/laser_bot.h"

#include "map_structures/entities/mob_types/cannon_boss_bot.h"
#include "map_structures/entities/mob_types/rocket_boss_bot.h"


std::unique_ptr<Entity> Entity::createEntity(const uint16_t type, Team* const team)
{
	switch (type)
	{
	case STANDARD_BOT:
		return std::make_unique<StandardBot>(STANDARD_BOT, team);
	case HEAVY_BOT:
		return std::make_unique<HeavyBot>(HEAVY_BOT, team);
	case ROCKET_BOT:
		return std::make_unique<RocketBot>(ROCKET_BOT, team);
	case LASER_BOT:
		return std::make_unique<LaserBot>(LASER_BOT, team);
	case CANNON_BOSS:
		return std::make_unique<CannonBossBot>(CANNON_BOSS, team);
	case ROCKET_BOSS:
		return std::make_unique<RocketBossBot>(ROCKET_BOSS, team);
	default:
		throw std::exception("mob_type does not exist");
	}
}


PixelCoord Entity::randomMapBorderSpawn()
{
	using namespace t1::be;

	float coordX, coordY;
	int x = rand() % 4;
	switch (x)
	{
	case 0:
		coordX = pixelF(0);
		coordY = pixelF(rand() % (mapSize.y - 1));
		break;

	case 1:
		coordX = pixelF(rand() % (mapSize.x - 3) + 1);
		coordY = pixelF(0);
		break;

	case 2:
		coordX = pixelF(mapSize.x - 1);
		coordY = pixelF(rand() % (mapSize.y - 1));
		break;

	case 3:
		coordX = pixelF(rand() % (mapSize.x - 3) + 1);
		coordY = pixelF(mapSize.y - 1);
		break;

	default:
		coordX = pixelF(0);
		coordY = pixelF(0);
		break;
	}
	return { coordX, coordY };
}

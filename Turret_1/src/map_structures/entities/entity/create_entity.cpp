
#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/world/world.h"
#include "t1_system/random/t1_random.h"

#include "map_structures/entities/mob_types/standard_bot.h"
#include "map_structures/entities/mob_types/heavy_bot.h"
#include "map_structures/entities/mob_types/rocket_bot.h"
#include "map_structures/entities/mob_types/laser_bot.h"

#include "map_structures/entities/mob_types/cannon_boss_bot.h"
#include "map_structures/entities/mob_types/rocket_boss_bot.h"

#include "map_structures/entities/shuttle/shuttle.h"


std::unique_ptr<Entity> Entity::createEntity(const MobType type, Team* const team)
{
	switch (type)
	{
	case MobType::STANDARD_BOT:
		return std::make_unique<StandardBot>(team);
	case MobType::HEAVY_BOT:
		return std::make_unique<HeavyBot>(team);
	case MobType::ROCKET_BOT:
		return std::make_unique<RocketBot>(team);
	case MobType::LASER_BOT:
		return std::make_unique<LaserBot>(team);
	case MobType::CANNON_BOSS:
		return std::make_unique<CannonBossBot>(team);
	case MobType::ROCKET_BOSS:
		return std::make_unique<RocketBossBot>(team);
	case MobType::LIGHT_SHUTTLE:
		return std::make_unique<Shuttle>(team);
	default:
		std::cout << "Mob_type does not exist. Type: " << static_cast<uint16_t>(type) << ".\n";
		return nullptr;
	}
}


PixelCoord Entity::randomMapBorderSpawn()
{
	using namespace t1::be;
	TileCoord mapSize = world->getPreSettings().getTerrain().mapSize;
	float coordX, coordY;
	const int side = t1::Rand::getValue(0, 3);
	switch (side)
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

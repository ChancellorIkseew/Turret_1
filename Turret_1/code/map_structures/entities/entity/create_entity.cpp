
#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entities_list/entities_list.h"

#include "map_structures/entities/mob_types/standard_bot.h"
#include "map_structures/entities/mob_types/heavy_bot.h"
#include "map_structures/entities/mob_types/rocket_bot.h"

#include "map_structures/entities/mob_types/cannon_boss_bot.h"
#include "map_structures/entities/mob_types/rocket_boss_bot.h"


void Entity::spawnEntity(const int amount, const int type)
{
	for (int i = 0; i < amount; ++i)
	{
		entitiesList.emplace_back(createEntity(type));
		entitiesList.back()->setCoord(randomMapBorderSpawn());
	}
}


std::unique_ptr<Entity> Entity::createEntity(const int type)
{
	switch (type)
	{
	case STANDARD_BOT:
		return std::make_unique<StandardBot>(STANDARD_BOT);
	case HEAVY_BOT:
		return std::make_unique<HeavyBot>(HEAVY_BOT);
	case ROCKET_BOT:
		return std::make_unique<RocketBot>(ROCKET_BOT);
	case CANNON_BOSS:
		return std::make_unique<CannonBossBot>(CANNON_BOSS);
	case ROCKET_BOSS:
		return std::make_unique<RocketBossBot>(ROCKET_BOSS);
	default:
		return nullptr;
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
		coordY = pixelF(rand() % (mapSizeY - 1));
		break;

	case 1:
		coordX = pixelF(rand() % (mapSizeX - 3) + 1);
		coordY = pixelF(0);
		break;

	case 2:
		coordX = pixelF(mapSizeX - 1);
		coordY = pixelF(rand() % (mapSizeY - 1));
		break;

	case 3:
		coordX = pixelF(rand() % (mapSizeX - 3) + 1);
		coordY = pixelF(mapSizeY - 1);
		break;

	default:
		coordX = pixelF(0);
		coordY = pixelF(0);
		break;
	}
	return { coordX, coordY };
}
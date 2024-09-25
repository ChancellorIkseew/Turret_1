
#include "map_structures/entities/entity.h"
#include "map_structures/entities/mob_enum.h"


#include "map_structures/entities/mob_types/standard_bot.h"
#include "map_structures/entities/mob_types/heavy_bot.h"
#include "map_structures/entities/mob_types/rocket_bot.h"

#include "map_structures/entities/mob_types/cannon_boss_bot.h"
#include "map_structures/entities/mob_types/rocket_boss_bot.h"


Entity* Entity::createEntity(int type)
{
	PixelCoord nullCoord{ 0, 0 };

	switch (type)
	{
	case STANDARD_BOT:
		return new StandardBot(STANDARD_BOT, nullCoord, 0, 0);

	case HEAVY_BOT:
		return new HeavyBot(HEAVY_BOT, nullCoord, 0, 0);

	case ROCKET_BOT:
		return new RocketBot(ROCKET_BOT, nullCoord, 0, 0);

	case CANNON_BOSS:
		return new CannonBossBot(CANNON_BOSS, nullCoord, 0, 0);

	case ROCKET_BOSS:
		return new RocketBossBot(ROCKET_BOSS, nullCoord, 0, 0);
	}
}


[[nodiscard]] PixelCoord Entity::randomMapBorderSpawn()
{
	float coordX, coordY;
	int x = rand() % 4;
	switch (x)
	{
	case 0:
		coordX = pixelF(0);
		coordY = pixelF(rand() % (mapMaxY - 1));
		break;

	case 1:
		coordX = pixelF(rand() % (mapMaxX - 3) + 1);
		coordY = pixelF(0);
		break;

	case 2:
		coordX = pixelF(mapMaxX - 1);
		coordY = pixelF(rand() % (mapMaxY - 1));
		break;

	case 3:
		coordX = pixelF(rand() % (mapMaxX - 3) + 1);
		coordY = pixelF(mapMaxY - 1);
		break;

	default:
		coordX = pixelF(0);
		coordY = pixelF(0);
		break;
	}
	return { coordX, coordY };
}

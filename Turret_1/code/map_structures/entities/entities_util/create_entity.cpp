
#include "../entities.h"
#include "../mob_enum.h"


#include "../mob_types/standard_bot.h"
#include "../mob_types/heavy_bot.h"
#include "../mob_types/rocket_bot.h"

#include "../mob_types/cannon_boss_bot.h"
#include "../mob_types/rocket_boss_bot.h"



Entity* Entity::createEntity(int type)
{
	switch (type)
	{
	case STANDARD_BOT:
		return new StandardBot(STANDARD_BOT, 0, 0, 0, 0);

	case HEAVY_BOT:
		return new HeavyBot(HEAVY_BOT, 0, 0, 0, 0);

	case ROCKET_BOT:
		return new RocketBot(ROCKET_BOT, 0, 0, 0, 0);

	case CANNON_BOSS:
		return new CannonBossBot(CANNON_BOSS, 0, 0, 0, 0);

	case ROCKET_BOSS:
		return new RocketBossBot(ROCKET_BOSS, 0, 0, 0, 0);
	}
}
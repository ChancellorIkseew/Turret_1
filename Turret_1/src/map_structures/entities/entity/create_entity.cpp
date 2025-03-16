
#include "entity.h"
#include "map_structures/entities/entity/mob_enum.h"

#include "map_structures/entities/mob_types/standard_bot.h"
#include "map_structures/entities/mob_types/heavy_bot.h"
#include "map_structures/entities/mob_types/rocket_bot.h"
#include "map_structures/entities/mob_types/laser_bot.h"

#include "map_structures/entities/mob_types/cannon_boss_bot.h"
#include "map_structures/entities/mob_types/rocket_boss_bot.h"

#include "map_structures/entities/mob_types/shuttle.h"


std::unique_ptr<Entity> Entity::createEntity(const MobType type, Team* team)
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


#include "wave_constructor.h"

#include "t1_time.h"

#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entities_list/entities_list.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"


void WaveConstructor::createWave(Team& team, World& world)
{
	if(world.getTime().getTime() % 10800 == 0)
	{
		world.time.setNextWave();
		switchEntities(world.getTime().getWave(), team, world.getBuildingsMap());
		world.time.setTime(0);
	}
}


void WaveConstructor::switchEntities(const int wave, Team& enemy, const BuildingsMap& buildingsMap)
{
	switch(wave)
	{
	case 1:
		enemy.spawnEntity(2, MobType::STANDARD_BOT, buildingsMap);
//#ifdef TURRET_1_MOB_TYPES_TEST
		enemy.spawnEntity(1, MobType::HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(1, MobType::ROCKET_BOT, buildingsMap);
		enemy.spawnEntity(1, MobType::LASER_BOT, buildingsMap);
		enemy.spawnEntity(1, MobType::CANNON_BOSS, buildingsMap);
		enemy.spawnEntity(1, MobType::ROCKET_BOSS, buildingsMap);
		enemy.spawnEntity(1, MobType::UNKNOWN_VALUE, buildingsMap);
//#endif // TURRET_1_MOB_TYPES_TEST
		break;

	case 2:
		enemy.spawnEntity(5, MobType::STANDARD_BOT, buildingsMap);
		break;

	case 3:
		enemy.spawnEntity(5, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(2, MobType::HEAVY_BOT, buildingsMap);
		break;

	case 4:
		enemy.spawnEntity(7, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(3, MobType::HEAVY_BOT, buildingsMap);
		break;

	case 5:
		enemy.spawnEntity(4, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(1, MobType::CANNON_BOSS, buildingsMap);
		break;

	case 6:
		enemy.spawnEntity(5, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(2, MobType::ROCKET_BOT, buildingsMap);
		break;

	case 7:
		enemy.spawnEntity(7, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(4, MobType::HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(2, MobType::ROCKET_BOT, buildingsMap);
		break;

	case 8:
		enemy.spawnEntity(7, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(2, MobType::HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(5, MobType::ROCKET_BOT, buildingsMap);
		break;

	case 9:
		enemy.spawnEntity(11, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(7, MobType::HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(5, MobType::ROCKET_BOT, buildingsMap);
		break;


	case 10:
		enemy.spawnEntity(11, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(5, MobType::HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(2, MobType::ROCKET_BOT, buildingsMap);
		enemy.spawnEntity(2, MobType::CANNON_BOSS, buildingsMap);
		break;
	}
	
	if(wave > 10 && wave < 20)
	{
		enemy.spawnEntity(15, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(9, MobType::HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(7, MobType::ROCKET_BOT, buildingsMap);
		
		if(wave % 5 == 0)
			enemy.spawnEntity(3, MobType::CANNON_BOSS, buildingsMap);
	}
	
	if(wave > 19 && wave < 30)
	{
		enemy.spawnEntity(15, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(9, MobType::HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(7, MobType::ROCKET_BOT, buildingsMap);

		if(wave % 5 == 0)
		{
			enemy.spawnEntity(2, MobType::CANNON_BOSS, buildingsMap);
			enemy.spawnEntity(2, MobType::ROCKET_BOSS, buildingsMap);
		}
	}
	
	if(wave > 29 && wave < 40)
	{
		enemy.spawnEntity(15, MobType::STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(9, MobType::HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(7, MobType::ROCKET_BOT, buildingsMap);
		enemy.spawnEntity(7, MobType::LASER_BOT, buildingsMap);
		
		if(wave % 5 == 0)
		{
			enemy.spawnEntity(2, MobType::CANNON_BOSS, buildingsMap);
			enemy.spawnEntity(2, MobType::ROCKET_BOSS, buildingsMap);
		}	
	}
}

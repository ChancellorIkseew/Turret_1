
#include "wave_constructor.h"

#include "t1_time.h"

#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entities_list/entities_list.h"
#include "map_structures/team/team.h"


void createWave(Team& team, const BuildingsMap& buildingsMap)
{
	if(t1::time::time%10800 == 0)
	{
		t1::time::waveNumber += 1;
		
		switchEntities(t1::time::waveNumber, team, buildingsMap);
		t1::time::time = 0;
	}
}


void switchEntities(const int wave, Team& enemy, const BuildingsMap& buildingsMap)
{
	switch(wave)
	{
	case 1:
		enemy.spawnEntity(2, STANDARD_BOT, buildingsMap);
//#ifdef TURRET_1_MOB_TYPES_TEST
		enemy.spawnEntity(1, HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(1, ROCKET_BOT, buildingsMap);
		enemy.spawnEntity(1, LASER_BOT, buildingsMap);
		enemy.spawnEntity(1, CANNON_BOSS, buildingsMap);
		enemy.spawnEntity(1, ROCKET_BOSS, buildingsMap);
		enemy.spawnEntity(1, 999, buildingsMap);
//#endif // TURRET_1_MOB_TYPES_TEST
		break;

	case 2:
		enemy.spawnEntity(5, STANDARD_BOT, buildingsMap);
		break;

	case 3:
		enemy.spawnEntity(5, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(2, HEAVY_BOT, buildingsMap);
		break;

	case 4:
		enemy.spawnEntity(7, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(3, HEAVY_BOT, buildingsMap);
		break;

	case 5:
		enemy.spawnEntity(4, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(1, CANNON_BOSS, buildingsMap);
		break;

	case 6:
		enemy.spawnEntity(5, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(2, ROCKET_BOT, buildingsMap);
		break;

	case 7:
		enemy.spawnEntity(7, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(4, HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(2, ROCKET_BOT, buildingsMap);
		break;

	case 8:
		enemy.spawnEntity(7, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(2, HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(5, ROCKET_BOT, buildingsMap);
		break;

	case 9:
		enemy.spawnEntity(11, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(7, HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(5, ROCKET_BOT, buildingsMap);
		break;


	case 10:
		enemy.spawnEntity(11, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(5, HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(2, ROCKET_BOT, buildingsMap);
		enemy.spawnEntity(2, CANNON_BOSS, buildingsMap);
		break;
	}
	
	if(wave > 10 && wave < 20)
	{
		enemy.spawnEntity(15, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(9, HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(7, ROCKET_BOT, buildingsMap);
		
		if(wave % 5 == 0)
			enemy.spawnEntity(3, CANNON_BOSS, buildingsMap);
	}
	
	if(wave > 19 && wave < 30)
	{
		enemy.spawnEntity(15, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(9, HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(7, ROCKET_BOT, buildingsMap);

		if(wave % 5 == 0)
		{
			enemy.spawnEntity(2, CANNON_BOSS, buildingsMap);
			enemy.spawnEntity(2, ROCKET_BOSS, buildingsMap);
		}
	}
	
	if(wave > 29 && wave < 40)
	{
		enemy.spawnEntity(15, STANDARD_BOT, buildingsMap);
		enemy.spawnEntity(9, HEAVY_BOT, buildingsMap);
		enemy.spawnEntity(7, ROCKET_BOT, buildingsMap);
		enemy.spawnEntity(7, LASER_BOT, buildingsMap);
		
		if(wave % 5 == 0)
		{
			enemy.spawnEntity(2, CANNON_BOSS, buildingsMap);
			enemy.spawnEntity(2, ROCKET_BOSS, buildingsMap);
		}	
	}
}


#include "wave_constructor.h"

#include "t1_time.h"

#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entities_list/entities_list.h"


void createWave()
{
	if(t1::time::time%10800 == 0)
	{
		t1::time::waveNumber += 1;
		
		switchEntities(t1::time::waveNumber);
		t1::time::time = 0;
	}
}


void switchEntities(const int wave)
{
	switch(wave)
	{
	case 1:
		Entity::spawnEntity(2, STANDARD_BOT);
#ifdef TURRET_1_MOB_TYPES_TEST
		Entity::spawnEntity(1, HEAVY_BOT);
		Entity::spawnEntity(1, ROCKET_BOT);
		Entity::spawnEntity(1, LASER_BOT);
		Entity::spawnEntity(1, CANNON_BOSS);
		Entity::spawnEntity(1, ROCKET_BOSS);
		Entity::spawnEntity(1, 999);
#endif // TURRET_1_MOB_TYPES_TEST
		break;

	case 2:
		Entity::spawnEntity(5, STANDARD_BOT);
		break;

	case 3:
		Entity::spawnEntity(5, STANDARD_BOT);
		Entity::spawnEntity(2, HEAVY_BOT);
		break;

	case 4:
		Entity::spawnEntity(7, STANDARD_BOT);
		Entity::spawnEntity(3, HEAVY_BOT);
		break;

	case 5:
		Entity::spawnEntity(4, STANDARD_BOT);
		Entity::spawnEntity(1, CANNON_BOSS);
		break;

	case 6:
		Entity::spawnEntity(5, STANDARD_BOT);
		Entity::spawnEntity(2, ROCKET_BOT);
		break;

	case 7:
		Entity::spawnEntity(7, STANDARD_BOT);
		Entity::spawnEntity(4, HEAVY_BOT);
		Entity::spawnEntity(2, ROCKET_BOT);
		break;

	case 8:
		Entity::spawnEntity(7, STANDARD_BOT);
		Entity::spawnEntity(2, HEAVY_BOT);
		Entity::spawnEntity(5, ROCKET_BOT);
		break;

	case 9:
		Entity::spawnEntity(11, STANDARD_BOT);
		Entity::spawnEntity(7, HEAVY_BOT);
		Entity::spawnEntity(5, ROCKET_BOT);
		break;


	case 10:
		Entity::spawnEntity(11, STANDARD_BOT);
		Entity::spawnEntity(5, HEAVY_BOT);
		Entity::spawnEntity(2, ROCKET_BOT);
		Entity::spawnEntity(2, CANNON_BOSS);
		break;
	}
	
	if(wave > 10 && wave < 20)
	{
		Entity::spawnEntity(15, STANDARD_BOT);
		Entity::spawnEntity(9, HEAVY_BOT);
		Entity::spawnEntity(7, ROCKET_BOT);
		
		if(wave % 5 == 0)
			Entity::spawnEntity(3, CANNON_BOSS);
	}
	
	if(wave > 19 && wave < 30)
	{
		Entity::spawnEntity(15, STANDARD_BOT);
		Entity::spawnEntity(9, HEAVY_BOT);
		Entity::spawnEntity(7, ROCKET_BOT);

		if(wave % 5 == 0)
		{
			Entity::spawnEntity(2, CANNON_BOSS);
			Entity::spawnEntity(2, ROCKET_BOSS);
		}
	}
	
	if(wave > 29 && wave < 40)
	{
		Entity::spawnEntity(15, STANDARD_BOT);
		Entity::spawnEntity(9, HEAVY_BOT);
		Entity::spawnEntity(7, ROCKET_BOT);
		Entity::spawnEntity(7, LASER_BOT);
		
		if(wave % 5 == 0)
		{
			Entity::spawnEntity(2, CANNON_BOSS);
			Entity::spawnEntity(2, ROCKET_BOSS);
		}	
	}
}

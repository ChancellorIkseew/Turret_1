
#include "wave_constructor.h"

#include "t1_time.h"

#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entities_list/entities_list.h"
#include "map_structures/entities/behavior/path_finding.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"


void WaveConstructor::spawnEnemy(const int amount, const MobType type, Team& enemy, const BuildingsMap& buildingsMap)
{
	for (int i = 0; i < amount; ++i)
	{
		std::unique_ptr<Entity> entity = Entity::createEntity(type, &enemy);
		if (entity == nullptr)
			continue;
		entity->setControlType(Control::NONE);
		PixelCoord coord = Entity::randomMapBorderSpawn();
		entity->setCoord(coord);
		entity->setDestCoord(PathFinding::findClosestCore(t1::be::tile(coord), buildingsMap));
		enemy.getEneities().spawnEntity(std::move(entity));
	}
}


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
		spawnEnemy(2, MobType::STANDARD_BOT, enemy, buildingsMap);
		break;

	case 2:
		spawnEnemy(5, MobType::STANDARD_BOT, enemy, buildingsMap);
		break;

	case 3:
		spawnEnemy(5, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(2, MobType::HEAVY_BOT, enemy, buildingsMap);
		break;

	case 4:
		spawnEnemy(7, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(3, MobType::HEAVY_BOT, enemy, buildingsMap);
		break;

	case 5:
		spawnEnemy(4, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(1, MobType::CANNON_BOSS, enemy, buildingsMap);
		break;

	case 6:
		spawnEnemy(5, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(2, MobType::ROCKET_BOT, enemy, buildingsMap);
		break;

	case 7:
		spawnEnemy(7, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(4, MobType::HEAVY_BOT, enemy, buildingsMap);
		spawnEnemy(2, MobType::ROCKET_BOT, enemy, buildingsMap);
		break;

	case 8:
		spawnEnemy(7, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(2, MobType::HEAVY_BOT, enemy, buildingsMap);
		spawnEnemy(5, MobType::ROCKET_BOT, enemy, buildingsMap);
		break;

	case 9:
		spawnEnemy(11, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(7, MobType::HEAVY_BOT, enemy, buildingsMap);
		spawnEnemy(5, MobType::ROCKET_BOT, enemy, buildingsMap);
		break;


	case 10:
		spawnEnemy(11, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(5, MobType::HEAVY_BOT, enemy, buildingsMap);
		spawnEnemy(2, MobType::ROCKET_BOT, enemy, buildingsMap);
		spawnEnemy(2, MobType::CANNON_BOSS, enemy, buildingsMap);
		break;
	}
	
	if(wave > 10 && wave < 20)
	{
		spawnEnemy(15, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(9, MobType::HEAVY_BOT, enemy, buildingsMap);
		spawnEnemy(7, MobType::ROCKET_BOT, enemy, buildingsMap);
		
		if(wave % 5 == 0)
			spawnEnemy(3, MobType::CANNON_BOSS, enemy, buildingsMap);
	}
	
	if(wave > 19 && wave < 30)
	{
		spawnEnemy(15, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(9, MobType::HEAVY_BOT, enemy, buildingsMap);
		spawnEnemy(7, MobType::ROCKET_BOT, enemy, buildingsMap);

		if(wave % 5 == 0)
		{
			spawnEnemy(2, MobType::CANNON_BOSS, enemy, buildingsMap);
			spawnEnemy(2, MobType::ROCKET_BOSS, enemy, buildingsMap);
		}
	}
	
	if(wave > 29 && wave < 40)
	{
		spawnEnemy(15, MobType::STANDARD_BOT, enemy, buildingsMap);
		spawnEnemy(9, MobType::HEAVY_BOT, enemy, buildingsMap);
		spawnEnemy(7, MobType::ROCKET_BOT, enemy, buildingsMap);
		spawnEnemy(7, MobType::LASER_BOT, enemy, buildingsMap);
		
		if(wave % 5 == 0)
		{
			spawnEnemy(2, MobType::CANNON_BOSS, enemy, buildingsMap);
			spawnEnemy(2, MobType::ROCKET_BOSS, enemy, buildingsMap);
		}	
	}
}


void WaveConstructor::spawnTestWave(Team& enemy, const BuildingsMap& buildingsMap)
{
	spawnEnemy(2, MobType::STANDARD_BOT, enemy, buildingsMap);
	spawnEnemy(1, MobType::HEAVY_BOT, enemy, buildingsMap);
	spawnEnemy(1, MobType::ROCKET_BOT, enemy, buildingsMap);
	spawnEnemy(1, MobType::LASER_BOT, enemy, buildingsMap);
	spawnEnemy(1, MobType::CANNON_BOSS, enemy, buildingsMap);
	spawnEnemy(1, MobType::ROCKET_BOSS, enemy, buildingsMap);
	spawnEnemy(1, MobType::UNKNOWN_VALUE, enemy, buildingsMap);
}

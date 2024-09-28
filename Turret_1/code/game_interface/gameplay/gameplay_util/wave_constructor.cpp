
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>

#include "wave_constructor.h"

#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entities_list/entities_list.h"


int waveNumber = 0;


void createWave(int &time)
{
	if(time%10800 == 0)
	{
		waveNumber = waveNumber + 1;
		
		switchEntities(waveNumber);
		time = 0;
	}
}


void switchEntities(const int waveNumber)
{
	switch(waveNumber)
	{
	case 1:
		Entity::spawnEntity(2, STANDARD_BOT);
#ifdef TURRET_1_MOB_TYPES_TEST
		Entity::spawnEntityHeavyBot(HEAVY_BOT);
		Entity::spawnEntityRocketBot(ROCKET_BOT);
		Entity::spawnEntityLaserBot(LASER_BOT);
		Entity::spawnEntityCannonBossBot(CANNON_BOSS);
		Entity::spawnEntityRocketBossBot(ROCKET_BOSS);
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
	
	if(waveNumber > 10 && waveNumber < 20)
	{
		Entity::spawnEntity(15, STANDARD_BOT);
		Entity::spawnEntity(9, HEAVY_BOT);
		Entity::spawnEntity(7, ROCKET_BOT);
		
		if(waveNumber%5 == 0)
			Entity::spawnEntity(3, CANNON_BOSS);
	}
	
	if(waveNumber > 19 && waveNumber < 30)
	{
		Entity::spawnEntity(15, STANDARD_BOT);
		Entity::spawnEntity(9, HEAVY_BOT);
		Entity::spawnEntity(7, ROCKET_BOT);

		if(waveNumber%5 == 0)
		{
			Entity::spawnEntity(2, CANNON_BOSS);
			Entity::spawnEntity(2, ROCKET_BOSS);
		}
	}
	
	if(waveNumber > 29 && waveNumber < 40)
	{
		Entity::spawnEntity(15, STANDARD_BOT);
		Entity::spawnEntity(9, HEAVY_BOT);
		Entity::spawnEntity(7, ROCKET_BOT);
		Entity::spawnEntity(7, LASER_BOT);
		
		if(waveNumber%5 == 0)
		{
			Entity::spawnEntity(2, CANNON_BOSS);
			Entity::spawnEntity(2, ROCKET_BOSS);
		}	
	}
}


int loadTime(std::string saveFolderName)
{
	std::string saveFileName = "saves/" + saveFolderName + "/time.txt";

	std::ifstream fin;
	fin.open(saveFileName);
	int time = 0;
	if(fin.is_open())
	{
		fin >> waveNumber >> time;
	}
	fin.close();
	
	std::cout << "Load time and wave_num works" <<'\n';
	return time;
}


void saveTime(std::string saveFolderName, const int v_time)
{
	std::string saveFileName = "saves/" + saveFolderName + "/time.txt";

	std::ofstream fout;
	fout.open(saveFileName);
	fout << waveNumber << " " << v_time;
	fout.close();
	
	std::cout << "Save time and wave_num works" <<'\n';
}

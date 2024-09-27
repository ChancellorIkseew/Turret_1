
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



void switchEntities(int waveNumber)
{
	
	switch(waveNumber)
	{
		case 1:
			{
			Entity::spawnEntity(STANDARD_BOT);
			Entity::spawnEntity(STANDARD_BOT);
#ifdef TURRET_1_MOB_TYPES_TEST
			Entity::spawnEntityHeavyBot(HEAVY_BOT);
			Entity::spawnEntityRocketBot(ROCKET_BOT);
			Entity::spawnEntityLaserBot(LASER_BOT);
			Entity::spawnEntityCannonBossBot(CANNON_BOSS);
			Entity::spawnEntityRocketBossBot(ROCKET_BOSS);
#endif // TURRET_1_MOB_TYPES_TEST
				break;
			}
			
		case 2:
			{
				for(int i=0; i<5; i++)
				{
					Entity::spawnEntity(STANDARD_BOT);
				}
				break;
			}
			
		case 3:
			{
				for(int i=0; i<5; i++)
				{
					Entity::spawnEntity(STANDARD_BOT);
				}
				Entity::spawnEntity(HEAVY_BOT);
				Entity::spawnEntity(HEAVY_BOT);
				break;
			}
			
		case 4:
			{
				for(int i=0; i<7; i++)
				{
					Entity::spawnEntity(STANDARD_BOT);
				}
				for(int i=0; i<3; i++)
				{
					Entity::spawnEntity(HEAVY_BOT);
				}
				break;
			}
			
		case 5:
			{
				for(int i=0; i<4; i++)
				{
					Entity::spawnEntity(STANDARD_BOT);
				}
				Entity::spawnEntity(CANNON_BOSS);
				break;
			}
			
		case 6:
			{
				for(int i=0; i<5; i++)
				{
					Entity::spawnEntity(STANDARD_BOT);
				}
				Entity::spawnEntity(ROCKET_BOT);
				Entity::spawnEntity(ROCKET_BOT);
				break;
			}
			
		case 7:
			{
				for(int i=0; i<7; i++)
				{
					Entity::spawnEntity(STANDARD_BOT);
				}
				for(int i=0; i<4; i++)
				{
					Entity::spawnEntity(HEAVY_BOT);
				}
				Entity::spawnEntity(ROCKET_BOT);
				Entity::spawnEntity(ROCKET_BOT);
				break;
			}
			
		case 8:
			{
				for(int i=0; i<7; i++)
				{
					Entity::spawnEntity(STANDARD_BOT);
				}
				Entity::spawnEntity(HEAVY_BOT);
				Entity::spawnEntity(HEAVY_BOT);
				for(int i=0; i<5; i++)
				{
					Entity::spawnEntity(ROCKET_BOT);
				}
				break;
			}
			
		case 9:
			{
				for(int i=0; i<11; i++)
				{
					Entity::spawnEntity(STANDARD_BOT);
				}
				for(int i=0; i<7; i++)
				{
					Entity::spawnEntity(HEAVY_BOT);
				}
				for(int i=0; i<5; i++)
				{
					Entity::spawnEntity(ROCKET_BOT);
				}
				break;
			}
		
		case 10:
			{
				for(int i=0; i<11; i++)
				{
					Entity::spawnEntity(STANDARD_BOT);
				}
				for(int i=0; i<5; i++)
				{
					Entity::spawnEntity(HEAVY_BOT);
				}
				for(int i=0; i<2; i++)
				{
					Entity::spawnEntity(ROCKET_BOT);
					Entity::spawnEntity(ROCKET_BOT);
				}
				break;
			}
			
			
			
	}
	
	if(waveNumber > 10 && waveNumber < 20)
	{
		for(int i=0; i<15; i++)
		{
			Entity::spawnEntity(STANDARD_BOT);
		}
		for(int i=0; i<9; i++)
		{
			Entity::spawnEntity(HEAVY_BOT);
		}
		for(int i=0; i<7; i++)
		{
			Entity::spawnEntity(ROCKET_BOT);
		}
		
		if(waveNumber%5 == 0)
		{
			for(int i=0; i<3; i++)
			{
				Entity::spawnEntity(CANNON_BOSS);
			}
		}
		
	}
	
	
	if(waveNumber > 19 && waveNumber < 30)
	{
		for(int i=0; i<15; i++)
		{
			Entity::spawnEntity(STANDARD_BOT);
		}
		for(int i=0; i<9; i++)
		{
			Entity::spawnEntity(HEAVY_BOT);
		}
		for(int i=0; i<7; i++)
		{
			Entity::spawnEntity(ROCKET_BOT);
		}
		
		if(waveNumber%5 == 0)
		{
			for(int i=0; i<2; i++)
			{
				Entity::spawnEntity(CANNON_BOSS);
				Entity::spawnEntity(ROCKET_BOSS);
			}
		}
		
	}
	
	if(waveNumber > 29 && waveNumber < 40)
	{
		for(int i=0; i<15; i++)
		{
			Entity::spawnEntity(STANDARD_BOT);
		}
		for(int i=0; i<9; i++)
		{
			Entity::spawnEntity(HEAVY_BOT);
		}
		for(int i=0; i<7; i++)
		{
			Entity::spawnEntity(ROCKET_BOT);
			Entity::spawnEntity(LASER_BOT);
		}
		
		if(waveNumber%5 == 0)
		{
			for(int i=0; i<2; i++)
			{
				Entity::spawnEntity(CANNON_BOSS);
				Entity::spawnEntity(ROCKET_BOSS);
			}
		}
		
	}
	
}



int loadTime(std::string saveFolderName)
{
	std::string saveFileName = "saves/" + saveFolderName + "/time.txt";

	std::ifstream fin;
	fin.open(saveFileName);
	
	int t = 0;
	
	if(fin.is_open())
	{
		for(int i=0; i<3; i++)
		{
			char c;
			fin.get(c);
			int num = 0;
			num = c - '0';
			waveNumber = waveNumber * 10 + num;
		}
		
		for(int i=0; i<5; i++)
		{
			char c;
			fin.get(c);
			int num = 0;
			num = c - '0';
			t = t * 10 + num;
		}
	}
	
	fin.close();
	
	std::cout << "Load time and wave_num works" <<'\n';
	
	return t;
}



void saveTime(std::string saveFolderName, int v_time)
{
	std::string saveFileName = "saves/" + saveFolderName + "/time.txt";

	std::ofstream fout;
	fout.open(saveFileName);
	
	if(fout.is_open())
	{
		
		if(waveNumber < 10)
		{
			fout << "00" << waveNumber;
		}
		else
		{
			if(waveNumber < 100)
			{
				fout << "0" << waveNumber;
			}
			else
			{
				fout << waveNumber;
			}
		}
		
		
		
		if(v_time < 10)
		{
			fout << "0000" << v_time;
		}
		else
		{
			if(v_time < 100)
			{
				fout << "000" << v_time;
			}
			else
			{
				if(v_time < 1000)
				{
					fout << "00" << v_time;
				}
				else
				{
					if(v_time < 10000)
					{
						fout << "0" << v_time;
					}
					else
					{
						fout << v_time;
					}
				}
			}
		}
		
	}
	
	fout.close();
	
	std::cout << "Save time and wave_num works" <<'\n';
}






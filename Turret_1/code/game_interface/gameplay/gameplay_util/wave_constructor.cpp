
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>

#include "wave_constructor.h"

#include "map_structures/entities/entity.h"
#include "map_structures/entities/mob_enum.h"
#include "map_structures/entities/entities_util/entities_list.h"

// mobs
#include "map_structures/entities/mob_types/standard_bot.h"
#include "map_structures/entities/mob_types/heavy_bot.h"
#include "map_structures/entities/mob_types/rocket_bot.h"
#include "map_structures/entities/mob_types/laser_bot.h"
// boss_mobs
#include "map_structures/entities/mob_types/cannon_boss_bot.h"
#include "map_structures/entities/mob_types/rocket_boss_bot.h"





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
			entitiesList.push_back(new StandardBot(STANDARD_BOT));
			entitiesList.push_back(new StandardBot(STANDARD_BOT));
#ifdef TURRET_1_MOB_TYPES_TEST
			entitiesList.push_back(new HeavyBot(HEAVY_BOT));
			entitiesList.push_back(new RocketBot(ROCKET_BOT));
			entitiesList.push_back(new LaserBot(LASER_BOT));
			entitiesList.push_back(new CannonBossBot(CANNON_BOSS));
			entitiesList.push_back(new RocketBossBot(ROCKET_BOSS));
#endif // TURRET_1_MOB_TYPES_TEST
				break;
			}
			
		case 2:
			{
				for(int i=0; i<5; i++)
				{
					entitiesList.push_back(new StandardBot(STANDARD_BOT));
				}
				break;
			}
			
		case 3:
			{
				for(int i=0; i<5; i++)
				{
					entitiesList.push_back(new StandardBot(STANDARD_BOT));
				}
				entitiesList.push_back(new HeavyBot(HEAVY_BOT));
				entitiesList.push_back(new HeavyBot(HEAVY_BOT));
				break;
			}
			
		case 4:
			{
				for(int i=0; i<7; i++)
				{
					entitiesList.push_back(new StandardBot(STANDARD_BOT));
				}
				for(int i=0; i<3; i++)
				{
					entitiesList.push_back(new HeavyBot(HEAVY_BOT));
				}
				break;
			}
			
		case 5:
			{
				for(int i=0; i<4; i++)
				{
					entitiesList.push_back(new StandardBot(STANDARD_BOT));
				}
				entitiesList.push_back(new CannonBossBot(CANNON_BOSS));
				break;
			}
			
		case 6:
			{
				for(int i=0; i<5; i++)
				{
					entitiesList.push_back(new StandardBot(STANDARD_BOT));
				}
				entitiesList.push_back(new RocketBot(ROCKET_BOT));
				entitiesList.push_back(new RocketBot(ROCKET_BOT));
				break;
			}
			
		case 7:
			{
				for(int i=0; i<7; i++)
				{
					entitiesList.push_back(new StandardBot(STANDARD_BOT));
				}
				for(int i=0; i<4; i++)
				{
					entitiesList.push_back(new HeavyBot(HEAVY_BOT));
				}
				entitiesList.push_back(new RocketBot(ROCKET_BOT));
				entitiesList.push_back(new RocketBot(ROCKET_BOT));
				break;
			}
			
		case 8:
			{
				for(int i=0; i<7; i++)
				{
					entitiesList.push_back(new StandardBot(STANDARD_BOT));
				}
				entitiesList.push_back(new HeavyBot(HEAVY_BOT));
				entitiesList.push_back(new HeavyBot(HEAVY_BOT));
				for(int i=0; i<5; i++)
				{
					entitiesList.push_back(new RocketBot(ROCKET_BOT));
				}
				break;
			}
			
		case 9:
			{
				for(int i=0; i<11; i++)
				{
					entitiesList.push_back(new StandardBot(STANDARD_BOT));
				}
				for(int i=0; i<7; i++)
				{
					entitiesList.push_back(new HeavyBot(HEAVY_BOT));
				}
				for(int i=0; i<5; i++)
				{
					entitiesList.push_back(new RocketBot(ROCKET_BOT));
				}
				break;
			}
		
		case 10:
			{
				for(int i=0; i<11; i++)
				{
					entitiesList.push_back(new StandardBot(STANDARD_BOT));
				}
				for(int i=0; i<5; i++)
				{
					entitiesList.push_back(new HeavyBot(HEAVY_BOT));
				}
				for(int i=0; i<2; i++)
				{
					entitiesList.push_back(new RocketBot(ROCKET_BOT));
					entitiesList.push_back(new CannonBossBot(ROCKET_BOT));
				}
				break;
			}
			
			
			
	}
	
	if(waveNumber > 10 && waveNumber < 20)
	{
		for(int i=0; i<15; i++)
		{
			entitiesList.push_back(new StandardBot(STANDARD_BOT));
		}
		for(int i=0; i<9; i++)
		{
			entitiesList.push_back(new HeavyBot(HEAVY_BOT));
		}
		for(int i=0; i<7; i++)
		{
			entitiesList.push_back(new RocketBot(ROCKET_BOT));
		}
		
		if(waveNumber%5 == 0)
		{
			for(int i=0; i<3; i++)
			{
				entitiesList.push_back(new CannonBossBot(CANNON_BOSS));
			}
		}
		
	}
	
	
	if(waveNumber > 19 && waveNumber < 30)
	{
		for(int i=0; i<15; i++)
		{
			entitiesList.push_back(new StandardBot(STANDARD_BOT));
		}
		for(int i=0; i<9; i++)
		{
			entitiesList.push_back(new HeavyBot(HEAVY_BOT));
		}
		for(int i=0; i<7; i++)
		{
			entitiesList.push_back(new RocketBot(ROCKET_BOT));
		}
		
		if(waveNumber%5 == 0)
		{
			for(int i=0; i<2; i++)
			{
				entitiesList.push_back(new CannonBossBot(CANNON_BOSS));
				entitiesList.push_back(new RocketBossBot(ROCKET_BOSS));
			}
		}
		
	}
	
	if(waveNumber > 29 && waveNumber < 40)
	{
		for(int i=0; i<15; i++)
		{
			entitiesList.push_back(new StandardBot(STANDARD_BOT));
		}
		for(int i=0; i<9; i++)
		{
			entitiesList.push_back(new HeavyBot(HEAVY_BOT));
		}
		for(int i=0; i<7; i++)
		{
			entitiesList.push_back(new RocketBot(ROCKET_BOT));
			//entitiesList.push_back(new Entity('4'));
		}
		
		if(waveNumber%5 == 0)
		{
			for(int i=0; i<2; i++)
			{
				entitiesList.push_back(new CannonBossBot(CANNON_BOSS));
				entitiesList.push_back(new RocketBossBot(ROCKET_BOSS));
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






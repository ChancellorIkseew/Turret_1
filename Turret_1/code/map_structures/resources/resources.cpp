
#include <iostream>
#include <fstream>
#include <string>


#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map.h"

#include "resources.h"
#include "res_enum.h"


int t1::res::stoneQuantity = 0;
int t1::res::ironQuantity = 0;
int t1::res::copperQuantity = 0;
int t1::res::siliconQuantity = 0;
int t1::res::coalQuantity = 0;
int t1::res::oilQuantity = 0;
int t1::res::sulfurQuantity = 0;

int t1::res::newEnergy = 0;
int t1::res::oldEnergy = 0;

void t1::res::giveStartResources()
{
	stoneQuantity = 1000;
	ironQuantity = 1000;
	copperQuantity = 1000;
	siliconQuantity = 1000;
	coalQuantity = 1000;
	oilQuantity = 1000;
	sulfurQuantity = 1000;
}



void t1::res::useEnergy(int time)
{
	if(time%60 == 0)
	{
		std::cout << "all_energy: " << newEnergy << '\n';
		std::cout << "avaliable_energy: " << oldEnergy << '\n';
		
		oldEnergy = newEnergy;
		newEnergy = 200;
	}
}



void t1::res::loadResources(std::string saveFolderName)
{
	std::string saveFileName = "saves/" + saveFolderName + "/resources.txt";
	
	std::ifstream fin;
	fin.open(saveFileName);
	
	if(fin.is_open())
	{
		fin >> stoneQuantity >> ironQuantity >> copperQuantity >> siliconQuantity >> coalQuantity >> sulfurQuantity;
		
	}
	fin.close();
}



void t1::res::saveResources(std::string saveFolderName)
{
	std::string saveFileName = "saves/" + saveFolderName + "/resources.txt";
	
	std::ofstream fout;
	fout.open(saveFileName);
	
	if(fout.is_open())
	{
		
		for(int i=0; i<7; i++)
		{
			int x = 0;
			switch(i)
			{
				case 0:
				{
					x = stoneQuantity;
					break;
				}
				
				case 1:
				{
					x = ironQuantity;
					break;
				}
				
				case 2:
				{
					x = copperQuantity;
					break;
				}
				
				case 3:
				{
					x = siliconQuantity;
					break;
				}
				
				case 4:
				{
					x = coalQuantity;
					break;
				}
				
				case 5:
				{
					x = sulfurQuantity;
					break;
				}
				
			}
			
			
			if(x < 10)
			{
				fout << "00000" << x << " ";
			}
			else
			{
				if(x < 100)
				{
					fout << "0000" << x << " ";
				}
				else
				{
					if(x < 1000)
					{
						fout << "000" << x << " ";
					}
					else
					{
						if(x < 10000)
						{
							fout << "00" << x << " ";
						}
						else
						{
							if(x < 100000)
							{
								fout << "0" << x << " ";
							}
						}
					}
				}
			}
			
		}
		
	}
	fout.close();
	
	std::cout << "save resources works" << '\n';
	
		
}



void t1::res::sendToBalance(int type, short amount)
{


	switch (type)
	{

	case RES_STONE:
		if (stoneQuantity < 1000000)
			stoneQuantity = stoneQuantity + amount;

		if (stoneQuantity >= 1000000)
			stoneQuantity = 999999;
		break;

	case RES_IRON:
		if (ironQuantity < 1000000)
			ironQuantity = ironQuantity + amount;

		if (ironQuantity >= 1000000)
			ironQuantity = 999999;
		break;

	case RES_COPPER:
		if (copperQuantity < 1000000)
			copperQuantity = copperQuantity + amount;

		if (copperQuantity >= 1000000)
			copperQuantity = 999999;
		break;

	case RES_SILICON:
		if (siliconQuantity < 1000000)
			siliconQuantity = siliconQuantity + amount;

		if (siliconQuantity >= 1000000)
			siliconQuantity = 999999;
		break;

	case RES_COAL:
		if (coalQuantity < 1000000)
			coalQuantity = coalQuantity + amount;

		if (coalQuantity >= 1000000)
			coalQuantity = 999999;
		break;

	case RES_SULFUR:
		if (sulfurQuantity < 1000000)
			sulfurQuantity = sulfurQuantity + amount;

		if (sulfurQuantity >= 1000000)
			sulfurQuantity = 999999;
		break;

	/*
	case RES_AC_SHELLS:
	{
		if (sulfurQuantity < 1000000)
			sulfurQuantity = sulfurQuantity + amount;

		if (sulfurQuantity >= 1000000)
			sulfurQuantity = 999999;
		break;
	}
	*/
	}

}


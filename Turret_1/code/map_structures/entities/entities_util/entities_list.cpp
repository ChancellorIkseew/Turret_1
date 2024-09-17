
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>


#include "entities_list.h"

#include "../entities.h"
#include "../mob_types/standard_bot.h"
#include "../mob_types/rocket_bot.h"
#include "../mob_types/cannon_boss_bot.h"


std::list<Entity*> entitiesList;


void printEntitiesList()
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		
		std::cout << "<T" << (*it)->getEntityType() << ">" << '\n';									//Type
		std::cout << "<X" << (*it)->getCoordX() << "> <Y" << (*it)->getCoordY() << ">" << '\n';		//Coords
		std::cout << "<A" << (*it)->getAngleDeg() << ">" << '\n';									//Angle in Deg.
		std::cout << "<D" << (*it)->getDurability() << ">" << '\n';									//Durability											
		std::cout << "$" << '\n'<< '\n';
	}
}



void loadEntitiesList(std::string saveFolderName)
{
	std::string saveFileName = "saves/" + saveFolderName + "/entities.txt";

	std::ifstream fin;
	fin.open(saveFileName);
	
	char nextSymbol = '&';

	if(fin.is_open())
	{
		while (true)
		{
			fin >> nextSymbol;
			if (nextSymbol != '&')
			{
				fin.seekg(-1, std::ios::cur);

				int entityType;
				fin >> entityType;

				Entity* entity = Entity::createEntity(entityType);
				entity->load(fin);
				entitiesList.push_back(entity);
			}
			else
			{
				break;
			}
		}
	}
	fin.close();
	
	std::cout << "Load entities list works" <<'\n';
}



void saveEntitiesList(std::string saveFolderName)
{
	std::string saveFileName = "saves/" + saveFolderName + "/entities.txt";

	std::ofstream fout;
	fout.open(saveFileName);
	
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		(*it)->save(fout);
	}
	fout << '&';
	fout.close();
	
	std::cout << "Save entities list works" <<'\n';
}



void moveEntitiesList(BuildingsMap& buildingsMap1, int time)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end();)
	{
		(*it)->motion(buildingsMap1, time, 0.1f);

		(*it)->shooting(buildingsMap1, time);

		if ((*it)->getDurability() < 1)
		{
			delete* it;
			it = entitiesList.erase(it);
		}
		else
		{
			++it;
		}
	}
}



void drawEntitiesList(sf::RenderWindow& mainWindow)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)	//Draw_entities
	{
		(*it)->draw(mainWindow);
	}
}



void cleanEntitiesList()
{
	entitiesList.clear();
}

#include <iostream>
#include <string>


#include "entities_list.h"

#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/mob_types/standard_bot.h"
#include "map_structures/entities/mob_types/rocket_bot.h"
#include "map_structures/entities/mob_types/cannon_boss_bot.h"


std::list<std::unique_ptr<Entity>> entitiesList;


void loadEntitiesList(std::string saveFolderName)
{
	std::string saveFileName = "saves/" + saveFolderName + "/entities.txt";

	std::ifstream fin;
	fin.open(saveFileName);
	if(fin.is_open())
	{
		while (true)
		{
			char nextSymbol;
			fin >> nextSymbol;

			if (nextSymbol == '&')
				break;

			fin.seekg(-1, std::ios::cur);
			int entityType;
			fin >> entityType;
			entitiesList.push_back(Entity::createEntity(entityType));
			entitiesList.back()->load(fin);
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
	for (auto it = entitiesList.cbegin(); it != entitiesList.cend(); ++it)
	{
		(*it)->save(fout);
	}
	fout << '&';
	fout.close();
	
	std::cout << "Save entities list works" <<'\n';
}



void moveEntitiesList()
{
	for (auto it = entitiesList.begin(); it != entitiesList.end();)
	{
		(*it)->motion();
		(*it)->shoot();

		if ((*it)->getDurability() < 1)
		{
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
	for (auto it = entitiesList.begin(); it != entitiesList.end(); ++it)	//Draw_entities
	{
		(*it)->draw(mainWindow);
	}
}


void cleanEntitiesList() noexcept
{
	entitiesList.clear();
}

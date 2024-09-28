
#include <iostream>
#include <string>

#include "entities_list.h"

#include "map_structures/entities/entity/entity.h"


std::list<std::unique_ptr<Entity>> entitiesList;


void saveEntitiesList(const std::string& folder)
{
	std::string file = "saves/" + folder + "/entities.txt";

	std::ofstream fout;
	fout.open(file);
	if (fout.is_open())
	{
		for (auto it = entitiesList.cbegin(); it != entitiesList.cend(); ++it)
		{
			(*it)->save(fout);
		}
	}
	fout << '&';
	fout.close();
	std::cout << "Save entities list works" << '\n';
}

void loadEntitiesList(const std::string& folder)
{
	std::string file = "saves/" + folder + "/entities.txt";
	std::ifstream fin;
	fin.open(file);
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


void moveEntitiesList()
{
	for (auto it = entitiesList.begin(); it != entitiesList.end();)
	{
		(*it)->motion();
		(*it)->shoot();

		if ((*it)->getDurability() < 1)
			it = entitiesList.erase(it);
		else
			++it;
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

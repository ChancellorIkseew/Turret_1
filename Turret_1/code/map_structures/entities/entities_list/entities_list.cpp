
#include <iostream>

#include "entities_list.h"

#include "map_structures/entities/entity/entity.h"


EntitiesList::EntitiesList()
{

}


void EntitiesList::save(const std::string& folder)
{
	/*
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
	*/
}

void EntitiesList::load(const std::string& folder)
{
	/*
	std::string file = "saves/" + folder + "/entities.txt";
	std::ifstream fin;
	fin.open(file);
	if (fin.is_open())
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
	std::cout << "Load entities list works" << '\n';
	*/
}



void EntitiesList::spawnEntity(const int amount, const int type, Team* team)
{
	for (int i = 0; i < amount; ++i)
	{
		try
		{
			entitiesList.emplace_back(Entity::createEntity(type, team));
			entitiesList.back()->setCoord(Entity::randomMapBorderSpawn());
		}
		catch (std::exception)
		{
			std::cout << "mob_type does not exist. type: " << type << '\n';
		}
	}
}


void EntitiesList::interact()
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


void EntitiesList::draw(sf::RenderWindow& mainWindow)
{
	for (auto it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		(*it)->draw(mainWindow);
	}
}

std::list<std::unique_ptr<Entity>>::iterator EntitiesList::begin() noexcept
{
	return entitiesList.begin();
}

std::list<std::unique_ptr<Entity>>::iterator EntitiesList::end() noexcept
{
	return entitiesList.end();
}

void EntitiesList::clean() noexcept
{
	entitiesList.clear();
}


#include <iostream>

#include "entities_list.h"

#include "map_structures/entities/entity/entity.h"


EntitiesList::EntitiesList()
{

}


void EntitiesList::save(const std::string& folder)
{
	
}

void EntitiesList::load(const std::string& folder)
{
	
}



void EntitiesList::spawnEntity(const uint8_t amount, const uint16_t type, Team* team, const BuildingsMap& buildingsMap)
{
	for (int i = 0; i < amount; ++i)
	{
		try
		{
			entitiesList.emplace_back(Entity::createEntity(type, team));
			entitiesList.back()->setCoord(Entity::randomMapBorderSpawn());
			entitiesList.back()->setDestCoord(t1::be::pixel(t1::ent::findClosestCore(*entitiesList.back(), buildingsMap)));
		}
		catch (std::exception)
		{
			std::cout << "mob_type does not exist. type: " << type << '\n';
		}
	}
}


void EntitiesList::interact(const BuildingsMap& buildingsMap)
{
	for (auto it = entitiesList.begin(); it != entitiesList.end();)
	{
		(*it)->motion(buildingsMap);
		(*it)->shoot(buildingsMap);

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

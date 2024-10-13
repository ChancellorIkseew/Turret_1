#pragma once
#ifndef ENTITIES_LIST_H
#define ENTITIES_LIST_H

#include <string>
#include <list>
#include <SFML/Graphics.hpp>

#include "map_structures/entities/entity/entity.h"


class EntitiesList
{
private:
	std::list<std::unique_ptr<Entity>> entitiesList;

public:
	EntitiesList();
	~EntitiesList() = default;
	
	void save(const std::string& folder);
	void load(const std::string& folder);

	void spawnEntity(const int amount, const int type, Team* team);
	void clean() noexcept;

	void interact();
	void draw(sf::RenderWindow& mainWindow);
	
};

#endif // ENTITIES_LIST_H

#pragma once
#ifndef ENTITIES_LIST_H
#define ENTITIES_LIST_H

#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "map_structures/entities/entity/entity.h"


class EntitiesList
{
private:
	std::list<std::unique_ptr<Entity>> entitiesList;

public:
	EntitiesList() = default;
	~EntitiesList() = default;
	
	void save(const std::string& folder);
	void load(const std::string& folder);

	void spawnEntity(const int amount, const int type);
	void clean() noexcept;

	void move();
	void draw(sf::RenderWindow& mainWindow);
	
};

#endif // ENTITIES_LIST_H

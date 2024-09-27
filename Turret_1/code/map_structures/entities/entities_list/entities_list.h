#pragma once
#ifndef ENTITIES_LIST_H
#define ENTITIES_LIST_H

#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "map_structures/entities/entity/entity.h"


extern std::list<std::unique_ptr<Entity>> entitiesList;

void loadEntitiesList(std::string saveFolderName);
void saveEntitiesList(std::string saveFolderName);

void moveEntitiesList();

void drawEntitiesList(sf::RenderWindow& mainWindow);

void cleanEntitiesList() noexcept;

#endif // ENTITIES_LIST_H

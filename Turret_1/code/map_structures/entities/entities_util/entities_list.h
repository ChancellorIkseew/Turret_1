#pragma once

#ifndef ENTITIES_LIST_H
#define ENTITIES_LIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "../entities.h"

extern std::list<Entity*> entitiesList;

void printEntitiesList();

void loadEntitiesList(std::string saveFolderName);

void saveEntitiesList(std::string saveFolderName);

void moveEntitiesList(BuildingsMap& buildingsMap1, int time);

void drawEntitiesList(sf::RenderWindow& mainWindow);

void cleanEntitiesList();



#endif // ENTITIES_LIST_H
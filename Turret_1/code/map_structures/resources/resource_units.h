#pragma once
#ifndef RESOURCE_UNITS_H
#define RESOURCE_UNITS_H

#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>


struct ResPosition
{
	int tileX, tileY;
	int position;
};

class ResourceUnit
{
private:

	static inline int mapMaxX, mapMaxY;
	
	int resType;

	char motionDirection;
	ResPosition position;
	bool isMotionAvailable;
	
	int currentTile;
	
	float coordX;
	float coordY;
	
	bool isWasted;
	
	static inline sf::Image resourcesImage;
	static inline sf::Texture resourcesTexture;
	static inline sf::Sprite resourceSprite;
		
public:
	
	ResourceUnit(int v_type, int v_CoordX, int v_CoordY, char motionDirection);
	ResourceUnit();
	~ResourceUnit() = default;

	void save(std::ofstream& fout);
	void load(std::ifstream& fin);

	void interact(int time);
	void moveResourceUnit();
	bool changePosition();
	ResPosition getNextPosition();
	
	int getType();
	bool getIsWasted();
	
	static void prepareSprites();
	void draw(sf::RenderWindow& window);
	
};


extern std::list<ResourceUnit*> resourceUnitsList;

void moveResUnitsList(int time);

void drawResUnitsList(sf::RenderWindow &window);

void saveResUnitsList(std::string saveFolderName);
void loadResUnitsList(std::string saveFolderName);

void cleanResUnitsList();


#endif // RESOURCE_UNITS_H

#pragma once
#ifndef ENTITIES_H
#define ENTITIES_H

#include <fstream>
#include <SFML\Graphics.hpp>

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/base_engine/tile_coord.h"


class Entity
{

protected:

	static inline int mapMaxX, mapMaxY;
	static inline float enemyMobMaxDurabilityModifier;
	static int enemyMobsQuantity;
		
	int type;
	
	float angleRad;
	float angleDeg;
	
	float coordX;
	float coordY;

	int newTileCoordX;
	int newTileCoordY;

	int oldTileCoordX;
	int oldTileCoordY;
	
	bool isAimDetected;
	
	float shootingAngleRad;
	float shootingAngleDeg;
	
	float aimCoordX;
	float aimCoordY;

	float destCoordX; // destination_point
	float destCoordY;

	int durability;
	int range;
	int spyralRange;
	int reload;
	float maxSpeed;

	static inline sf::Image entityImage;
	static inline sf::Texture entityTexture;
	static inline sf::Sprite entitySprite;

	static inline sf::Image shieldImage;
	static inline sf::Texture shieldTexture;
	static inline sf::Sprite shieldSprite;

	virtual void initCombatData();

	public:

		static void initPreSettings();
		static int getEnemyMobsQuantity();
		
		Entity(int type ,float coordX, float coordY, float curentAngleDeg, short curentDurability);
		Entity(int type);
		virtual ~Entity();

		void save(std::ofstream& fout);
		void load(std::ifstream& fin);
		static Entity* createEntity(int type);

		// combat
		virtual void motion(BuildingsMap &buildingsMap1, int time);
		virtual void findPath(BuildingsMap& buildingsMap1) = 0;
		virtual void shooting(BuildingsMap &buildingsMap1, int time) = 0;
		virtual TileCoord findShootingAim(BuildingsMap& buildingsMap1) = 0;

		// simple_utilites
		void setDurability(int durability);
		void setDamage(int damage);
		char getType();
		int getCoordX();
		int getCoordY();
		int getAngleDeg(); 
		int getDurability();

		// visual
		static void prepareSprites();
		virtual void draw(sf::RenderWindow& window) = 0;
		
};

#endif // ENTITIES_H

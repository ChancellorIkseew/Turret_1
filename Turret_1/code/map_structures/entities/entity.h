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
	
	PixelCoord coord;
	PixelCoord aimCoord;
	PixelCoord destCoord; // destination_point

	TileCoord newTile, oldTile;
	
	bool isAimDetected;
	
	float motionAngleRad;
	float motionAngleDeg;

	float shootingAngleRad;
	float shootingAngleDeg;

	int durability;
	int range;
	int spyralRange;
	int reload;
	int reloadTimer;
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
		
		Entity(int type, PixelCoord coord, float curentAngleDeg, short curentDurability);
		Entity(int type);
		virtual ~Entity();

		void save(std::ofstream& fout) const;
		void load(std::ifstream& fin);
		static Entity* createEntity(int type);
		static [[nodiscard]] PixelCoord randomMapBorderSpawn();

		// combat
		virtual void motion();
		virtual PixelCoord findDestinationCoord() const;
		virtual void shoot() = 0;
		virtual PixelCoord findShootingAim() const;
		void detectAim();
		void reloadWeapon();

		// simple_utilites
		void setDurability(int durability);
		void setDamage(int damage);
		char getType() const;
		PixelCoord getCoord() const;
		TileCoord getTile() const;
		int getAngleDeg() const; 
		int getDurability() const;
		static int getEnemyMobsQuantity();

		// visual
		static void prepareSprites();
		virtual void draw(sf::RenderWindow& window) = 0;
		
};

#endif // ENTITIES_H

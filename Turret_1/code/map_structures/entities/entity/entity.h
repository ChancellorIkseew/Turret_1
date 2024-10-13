#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <fstream>
#include <SFML\Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"

class Team;

class Entity
{
protected:
	static inline int mapSizeX, mapSizeY;
	static inline float enemyMobMaxDurabilityModifier;
	
	int type;
<<<<<<< Updated upstream
	//class Team& team;
=======
	Team* team;
>>>>>>> Stashed changes
	
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
	int reloadTimer;
	float maxSpeed;

	static inline sf::Image entityImage;
	static inline sf::Texture entityTexture;
	static inline sf::Sprite entitySprite;

	static inline sf::Image shieldImage;
	static inline sf::Texture shieldTexture;
	static inline sf::Sprite shieldSprite;

	void reloadWeapon();
	virtual PixelCoord findDestinationCoord() const;
	virtual PixelCoord findShootingAim() const;
	void detectAim();

public:
	static void initPreSettings();

	Entity(int type, Team* team);
	Entity() = default;
	virtual ~Entity() = default;

	void save(std::ofstream& fout) const;
	void load(std::ifstream& fin);
<<<<<<< Updated upstream
	static std::unique_ptr<Entity> createEntity(const int type);
=======
	static std::unique_ptr<Entity> createEntity(const int type, Team* team);
>>>>>>> Stashed changes
	static PixelCoord randomMapBorderSpawn();

	// combat
	virtual void motion();
	virtual void shoot() = 0;

	// simple_utilites
	void setDurability(const int durability);
	void setDamage(const int damage);
	void setCoord(const PixelCoord coord);
	char getType() const;
	PixelCoord getCoord() const;
	TileCoord getTile() const;
	int getAngleDeg() const;
	int getDurability() const;

	// visual
	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window) = 0;
		
};

#endif // ENTITY_H

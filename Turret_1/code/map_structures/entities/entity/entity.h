#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <fstream>
#include <SFML\Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/entities/behavior/aiming.h"
#include "map_structures/entities/behavior/path_finding.h"

class Team;

class Entity
{
protected:
	static inline TileCoord mapSize;
	static inline float maxDurabilityModifier;
	
	Team* team = nullptr;
	
	PixelCoord coord;
	PixelCoord aimCoord;
	PixelCoord destCoord; // destination_point
	TileCoord currentTile, oldTile;
	
	bool isAimDetected = false;
	
	float motionAngleRad = 0;
	float motionAngleDeg = 0;
	float shootingAngleRad = 0;
	float shootingAngleDeg = 0;

	float maxSpeed = 0;

	uint16_t type = 0;

	int16_t durability = 0; // timer_and_durability can_be_negative_in_some_cases
	int16_t reloadTimer = 0;
	uint16_t pixelRange = 0;
	uint16_t spyralRange = 0;
	

	static inline sf::Image entityImage;
	static inline sf::Texture entityTexture;
	static inline sf::Sprite entitySprite;

	static inline sf::Image shieldImage;
	static inline sf::Texture shieldTexture;
	static inline sf::Sprite shieldSprite;

	void reloadWeapon();
	void detectAim();

public:
	static void initPreSettings();

	Entity(const uint16_t type, Team* const team);
	virtual ~Entity() = default;

	void save(std::ofstream& fout) const;
	void load(std::ifstream& fin);

	static std::unique_ptr<Entity> createEntity(const uint16_t type, Team* const team);
	static PixelCoord randomMapBorderSpawn();

	// combat
	bool tileChanged() const;
	virtual void motion();
	virtual void shoot() = 0;

	// simple_utilites
	void setDurability(const int16_t durability);
	void setDamage(const int16_t damage);
	void setCoord(const PixelCoord coord);
	uint16_t getType() const;
	PixelCoord getCoord() const;
	TileCoord getTile() const;
	int getAngleDeg() const;
	int getDurability() const;

	// visual
	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window) = 0;

	friend PixelCoord t1::ent::findAim(const Entity& entity);
	friend TileCoord t1::ent::findDestination(const Entity& entity);
		
};

#endif // ENTITY_H

#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/base_engine/base_engine.h"
#include "map_structures/entities/behavior/aiming.h"
#include "map_structures/entities/behavior/path_finding.h"

enum class MobType : uint8_t;
enum class MobCategory : uint8_t;

class Team;
class BuildingsMap;
class World;

class Entity
{
protected:
	static inline World* world;
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
	void detectAim(const World& world);

public:
	static void initWorld(World* world);

	Entity(Team* const team);
	Entity() = default;
	virtual ~Entity() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	static std::unique_ptr<Entity> createEntity(const MobType type, Team* const team);
	static PixelCoord randomMapBorderSpawn();

	// combat
	bool tileChanged() const;
	virtual void motion(const BuildingsMap& buildingsMap);
	virtual void shoot(const BuildingsMap& buildingsMap) = 0;

	// simple_utilites
	void setDurability(const int16_t durability);
	void setDamage(const int16_t damage);
	void setCoord(const PixelCoord coord);
	void setDestCoord(const PixelCoord destCoord);
	PixelCoord getCoord() const { return coord; }
	TileCoord getTile() const { return currentTile; }
	float getAngleRad() const { return motionAngleRad; }
	int getDurability() const { return durability; }
	Team* getTeam() const { return team; }

	virtual MobCategory getCategory() const = 0;
	virtual MobType getType() const = 0;

	// visual
	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window) = 0;

	friend PixelCoord t1::ent::findAim(const Entity& entity, const World& world);
	friend TileCoord t1::ent::findDestination(const Entity& entity, const BuildingsMap& buildingsMap);
		
};

#endif // ENTITY_H

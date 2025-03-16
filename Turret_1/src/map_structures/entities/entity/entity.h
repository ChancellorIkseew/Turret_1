#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>
#include "map_structures/base_engine/base_engine.h"
#include "control.h"

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
	PixelCoord aimCoord = INCORRECT_PIXEL_COORD;
	TileCoord destCoord = INCORRECT_TILE_COORD; // destination_point
	PixelCoord lineMotion;
	TileCoord currentTile, nextTile;
	
	float motionAngleRad = 0;
	float shootingAngleRad = 0;

	Control control = Control::HARD;
	bool tileJustChanged = false;

	int16_t durability = 0; // timer_and_durability can_be_negative_in_some_cases
	int16_t reloadTimer = 0;

	static inline sf::Image entityImage;
	static inline sf::Texture entityTexture;
	static inline sf::Sprite entitySprite = sf::Sprite(entityTexture);

	static inline sf::Image shieldImage;
	static inline sf::Texture shieldTexture;
	static inline sf::Sprite shieldSprite = sf::Sprite(shieldTexture);

	void reloadWeapon();
	void aim(const int spyralRange, const float pixelRange);
	void checkTileChanged();
	void changeLineMotion(const float speed);
	virtual void calculateMotion(const BuildingsMap& buildingsMap);

public:
	Entity(Team* team);
	Entity() = default;
	virtual ~Entity() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	static std::unique_ptr<Entity> createEntity(const MobType type, Team* team);

	// combat
	
	void interact();

	virtual void moveByDirectControl(const PixelCoord vector);
	virtual void moveByOwnAI();

	virtual void shootByOwnAI() = 0;
	virtual void shoot() = 0;

	// simple_utilites
	void setTeam(Team* team);
	void setDurability(const int16_t durability);
	void setControlType(Control controlType);
	void setDamage(const int16_t damage);
	void setDamage(const float damage);
	void setCoord(const PixelCoord coord);
	void setDestCoord(const TileCoord destCoord);
	void setShootingAim(const PixelCoord aimCoord);
	PixelCoord getCoord() const { return coord; }
	TileCoord getTile() const { return currentTile; }
	float getAngleRad() const { return motionAngleRad; }
	int getDurability() const { return durability; }
	Control getControlType() const { return control; }
	Team* getTeam() const { return team; }

	virtual MobCategory getCategory() const = 0;
	virtual MobType getType() const = 0;

	// visual
	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window) = 0;

	static void initWorld(World* world) {
		Entity::world = world;
	}
};

#endif // ENTITY_H

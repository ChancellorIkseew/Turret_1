#pragma once
#ifndef TURRETS_H
#define TURRETS_H

#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

#include "map_structures/base_engine/base_engine.h"
#include "map_structures/entities/behavior/aiming.h"

enum class BuildingType : uint16_t;
enum class ResType : uint8_t;

class Team;
class World;

class Turret
{
private:
	static inline World* world;

protected:
	PixelCoord coord;
	PixelCoord aimCoord;
	Team* team = nullptr;
	
	float angleRad = 0;
	
	int16_t reloadTimer = 0;
	uint16_t amooQuantity = 0;
	
	static inline sf::Image turretImage;
	static inline sf::Texture turretTexture;
	static inline sf::Sprite turretSprite = sf::Sprite(turretTexture);

	void reloadWeapon();
	void aim(const int spyralRange, const float pixelRange);

public:
	Turret(const TileCoord tile, Team* const team);
	Turret() = default;
	~Turret() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);
	static std::unique_ptr<Turret> createTurret(const BuildingType type, const TileCoord tile, Team* const team);

	virtual void shooting() = 0;

	bool needAmoo() const;
	virtual void takeAmoo(const ResType resType) = 0;

	TileCoord getTile() const { return t1::be::tile(coord); }
	PixelCoord getCoord() const { return coord; }
	float getAngleRad() const { return angleRad; }
	short getAmooQuantity() const { return amooQuantity; }
	virtual  short getMaxAmoo() const = 0;
	virtual ResType getAmooType() const = 0;
	void setCoord(const PixelCoord coord);

	// visual
	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window) = 0;

	static void initWorld(World* world) {
		Turret::world = world;
	}
	friend Aiming;
};

CEREAL_REGISTER_TYPE(Turret)

#endif // TURRETS_H

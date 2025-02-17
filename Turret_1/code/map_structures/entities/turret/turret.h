#pragma once
#ifndef TURRETS_H
#define TURRETS_H

#include <fstream>
#include <SFML\Graphics.hpp>

#include "map_structures/base_engine/base_engine.h"

enum class BuildingType : uint16_t;

class Team;

class Turret
{
protected:
	PixelCoord coord;
	Team* team;
	
	float angleRad;
	float angleDeg;

	uint16_t type;
	
	int16_t durability; // timer_and_durability can_be_negative_in_xome_cases
	int16_t reloadTimer;
	uint16_t amooQuantity;
	uint16_t maxAmoo;
	
	uint16_t spyralRange;
	uint16_t pixelRange;
	
	static inline sf::Image turretImage;
	static inline sf::Texture turretTexture;
	static inline sf::Sprite turretSprite;

	void reloadWeapon();
	PixelCoord findShootingAim() const;

public:
	Turret(const TileCoord tile, Team* const team);
	~Turret() = default;

	void save(std::ofstream& fout) const;
	void load(std::ifstream& fin);
	static std::unique_ptr<Turret> createTurret(const BuildingType type, const TileCoord tile, Team* const team);

	virtual void shooting() = 0;

	bool needAmoo() const;
	virtual void takeAmoo(const int resType) = 0;

	uint16_t getType() const;
	TileCoord getTile() const;
	PixelCoord getCoord() const;
	int getAngleDeg() const;
	int getDurability() const;
	short getAmooQuantity() const;
	virtual int getAmooType() const = 0;
	void setCoord(const PixelCoord coord);

	// visual
	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window) = 0;
		
};

#endif // TURRETS_H

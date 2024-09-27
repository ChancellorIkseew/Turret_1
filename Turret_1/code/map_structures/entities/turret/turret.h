#pragma once
#ifndef TURRETS_H
#define TURRETS_H

#include <fstream>
#include <SFML\Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"


class Turret
{
protected:
	int type;	
	PixelCoord coord;
	
	float angleRad;
	float angleDeg;
	
	int durability;
	short amooQuantity;
	short maxAmoo;

	int reloadTimer;
	int pixelRange;
	
	static inline sf::Image turretImage;
	static inline sf::Texture turretTexture;
	static inline sf::Sprite turretSprite;

	void reloadWeapon();
	PixelCoord findShootingAim() const;

public:
	Turret(const int type, const TileCoord tile);
	~Turret() = default;

	void save(std::ofstream& fout) const;
	void load(std::ifstream& fin);
	static std::unique_ptr<Turret> createTurret(const int type, const TileCoord tile);

	virtual void shooting() = 0;

	bool needAmoo() const;
	virtual void takeAmoo(const int resType) = 0;

	int getType() const;
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

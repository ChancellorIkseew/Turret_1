#pragma once
#ifndef SHELLS_H
#define SHELLS_H

#include <fstream>
#include <SFML\Graphics.hpp>

#include "map_structures/base_engine/base_engine.h"

class Team;

class Shell
{
protected:
	PixelCoord coord;
	PixelCoord lineMotion;

	Team* team;

	float angleRad;
	float angleDeg;

	bool isWasted;

	uint16_t type;
	int16_t damage;

	uint16_t curentLifeTime;
	uint16_t maxLifeTime;
	

	static inline sf::Image shellImage;
	static inline sf::Texture shellTexture;
	static inline sf::Sprite shellSprite;
	
public:
	Shell(const uint16_t type, const PixelCoord coord, float angleRad, float angleDeg, Team* const team);
	virtual ~Shell() = default;

	static std::unique_ptr<Shell> createShell(const uint16_t type, const PixelCoord coord, float angleRad, float angleDeg, Team* const team);

	virtual void motion();
	virtual void explosion();
	virtual void tryHitting();

	PixelCoord getCoord();
	bool getIsWasted();

	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window);

};

#endif // SHELLS_H

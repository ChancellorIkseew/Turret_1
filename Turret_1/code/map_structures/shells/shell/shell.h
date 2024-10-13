#pragma once
#ifndef SHELLS_H
#define SHELLS_H

#include <fstream>
#include <SFML\Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"

class Team;

class Shell
{
protected:
	short type;
	short damage;

	float angleRad;
	float angleDeg;
	
	PixelCoord coord;
	PixelCoord lineMotion;
	
	int curentLifeTime;
	int maxLifeTime;
	bool isWasted;
	Team* team;

	static inline sf::Image shellImage;
	static inline sf::Texture shellTexture;
	static inline sf::Sprite shellSprite;
	
public:
	Shell(short type, const PixelCoord coord, float angleRad, float angleDeg, Team* team);
	virtual ~Shell() = default;

<<<<<<< Updated upstream
	static std::unique_ptr<Shell> createShell(short type, const PixelCoord coord, float angleRad, float angleDeg);

	virtual void motion();
	virtual void explosion();
	virtual void tryPlayerShellsHitting();
	virtual void tryEnemyShellsHitting();
=======
	static std::unique_ptr<Shell> createShell(short type, const PixelCoord coord, float angleRad, float angleDeg, Team* team);

	virtual void motion();
	virtual void explosion();
>>>>>>> Stashed changes
	virtual void tryShellsHitting();

	PixelCoord getCoord();
	bool getIsWasted();

	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window);

};

#endif // SHELLS_H

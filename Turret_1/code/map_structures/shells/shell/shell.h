#pragma once
#ifndef SHELLS_H
#define SHELLS_H

#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/base_engine/base_engine.h"

class Team;

class Shell
{
protected:
	PixelCoord coord = PixelCoord(0, 0);
	PixelCoord lineMotion = PixelCoord(0, 0);

	Team* team = nullptr;

	float angleRad = 0.0f;
	float angleDeg = 0.0f;

	bool isWasted = false;

	uint16_t type = 0;
	int16_t damage = 0;

	uint16_t curentLifeTime = 0;
	uint16_t maxLifeTime = 0;
	

	static inline sf::Image shellImage;
	static inline sf::Texture shellTexture;
	static inline sf::Sprite shellSprite;
	
public:
	Shell(const uint16_t type, const PixelCoord coord, float angleRad, float angleDeg, Team* const team);
	Shell() = default;
	virtual ~Shell() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

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

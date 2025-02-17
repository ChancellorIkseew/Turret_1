#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/base_engine/base_engine.h"

class Entity;

class Weapon
{
protected:
	PixelCoord coord = PixelCoord(0, 0);
	PixelCoord shooter = PixelCoord(0, 0);

	float minAngleRad = -45.0f;
	float maxAngleRad = 45.0f;

	float angleRad = 0.0f;
	float angleDeg = 0.0f;

	float rotationSpeed = 0.0f;

	uint16_t shellType = 0;

	static inline sf::Image weaponImage;
	static inline sf::Texture weaponTexture;
	static inline sf::Sprite weaponSprite;

public:
	//Weapon();
	Weapon() = default;
	virtual ~Weapon() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	void shoot(const Entity& owner);
	void rotate(const Entity& owner);


	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window, const Entity& owner);

};

#endif // WEAPON_H

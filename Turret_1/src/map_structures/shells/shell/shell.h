#pragma once
#ifndef SHELLS_H
#define SHELLS_H

#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/base_engine/base_engine.h"

enum class ShellType : uint8_t;

class Team;
class World;

class Shell
{
protected:
	static inline World* world;

	PixelCoord coord;
	PixelCoord lineMotion;

	Team* team = nullptr;

	float angleRad = 0.0f;

	bool isWasted = false;

	uint16_t restLifeTime = 0;

	static inline sf::Image shellImage;
	static inline sf::Texture shellTexture;
	static inline sf::Sprite shellSprite = sf::Sprite(shellTexture);
	
public:
	Shell(const PixelCoord coord, const float angleRad, Team* team);
	Shell() = default;
	virtual ~Shell() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	static std::unique_ptr<Shell> createShell(const ShellType type, const PixelCoord coord, const float angleRad, Team* team);

	virtual void motion();
	virtual void tryHitting();
	virtual void explosion() { }

	virtual ShellType getType() = 0;
	virtual float getDirectDamage() = 0;
	PixelCoord getCoord() const { return coord; }
	bool getIsWasted() const { return isWasted; }
	void setWasted() { isWasted = true; }
	void setTeam(Team* team) { this->team = team; }

	static void prepareSprites();
	virtual void draw(sf::RenderWindow& window) = 0;
	static void initWorld(World* world) {
		Shell::world = world;
	}
};

#endif // SHELLS_H

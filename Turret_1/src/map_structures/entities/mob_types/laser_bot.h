#pragma once
#ifndef LASER_BOT_H
#define LASER_BOT_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entity/entity.h"

class LaserBot : public Entity
{
public:
	LaserBot(Team* team);
	LaserBot() = default;
	~LaserBot() = default;

	MobCategory getCategory() const override final { return MobCategory::MEDIUM; }
	MobType getType() const override final { return MobType::LASER_BOT; }

	void shoot() override final;
	void shootByOwnAI() override final;
	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(LaserBot)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, LaserBot)

#endif // LASER_BOT_H

#pragma once
#ifndef ROCKET_BOT_H
#define ROCKET_BOT_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entity/entity.h"

class RocketBot : public Entity
{
public:
	RocketBot(Team* const team);
	RocketBot() = default;
	~RocketBot() = default;

	MobCategory getCategory() const override final { return MobCategory::MEDIUM; }
	MobType getType() const override final { return MobType::ROCKET_BOT; }

	void shoot() override final;
	void shootByOwnAI() override final;
	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(RocketBot)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, RocketBot)

#endif // ROCKET_BOT_H

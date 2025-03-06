#pragma once
#ifndef STANDARD_BOT_H
#define STANDARD_BOT_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entity/entity.h"

class StandardBot : public Entity
{
public:
	StandardBot(Team* const team);
	StandardBot() = default;
	~StandardBot() = default;

	MobCategory getCategory() const override final { return MobCategory::LIGHT; }
	MobType getType() const override final { return MobType::STANDARD_BOT; }

	void shoot() override final;
	void shootByOwnAI() override final;
	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(StandardBot)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, StandardBot)

#endif // STANDARD_BOT_H

#pragma once
#ifndef HEAVY_BOT_H
#define HEAVY_BOT_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entity/entity.h"

class HeavyBot : public Entity
{
public:
	HeavyBot(Team* const team);
	HeavyBot() = default;
	~HeavyBot() = default;

	MobCategory getCategory() const override final { return MobCategory::HEAVY; }
	MobType getType() const override final { return MobType::HEAVY_BOT; }

	void shoot(const BuildingsMap& buildingsMap) override final;
	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(HeavyBot)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, HeavyBot)

#endif // HEAVY_BOT_H

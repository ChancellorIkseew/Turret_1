#pragma once
#ifndef ROCKET_BOSS_BOT_H
#define ROCKET_BOSS_BOT_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entity/entity.h"

class RocketBossBot : public Entity
{
public:
	RocketBossBot(Team* team);
	RocketBossBot() = default;
	~RocketBossBot() = default;

	MobCategory getCategory() const override final { return MobCategory::BOSS; }
	MobType getType() const override final { return MobType::ROCKET_BOSS; }

	void shoot() override final;
	void shootByOwnAI() override final;
	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(RocketBossBot)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, RocketBossBot)

#endif // ROCKET_BOSS_BOT_H

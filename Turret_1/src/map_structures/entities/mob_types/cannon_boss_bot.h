#pragma once
#ifndef CANNON_BOSS_BOT_H
#define CANNON_BOSS_BOT_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entity/entity.h"

class CannonBossBot : public Entity
{
public:
	CannonBossBot(Team* const team);
	CannonBossBot() = default;
	~CannonBossBot() = default;

	MobCategory getCategory() const override final { return MobCategory::BOSS; }
	MobType getType() const override final { return MobType::CANNON_BOSS; }

	void shoot() override final;
	void shootByOwnAI() override final;
	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(CannonBossBot)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, CannonBossBot)

#endif // CANNON_BOSS_BOT_H

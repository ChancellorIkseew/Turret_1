#pragma once
#ifndef SHUTTLE_H
#define SHUTTLE_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/entities/entity/mob_enum.h"
#include "map_structures/entities/entity/entity.h"

class Shuttle : public Entity
{
public:
	Shuttle(Team* const team);
	Shuttle() = default;
	~Shuttle() = default;

	MobCategory getCategory() const override final { return MobCategory::BOSS; }
	MobType getType() const override final { return MobType::CANNON_BOSS; }

	void motion(const BuildingsMap& buildingsMap) override final;
	void shoot(const BuildingsMap& buildingsMap) override final;
	void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(Shuttle)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, Shuttle)

#endif // SHUTTLE_H

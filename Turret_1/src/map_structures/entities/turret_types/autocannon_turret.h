#pragma once
#ifndef AUTOCANNON_TURRET_H
#define AUTOCANNON_TURRET_H

#include <SFML\Graphics.hpp>
#include <cereal/types/polymorphic.hpp>
#include "map_structures/entities/turret/turret.h"

class AutocannonTurret : public Turret
{
	public:
		AutocannonTurret(const TileCoord tile, Team* const team);
		AutocannonTurret() = default;
		~AutocannonTurret() = default;

		void shooting() override final;
		
		void takeAmoo(const ResType resType) override final;
		short getMaxAmoo() const override final { return 180; }
		ResType getAmooType() const override final;
		
		void draw(sf::RenderWindow& window) override final;

};

CEREAL_REGISTER_TYPE(AutocannonTurret)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Turret, AutocannonTurret)

#endif // AUTOCANNON_TURRET_H

#pragma once
#ifndef MOB_CONTROLLER
#define MOB_CONTROLLER

#include "map_structures/entities/entity/control.h"

class Entity;
class Team;

class MobController
{
private:
	static inline Entity* targetedEntity = nullptr;
	static inline Control preveousControlType = Control::NONE;

	static void move();
	static void mine();
	static void shoot();

public:
	static void captureEntity(const Team& player);
	static void interact(const Team& player);

	static void setTarget(Entity* target) { targetedEntity = target; }
	static Entity* getTarget() { return targetedEntity; }

};

#endif // MOB_CONTROLLER

#pragma once
#ifndef MOB_CONTROLLER
#define MOB_CONTROLLER

#include <atomic>
#include "map_structures/base_engine/base_engine.h"
#include "map_structures/entities/entity/control.h"

class Entity;
class Team;

class MobController
{
private:
	static inline Entity* targetedEntity = nullptr;
	static inline Control preveousControlType = Control::NONE;
	static inline std::atomic<PixelCoord> motionVector;

	static void move();
	static void mine();
	static void shoot();

public:
	static void captureEntity(const Team& player);
	static void interact(const Team& player);

	static void setTarget(Entity* target) { targetedEntity = target; }
	static Entity* getTarget() { return targetedEntity; }

	static PixelCoord getMotionVector() { return motionVector.load(std::memory_order_relaxed); }

};

#endif // MOB_CONTROLLER

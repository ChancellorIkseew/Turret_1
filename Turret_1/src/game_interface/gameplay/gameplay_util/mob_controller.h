#pragma once
#ifndef MOB_CONTROLLER
#define MOB_CONTROLLER

#include <atomic>
#include "map_structures/base_engine/base_engine.h"
#include "map_structures/entities/entity/control.h"

class Entity;
class Team;
class Gameplay;

class MobController
{
private:
	static inline Entity* targetedEntity = nullptr;
	static inline Control preveousControlType = Control::NONE;
	static inline std::atomic<PixelCoord> motionVector;
	static inline std::atomic<PixelCoord> aimCoord;
	static inline std::atomic<bool> shooting;

	static void move();
	static void mine();
	static void shoot(const Gameplay& gameplay);

public:
	static void captureEntity(const Team& player);
	static void interact(const Team& player, const Gameplay& gameplay);

	static void setTarget(Entity* target) { targetedEntity = target; }
	static Entity* getTarget() { return targetedEntity; }

	static PixelCoord getMotionVector() { return motionVector.load(std::memory_order_relaxed); }
	static PixelCoord getAimCoord() { return aimCoord.load(std::memory_order_relaxed); }
	static bool shootingActive() { return shooting.load(std::memory_order_relaxed); }

};

#endif // MOB_CONTROLLER

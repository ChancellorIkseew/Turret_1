#pragma once
#ifndef T1_ENT_AIMING_H
#define T1_ENT_AIMING_H

#include "map_structures/base_engine/base_engine.h"

class Entity;

namespace t1::ent
{
	PixelCoord findAim(const Entity& entity);
}

#endif // T1_ENT_AIMING_H

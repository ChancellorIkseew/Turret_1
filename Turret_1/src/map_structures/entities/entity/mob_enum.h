#pragma once
#ifndef MOB_ENUM_H
#define MOB_ENUM_H

enum class MobType : uint8_t
{
	UNKNOWN_VALUE = 0, // for_test
	STANDARD_BOT = 1,
	HEAVY_BOT = 2,
	CANNON_BOT = 3,
	ROCKET_BOT = 4,
	MELE_BOT = 5,
	FLAME_BOT = 6,
	LASER_BOT = 7,
	GRAVITY_BOT = 8,

	CANNON_BOSS = 21,
	ROCKET_BOSS = 22,

	LIGHT_SHUTTLE = 41,
	HEAVY_SHUTTLE = 42
};

enum class MobCategory : uint8_t
{
	LIGHT,
	MEDIUM,
	HEAVY,
	SUPER_HEAVY,
	BOSS
};

#endif //!MOB_ENUM_H

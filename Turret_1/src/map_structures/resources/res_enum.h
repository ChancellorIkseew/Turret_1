#pragma once
#ifndef T1_RES_ENUM
#define T1_RES_ENUM


enum class ResType : uint8_t
{
	NO_RESOURCES = 0,
	ANY_RES = 0,

	STONE = 1,
	IRON = 2,
	COPPER = 3,
	SILICON = 4,
	COAL = 5,
	SULFUR = 6,
	SAND = 7,
	ZINÑ = 8,
	MANGANUM = 9,
	URANIUM = 10,

	GLASS = 101,
	BRASS = 102,
	CONCRETE = 103,
	STEEL = 104,
	HYDROGEN = 105,
	CARBON = 106,
	
	AC_SHELLS = 201,
	HEAVY_SHELLS = 202,
	ROCKET = 203,
	RAIL_SHELLS= 204
};

#endif RES_ENUM

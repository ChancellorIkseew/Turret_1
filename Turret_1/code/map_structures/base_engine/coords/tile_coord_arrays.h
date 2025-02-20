#pragma once
#ifndef T1_BE_TILE_COORD_ARRAYS
#define T1_BE_TILE_COORD_ARRAYS

#include <array>
#include "tile_coord.h"

namespace t1::be
{
	extern const std::array<int, 35> tileRangeToSpiralRange;
	extern const std::array<TileCoord, 16> coordSquareArr; 
	extern const std::array<TileCoord, 4109> coordSpyralArr;
};

#endif // T1_BE_TILE_COORD_ARRAYS

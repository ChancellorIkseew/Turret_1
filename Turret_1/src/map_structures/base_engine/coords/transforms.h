#pragma once
#ifndef T1_BE_TRANSFORMS
#define T1_BE_TRANSFORMS

#include "tile_coord.h"
#include "pixel_coord.h"

constexpr int _TILE_ = 32;
constexpr int _HALF_TILE_ = 16;

namespace t1::be
{
	int tile(float pixelCoord);
	int tile(int pixelCoord);
	TileCoord tile(float pixelCoordX, float pixelCoordY);
	TileCoord tile(int pixelCoordX, int pixelCoordY);
	TileCoord tile(const PixelCoord pixelCoord);

	int pixel(int tileCoord);
	float pixelF(int tileCoord);
	PixelCoord pixel(int tileCoordX, int tileCoordY);
	PixelCoord pixel(const TileCoord tileCoord);

	int pow2i(const int value);
	PixelCoord correction(const PixelCoord center, const PixelCoord point, const float angleRad);
	int spiralRangeToTileRange(const int spiralRange);

	float radToDegree(const float radian);
};

#endif // T1_BE_TRANSFORMS

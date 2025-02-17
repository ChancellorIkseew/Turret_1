#pragma once
#ifndef T1_BE_TRANSFORMS
#define T1_BE_TRANSFORMS

#include "tile_coord.h"
#include "pixel_coord.h"

constexpr int _TILE_ = 32;
constexpr int _HALF_TILE_ = 16;

namespace t1::be
{
	inline int tile(float pixelCoord);
	inline int tile(int pixelCoord);
	TileCoord tile(float pixelCoordX, float pixelCoordY);
	TileCoord tile(int pixelCoordX, int pixelCoordY);
	TileCoord tile(PixelCoord pixelCoord);

	inline int pixel(int tileCoord);
	inline float pixelF(int tileCoord);
	PixelCoord pixel(int tileCoordX, int tileCoordY);
	PixelCoord pixel(TileCoord tileCoord);

	int pow2i(const int value);
	PixelCoord correction(const PixelCoord center, const PixelCoord point, const float angleRad);

	float radToDegree(const float radian);
};

#endif // T1_BE_TRANSFORMS

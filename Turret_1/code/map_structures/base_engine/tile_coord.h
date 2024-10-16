#pragma once
#include <array>

#ifndef T1_BE_TILE_COORD_H
#define T1_BE_TILE_COORD_H

#define _TILE_ 32
#define _HALF_TILE_ 16

struct TileCoord
{
	int x, y;
};

struct PixelCoord
{
	float x, y;
};

namespace t1::be
{
	extern const TileCoord coordSquareArr[16];
	extern const TileCoord coordSpyralArr[4109];

	inline int tile(float pixelCoord);
	inline int tile(int pixelCoord);
	TileCoord tile(float pixelCoordX, float pixelCoordY);
	TileCoord tile(int pixelCoordX, int pixelCoordY);
	TileCoord tile(PixelCoord pixelCoord);

	inline int pixel(int tileCoord);
	inline float pixelF(int tileCoord);
	PixelCoord pixel(int tileCoordX, int tileCoordY);
	PixelCoord pixel(TileCoord tileCoord);
};

#endif // T1_BE_TILE_COORD_H

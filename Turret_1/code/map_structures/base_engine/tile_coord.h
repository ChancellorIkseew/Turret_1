#pragma once
#include <array>

#ifndef T1_BE_TILE_COORD_H
#define T1_BE_TILE_COORD_H

#define _TILE_ 32
#define _HALF_TILE_ 16

struct TileCoord
{
	int x = 0, y = 0;

	TileCoord() = default;
	TileCoord(int x, int y) {
		this->x = x;
		this->y = y;
	}

	TileCoord operator+(const TileCoord& rhs) const {
		return { x + rhs.x, y + rhs.y };
	}
	TileCoord operator-(const TileCoord& rhs) const {
		return { x - rhs.x, y - rhs.y };
	}
	TileCoord operator*(const int value) const {
		return { x * value, y * value };
	}
	TileCoord operator/(const int value) const {
		return { x / value, y / value };
	}
};

struct PixelCoord
{
	float x = 0, y = 0;
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

	int pow2i(const int value);

	float radToDegree(const float radian);
};

#endif // T1_BE_TILE_COORD_H

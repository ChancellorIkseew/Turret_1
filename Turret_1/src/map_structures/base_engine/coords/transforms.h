#pragma once
#ifndef T1_BE_TRANSFORMS
#define T1_BE_TRANSFORMS

#include "tile_coord.h"
#include "pixel_coord.h"
#include <SFML/System/Vector2.hpp>

constexpr int _TILE_ = 32;
constexpr int _HALF_TILE_ = 16;

constexpr sf::Vector2i X1_RECT(_TILE_, _TILE_);			// tile X tile
constexpr sf::Vector2i X2_RECT(_TILE_ * 2, _TILE_ * 2); // 2 tile X 2 tile
constexpr sf::Vector2i X3_RECT(_TILE_ * 3, _TILE_ * 3); // 3 tile X 3 tile
constexpr sf::Vector2i X4_RECT(_TILE_ * 4, _TILE_ * 4); // 4 tile X 4 tile
constexpr sf::Vector2i X5_RECT(_TILE_ * 5, _TILE_ * 5); // 5 tile X 5 tile
constexpr sf::Vector2i X6_RECT(_TILE_ * 6, _TILE_ * 6); // 6 tile X 6 tile

constexpr float PI = 3.14159265359f;

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
	float pow2f(const float value);
	bool areCloser(const PixelCoord first, const PixelCoord second, const float distance);
	PixelCoord correction(const PixelCoord center, const PixelCoord point, const float angleRad);
	int spiralRangeToTileRange(const int spiralRange);

	float radToDegree(const float radian);
};

#endif // T1_BE_TRANSFORMS

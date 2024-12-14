#pragma once
#ifndef T1_BE_TILE_COORD_H
#define T1_BE_TILE_COORD_H

#include <array>

struct TileCoord
{
	int x = 0, y = 0;

	TileCoord() = default;
	TileCoord(int x, int y) : x(x), y(y) {}

	bool operator==(const TileCoord& rhs) {
		return { x == rhs.x && y == rhs.y };
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

#endif // T1_BE_TILE_COORD_H

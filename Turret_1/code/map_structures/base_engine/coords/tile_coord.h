#pragma once
#ifndef T1_BE_TILE_COORD_H
#define T1_BE_TILE_COORD_H

#include <cereal/archives/binary.hpp>
#include <limits>

constexpr int MINIMAL_INT = std::numeric_limits<int>::lowest();

struct TileCoord
{
	int x = 0, y = 0;

	TileCoord() = default;
	TileCoord(int x, int y) : x(x), y(y) {}

	void save(cereal::BinaryOutputArchive& archive) const {
		archive(x);
		archive(y);
	}
	void load(cereal::BinaryInputArchive& archive) {
		archive(x);
		archive(y);
	}

	bool valid() const {
		return x > MINIMAL_INT;
	}
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

const TileCoord INCORRECT_TILE_COORD = TileCoord(MINIMAL_INT, MINIMAL_INT);

#endif // T1_BE_TILE_COORD_H

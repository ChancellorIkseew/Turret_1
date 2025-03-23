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
	TileCoord(const int x, const int y) : x(x), y(y) {}
	constexpr TileCoord(const int x, const int y, const char cExprFlag) : x(x), y(y) {}
	
	void save(cereal::BinaryOutputArchive& archive) const { archive(x, y); }
	void load(cereal::BinaryInputArchive& archive) { archive(x, y); }
	
	bool valid() const { return x > MINIMAL_INT; }
	
	bool operator==(const TileCoord& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const TileCoord& rhs) const {
		return x != rhs.x || y != rhs.y;
	}
	
	TileCoord operator+(const TileCoord& rhs) const {
		return TileCoord(x + rhs.x, y + rhs.y);
	}
	TileCoord operator-(const TileCoord& rhs) const {
		return TileCoord(x - rhs.x, y - rhs.y);
	}
	TileCoord operator*(const int value) const {
		return TileCoord(x * value, y * value);
	}
	TileCoord operator/(const int value) const {
		return TileCoord(x / value, y / value);
	}
};

constexpr TileCoord INCORRECT_TILE_COORD(MINIMAL_INT, MINIMAL_INT, 'c');

#endif // T1_BE_TILE_COORD_H

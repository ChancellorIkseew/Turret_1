#pragma once
#ifndef T1_BE_PIXEL_COORD_H
#define T1_BE_PIXEL_COORD_H

#include <cereal/archives/binary.hpp>

struct PixelCoord
{
	float x = 0.0f, y = 0.0f;

	PixelCoord() = default;
	PixelCoord(float x, float y) : x(x), y(y) { }
	PixelCoord(int x, int y) {
		this->x = static_cast<float>(x);
		this->y = static_cast<float>(y);
	}

	void save(cereal::BinaryOutputArchive& archive) const {
		archive(x);
		archive(y);
	}
	void load(cereal::BinaryInputArchive& archive) {
		archive(x);
		archive(y);
	}

	bool operator==(const PixelCoord& rhs) const {
		constexpr float epsilon = 0.0001f;
		return std::abs(x - rhs.x) < epsilon && std::abs(y - rhs.y) < epsilon;
	}

	PixelCoord operator+(const PixelCoord& rhs) const {
		return { x + rhs.x, y + rhs.y };
	}
	PixelCoord operator-(const PixelCoord& rhs) const {
		return { x - rhs.x, y - rhs.y };
	}
	PixelCoord operator*(const float value) const {
		return { x * value, y * value };
	}
	PixelCoord operator/(const float value) const {
		return { x / value, y / value };
	}
	PixelCoord operator*(const int value) const {
		float floatValue = static_cast<float>(value);
		return { x * floatValue, y * floatValue };
	}
	PixelCoord operator/(const int value) const {
		float floatValue = static_cast<float>(value);
		return { x / floatValue, y / floatValue };
	}
};

#endif // T1_BE_PIXEL_COORD_H

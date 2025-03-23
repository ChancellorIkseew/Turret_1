#pragma once
#ifndef T1_BE_PIXEL_COORD_H
#define T1_BE_PIXEL_COORD_H

#include <cereal/archives/binary.hpp>
#include <limits>

constexpr float MINIMAL_FLOAT = std::numeric_limits<float>::lowest();

struct PixelCoord
{
private:
	static inline constexpr float epsilon = 0.0001f;
public:
	float x = 0.0f, y = 0.0f;
	
	PixelCoord() = default;
	PixelCoord(const float x, const float y) : x(x), y(y) {}
	PixelCoord(const int x, const int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}
	constexpr PixelCoord(const float x, const float y, const char cExprFlag) : x(x), y(y) {}
	
	void save(cereal::BinaryOutputArchive& archive) const { archive(x, y); }
	void load(cereal::BinaryInputArchive& archive) { archive(x, y); }
	
	bool valid() const { return x > MINIMAL_FLOAT + epsilon; }
	
	bool operator==(const PixelCoord& rhs) const {
		return std::abs(x - rhs.x) <= epsilon && std::abs(y - rhs.y) <= epsilon;
	}
	bool operator!=(const PixelCoord& rhs) const {
		return std::abs(x - rhs.x) > epsilon || std::abs(y - rhs.y) > epsilon;
	}
	
	PixelCoord operator+(const PixelCoord& rhs) const {
		return PixelCoord(x + rhs.x, y + rhs.y);
	}
	PixelCoord operator-(const PixelCoord& rhs) const {
		return PixelCoord(x - rhs.x, y - rhs.y);
	}
	PixelCoord operator*(const float value) const {
		return PixelCoord(x * value, y * value);
	}
	PixelCoord operator/(const float value) const {
		return PixelCoord(x / value, y / value);
	}
	PixelCoord operator*(const int value) const {
		const float floatValue = static_cast<float>(value);
		return PixelCoord(x * floatValue, y * floatValue);
	}
	PixelCoord operator/(const int value) const {
		const float floatValue = static_cast<float>(value);
		return PixelCoord(x / floatValue, y / floatValue);
	}
};

constexpr PixelCoord INCORRECT_PIXEL_COORD(MINIMAL_FLOAT, MINIMAL_FLOAT, 'c');

#endif // T1_BE_PIXEL_COORD_H

#pragma once
#ifndef T1_BE_PIXEL_COORD_H
#define T1_BE_PIXEL_COORD_H

struct PixelCoord
{
	float x = 0.0f, y = 0.0f;

	PixelCoord() = default;
	PixelCoord(float x, float y) : x(x), y(y) { }
	PixelCoord(int x, int y) {
		this->x = static_cast<float>(x);
		this->y = static_cast<float>(y);
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

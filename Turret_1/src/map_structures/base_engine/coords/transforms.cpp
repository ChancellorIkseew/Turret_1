
#include "transforms.h"
#include "tile_coord_arrays.h"

// pixel_to_tile
int t1::be::tile(float pixelCoord) {
	return int(static_cast<int>(pixelCoord) / _TILE_);
}

int t1::be::tile(int pixelCoord) {
	return int(pixelCoord / _TILE_);
}

TileCoord t1::be::tile(float pixelCoordX, float pixelCoordY) {
	return { tile(pixelCoordX) , tile(pixelCoordY) };
}

TileCoord t1::be::tile(int pixelCoordX, int pixelCoordY) {
	return { tile(pixelCoordX) , tile(pixelCoordY) };
}

TileCoord t1::be::tile(const PixelCoord pixelCoord) {
	return { tile(pixelCoord.x) , tile(pixelCoord.y) };
}


// tile_to_pixel
int t1::be::pixel(int tileCoord) {
	return tileCoord * _TILE_ + _HALF_TILE_;
}

float t1::be::pixelF(int tileCoord) {
	return static_cast<float>(tileCoord * _TILE_ + _HALF_TILE_);
}

PixelCoord t1::be::pixel(int tileCoordX, int tileCoordY) {
	return { pixelF(tileCoordX),  pixelF(tileCoordY) };
}

PixelCoord t1::be::pixel(const TileCoord tileCoord) {
	return { pixelF(tileCoord.x), pixelF(tileCoord.y) };
}


// simple math
int t1::be::pow2i(const int value) {
	return value * value;
}

float t1::be::pow2f(const float value) {
	return value * value;
}

bool t1::be::areCloser(const PixelCoord first, const PixelCoord second, const float distance) {
	return abs(first.x - second.x) < distance && abs(first.y - second.y) < distance;
}

PixelCoord t1::be::correction(const PixelCoord center, const PixelCoord point, const float angleRad) {

	return PixelCoord(0, 0);
}

int t1::be::spiralRangeToTileRange(const int spiralRange) {
	for (int i = 0; i < 35; ++i) {
		if (t1::be::tileRangeToSpiralRange[i] > spiralRange) {
			return i;
		}
	}
}


// angles
float t1::be::radToDegree(const float radian) {
	return 180.0f - radian * 57.3f;
}

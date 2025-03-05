
#include "comon.h"

constexpr int STEP = _TILE_ / 16;

TileCoord Comon::findDirectPahtNextTile(const PixelCoord point, const TileCoord currentTile, const float angleToAim)
{
	float correction;
	PixelCoord line;
	TileCoord checkTile;
	for (int range = STEP; range < _TILE_ + _HALF_TILE_; range += STEP)
	{
		correction = static_cast<float>(range);
		line.x = sin(angleToAim) * correction;
		line.y = cos(angleToAim) * correction;
		checkTile = t1::be::tile(point + line);
		if (!(checkTile == currentTile))
			return checkTile;
	}
	return currentTile; // imposible in real situation.
}
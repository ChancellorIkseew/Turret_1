#pragma once

#ifndef TILE_COORD_H
#define TILE_COORD_H

#define _TILE_ 32
#define _HALF_TILE_ 16

struct TileCoord
{
	int x;
	int y;
};


extern const TileCoord coordSquareArr[16];

extern const TileCoord coordSpyralArr[4109];




//#define toTile()

int tile(float pixelCoord);

int tile(int pixelCoord);

int pixel(int tileCoord);


#endif //TILE_COORD_H

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


int tile(float pixelCoord);
int tile(int pixelCoord);
TileCoord tile(float pixelCoordX, float pixelCoordY);
TileCoord tile(int pixelCoordX, int pixelCoordY);

int pixel(int tileCoord);


#endif //TILE_COORD_H

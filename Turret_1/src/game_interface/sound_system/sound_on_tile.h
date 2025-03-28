#pragma once
#ifndef SOUND_ON_TILE_H
#define SOUND_ON_TILE_H

#include "sound_enum.h"
#include "map_structures/base_engine/base_engine.h"

struct SoundOnTile
{
	const SoundType type;
	const TileCoord tile;

	SoundOnTile(const SoundType type, const TileCoord tile) : type(type), tile(tile) {}
};

#endif // SOUND_ON_TILE_H

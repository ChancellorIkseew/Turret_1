#pragma once
#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include <vector>
#include <map>
#include <memory>

#include "map_structures/pre-settings/pre_settings/terrain_pre.h"


std::vector<std::vector<std::unique_ptr<int>>> generateTerrain(TerrainPre& terrainPre);

#endif // TERRAIN_GENERATOR_H

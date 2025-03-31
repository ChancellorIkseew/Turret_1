
#include "texturepacks.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/building/building.h"
#include "map_structures/blueprints/blueprints_map.h"
#include "map_structures/entities/turret/turret.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/shells/shell/shell.h"
#include "map_structures/particles/particle/particle.h"


void Texturepacks::loadTextures()
{
    TerrainMap::prepareSprites();
    Building::prepareSprites();
    BlueprintsMap::prepareSprites();
    Turret::prepareSprites();
    ResourceUnit::prepareSprites();
    Entity::prepareSprites();
    Shell::prepareSprites();
    Particle::prepareSprites();
}

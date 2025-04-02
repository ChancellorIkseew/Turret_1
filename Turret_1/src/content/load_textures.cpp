
#include "texturepacks.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/building/building.h"
#include "map_structures/blueprints/blueprints_map.h"
#include "map_structures/entities/turret/turret.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/shells/shell/shell.h"
#include "map_structures/particles/particle/particle.h"
#include "game_interface/ui_window/ui_window/ui_plate.h"
#include "game_interface/gameplay/ui_elements/building_panel.h"
#include "t1_system/t1_mutex.h"


void Texturepacks::loadTextures()
{
    std::lock_guard guard(t1::system::mt::drawing);
    // map_structures
    TerrainMap::prepareSprites();
    Building::prepareSprites();
    BlueprintsMap::prepareSprites();
    Turret::prepareSprites();
    ResourceUnit::prepareSprites();
    Entity::prepareSprites();
    Shell::prepareSprites();
    Particle::prepareSprites();
    // game_interface
    UIPlate::init();
    BuildingPanel::prepareSprites();
}

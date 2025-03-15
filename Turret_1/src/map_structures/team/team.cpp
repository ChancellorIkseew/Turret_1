
#include "team.h"
#include <cereal/types/string.hpp>


Team::Team(const std::string& name, const sf::Color& color, const int ID) :
    name(name), color(color), ID(ID) { }

void Team::save(cereal::BinaryOutputArchive& archive) const {
    archive(ID, name, balance, entities, shells);
    
}
void Team::load(cereal::BinaryInputArchive& archive) {
    archive(ID, name, balance, entities, shells);
    for (auto& entity : entities.getList())
        entity->setTeam(this);
    for (auto& shell : shells.getList())
        shell->setTeam(this);
}

void Team::spawnShell(const ShellType type, const PixelCoord coord, const float angleRad) {
    shells.spawnShell(type, coord, angleRad, this);
}
void Team::spawnEntity(const MobType type, const PixelCoord coord, const Control control) {
    auto entity = Entity::createEntity(type, this);
    if (entity == nullptr)
        return;
    entity->setCoord(coord);
    entity->setControlType(control);
    entities.spawnEntity(std::move(entity));
}

void Team::interact(const BuildingsMap& buildingsMap)
{
    entities.interact(buildingsMap);
    shells.interact();
}

void Team::draw(sf::RenderWindow& window, const Camera& camera)
{
    entities.draw(window, camera);
    shells.draw(window, camera);
}


#include "team.h"
#include <cereal/types/string.hpp>


Team::Team(std::string name)
{
    static int newID = 0;

    ID = newID;
    ++newID;
}

void Team::save(cereal::BinaryOutputArchive& archive) const
{
    archive(ID, name, balance, entities, shells);
}

void Team::load(cereal::BinaryInputArchive& archive)
{
    archive(ID, name, balance, entities, shells);
}

void Team::spawnShell(const ShellType type, const PixelCoord coord, float angleRad, float angleDeg)
{
    shells.spawnShell(type, coord, angleRad, angleDeg, this);
}

void Team::spawnEntity(const uint8_t amount, const MobType type, const BuildingsMap& buildingsMap)
{
    entities.spawnEntity(amount, type, this, buildingsMap);
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


int Team::getID() { return ID; }
Balance& Team::getBalance() { return balance; }


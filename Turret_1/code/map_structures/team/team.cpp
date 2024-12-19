
#include "team.h"


Team::Team(sf::String name)
{
    static int newID = 0;

    ID = newID;
    ++newID;
}
/*
void Team::addTeam(const sf::String& name)
{
    std::shared_ptr team = std::move(std::make_shared<Team>(name));
}

void Team::addTeam(const std::shared_ptr<Team> team)
{
    teams.emplace(team);
}
*/
void Team::spawnShell(const uint16_t type, const PixelCoord coord, float angleRad, float angleDeg)
{
    shells.spawnShell(type, coord, angleRad, angleDeg, this);
}

void Team::spawnEntity(const uint8_t amount, const uint16_t type, const BuildingsMap& buildingsMap)
{
    entities.spawnEntity(amount, type, this, buildingsMap);
}

void Team::interact(const BuildingsMap& buildingsMap)
{
    entities.interact(buildingsMap);
    shells.move();
}

void Team::draw(sf::RenderWindow& window)
{
    entities.draw(window);
    shells.draw(window);
}


int Team::getID() { return ID; }
Balance& Team::getBalance() { return balance; }


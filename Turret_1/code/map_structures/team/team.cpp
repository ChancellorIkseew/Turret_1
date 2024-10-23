
#include "team.h"


Team::Team(sf::String name)
{
    static int newID = 0;

    ID = newID;
    ++newID;
}

void Team::addTeam(const sf::String& name)
{
    std::shared_ptr team = std::move(std::make_shared<Team>(name));
}

void Team::addTeam(const std::shared_ptr<Team> team)
{
    teams.emplace(team);
}

void Team::spawnShell(const uint16_t type, const PixelCoord coord, float angleRad, float angleDeg)
{
    shells.spawnShell(type, coord, angleRad, angleDeg, this);
}

void Team::spawnEntity(const uint8_t amount, const uint16_t type)
{
    entities.spawnEntity(amount, type, this);
}

void Team::interact()
{
    entities.interact();
    shells.move();
}

void Team::interactAll()
{
    for (auto it = teams.begin(); it != teams.end(); ++it)
    {
        (*it)->interact();
    }
}


void Team::draw(sf::RenderWindow& window)
{
    entities.draw(window);
    shells.draw(window);
}


void Team::drawAll(sf::RenderWindow& window)
{
    for (auto it = teams.begin(); it != teams.end(); ++it)
    {
        (*it)->draw(window);
    }
}


int Team::getID() { return ID; }
Balance& Team::getBalance() { return balance; }


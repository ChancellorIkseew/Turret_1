
#include "team.h"


<<<<<<< Updated upstream
Team::Team()
{

=======
Team::Team(sf::String name)
{
    
}

void Team::addTeam(const sf::String& name)
{
    std::shared_ptr team = std::move(std::make_shared<Team>(name));
}

void Team::addTeam(const std::shared_ptr<Team> team)
{
    teams.emplace(team);
>>>>>>> Stashed changes
}

void Team::spawnShell(short type, const PixelCoord coord, float angleRad, float angleDeg)
{
<<<<<<< Updated upstream
    shellsList.spawnShell(type, coord, angleRad, angleDeg);
=======
    shells.spawnShell(type, coord, angleRad, angleDeg, this);
>>>>>>> Stashed changes
}

void Team::spawnEntity(const int amount, const int type)
{
<<<<<<< Updated upstream
    entitiesList.spawnEntity(amount, type);
=======
    entities.spawnEntity(amount, type, this);
>>>>>>> Stashed changes
}

void Team::interact()
{
<<<<<<< Updated upstream
    entitiesList.move();
    shellsList.move();
=======
    entities.interact();
    shells.move();
}

void Team::interactAll()
{
    for (auto it = teams.begin(); it != teams.end(); ++it)
    {
        (*it)->interact();
    }
>>>>>>> Stashed changes
}


void Team::draw(sf::RenderWindow& window)
{
<<<<<<< Updated upstream
    entitiesList.draw(window);
    shellsList.draw(window);
}
=======
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

>>>>>>> Stashed changes

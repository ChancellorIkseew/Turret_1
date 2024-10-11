
#include "team.h"


Team::Team()
{

}

void Team::spawnShell(short type, const PixelCoord coord, float angleRad, float angleDeg)
{
    shellsList.spawnShell(type, coord, angleRad, angleDeg);
}

void Team::spawnEntity(const int amount, const int type)
{
    entitiesList.spawnEntity(amount, type);
}

void Team::interact()
{
    entitiesList.move();
    shellsList.move();
}


void Team::draw(sf::RenderWindow& window)
{
    entitiesList.draw(window);
    shellsList.draw(window);
}

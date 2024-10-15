
#include "resources_panel.h"

#include "game_interface/sub_window/sub_win_util/fonts.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/team/team.h"


ResourcesPanel::ResourcesPanel() : SubWindow('s', sf::Vector2u(134, 219), sf::Vector2u(600, 600))
{
    resInfo[RES_STONE] = ResInfo(RES_STONE, 0);
    resInfo[RES_IRON] = ResInfo(RES_IRON, 0);
    resInfo[RES_COPPER] = ResInfo(RES_COPPER, 0);
    resInfo[RES_SILICON] = ResInfo(RES_SILICON, 0);
    resInfo[RES_COAL] = ResInfo(RES_COAL, 0);
    resInfo[RES_SULFUR] = ResInfo(RES_SULFUR, 0);

    this->prepareInterfaceSprites();
    this->relocate({ 0, 0 });
}


void ResourcesPanel::prepareInterfaceSprites()
{
    
}


void ResourcesPanel::interact(Team& team)
{
    mutex.lock();
    for (auto& resI : resInfo)
    {
        resI.second.update(team.getBalance().balance.allResources[resI.first]);
    }
    mutex.unlock();
}


void ResourcesPanel::relocate(const sf::Vector2u windowSize)
{
    position.x = windowSize.x - size.x;
    position.y = windowSize.y - 450;
}


void ResourcesPanel::draw(sf::RenderWindow &window)
{
    this->drawSubWindowBase(window);
    mutex.lock();
    int deltaY = 16;
    for (auto& resI : resInfo)
    {
        resI.second.draw(window, position.x + 16, position.y + deltaY);
        deltaY += 30;
    }
    mutex.unlock();
}

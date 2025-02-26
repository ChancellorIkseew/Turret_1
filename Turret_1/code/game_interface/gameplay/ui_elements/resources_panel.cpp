
#include "resources_panel.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/team/team.h"


ResourcesPanel::ResourcesPanel() : UIWindow(sf::Vector2u(134, 219), sf::Vector2u(0, 0))
{
    resInfo[ResType::STONE] = ResInfo(ResType::STONE, 0);
    resInfo[ResType::IRON] = ResInfo(ResType::IRON, 0);
    resInfo[ResType::COPPER] = ResInfo(ResType::COPPER, 0);
    resInfo[ResType::SILICON] = ResInfo(ResType::SILICON, 0);
    resInfo[ResType::COAL] = ResInfo(ResType::COAL, 0);
    resInfo[ResType::SULFUR] = ResInfo(ResType::SULFUR, 0);

    this->prepareInterfaceSprites();
}


void ResourcesPanel::prepareInterfaceSprites()
{
    
}


void ResourcesPanel::interact(Team& team)
{
    std::lock_guard<std::mutex> guard(mutex);
    for (auto& resI : resInfo)
    {
        resI.second.update(team.getBalance().getResources().getQuantity(resI.first));
    }
}


void ResourcesPanel::relocate(const sf::Vector2u windowSize)
{
    position.x = windowSize.x - size.x;
    position.y = windowSize.y - 550;
}


void ResourcesPanel::draw(sf::RenderWindow &window)
{
    drawBase(window);
    std::lock_guard<std::mutex> guard(mutex);
    int deltaY = 16;
    for (auto& resI : resInfo)
    {
        resI.second.draw(window, position.x + 16, position.y + deltaY);
        deltaY += 20;
    }
}

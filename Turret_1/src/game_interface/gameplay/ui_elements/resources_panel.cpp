
#include "resources_panel.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/team/team.h"


ResourcesPanel::ResourcesPanel() : UIWindow(sf::Vector2i(134, 219))
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
    for (auto& [type, info] : resInfo)
    {
        info.update(team.getBalance().getResources().getQuantity(type));
    }
}


void ResourcesPanel::relocate(const sf::Vector2i windowSize)
{
    position.x = windowSize.x - size.x;
    position.y = windowSize.y - 550;
}


void ResourcesPanel::draw(sf::RenderWindow &window)
{
    drawBase(window);
    std::lock_guard<std::mutex> guard(mutex);
    int deltaY = 16;
    for (auto& [type, info] : resInfo)
    {
        info.draw(window, position.x + 16, position.y + deltaY);
        deltaY += 20;
    }
}

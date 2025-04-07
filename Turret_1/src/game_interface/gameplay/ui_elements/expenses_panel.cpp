
#include <string>
#include <sstream>

#include "expenses_panel.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/pre-settings/pre-settings.h"

using Info = BuildingsInfoTable;
BuildingInfo ExpensesPanel::nullInfo = { L" ", 0, 0, {0, 0, 0, 0, 0, 0}, sf::IntRect({0, 0}, {0, 0}), L" " };

ExpensesPanel::ExpensesPanel() : UIWindow(sf::Vector2i(225, 120))
{
    resInfo.emplace(ResType::STONE, ResInfo(ResType::STONE, 0));
    resInfo.emplace(ResType::IRON, ResInfo(ResType::IRON, 0));
    resInfo.emplace(ResType::COPPER, ResInfo(ResType::COPPER, 0));
    resInfo.emplace(ResType::SILICON, ResInfo(ResType::SILICON, 0));
    resInfo.emplace(ResType::COAL, ResInfo(ResType::COAL, 0));
    resInfo.emplace(ResType::SULFUR, ResInfo(ResType::SULFUR, 0));

    this->prepareInterfaceSprites();
}


void ExpensesPanel::prepareInterfaceSprites()
{
    title.setPosition(sf::Vector2f(40, 320));
    title.setCharacterSize(16);
    title.setFillColor(standardColor);
}



void ExpensesPanel::interact(const BuildingType index, const BuildingsPre& buildingsPre)
{
    if (!isVisible)
        return;
    buildingInfo = Info::at(index);
    title.setString(buildingInfo.buildingTitle);
    for (auto& [type, info] : resInfo)
    {
        info.update(buildingInfo.costToBuild.allResources[type] * buildingsPre.expensesModifier);
    }
}


void ExpensesPanel::relocate(const sf::Vector2i windowSize)
{
    position.x = windowSize.x - size.x;
    position.y = windowSize.y - 192 - size.y;
}


void ExpensesPanel::draw(sf::RenderWindow& window)
{
    if (!isVisible)
        return;
    drawBase(window);
    title.setPosition(sf::Vector2f(position.x + 16, position.y + 10));
	window.draw(title);

    int posX = position.x + 16;
    int posY = position.y + 30;
    for (auto& [type, info] : resInfo)
    {
        if (info.getQuantity() != 0)
        {
            info.draw(window, posX, posY);
            posY += 20;
        }

        if (posY >= position.y + 110)
        {
            posY = position.y + 30;
            posX += 70;
        }
    }
}

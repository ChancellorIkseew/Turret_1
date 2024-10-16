
#include <string>
#include <sstream>
#include <SFML\Graphics.hpp>

#include "specifications_panel.h"

#include "game_interface/sub_window/sub_win_util/fonts.h"
#include "map_structures/resources/res_enum.h"


BuildingInfo SpecificationsPanel::nullInfo = { L" ", 0, 0, {0, 0, 0, 0, 0, 0}, L" " };

SpecificationsPanel::SpecificationsPanel() : SubWindow('s', sf::Vector2u(260, 400), sf::Vector2u(0, 310))
{
    resInfo.emplace(RES_STONE, ResInfo(RES_STONE, 0));
    resInfo.emplace(RES_IRON, ResInfo(RES_IRON, 0));
    resInfo.emplace(RES_COPPER, ResInfo(RES_COPPER, 0));
    resInfo.emplace(RES_SILICON, ResInfo(RES_SILICON, 0));
    resInfo.emplace(RES_COAL, ResInfo(RES_COAL, 0));
    resInfo.emplace(RES_SULFUR, ResInfo(RES_SULFUR, 0));

    this->prepareInterfaceSprites();
    this->relocate({ 0, 0 });
}


void SpecificationsPanel::prepareInterfaceSprites()
{
	title.setFont(turretClassic);
    title.setPosition(40, 320);
    title.setCharacterSize(16);
    title.setFillColor(standardColor);
	
    durability.setFont(turretClassic);
    durability.setPosition(20, 340);
    durability.setCharacterSize(16);
    durability.setFillColor(standardColor);

    description.setFont(turretClassic);
    description.setPosition(20, 400);
    description.setCharacterSize(16);
    description.setFillColor(standardColor);
}



void SpecificationsPanel::interact(const int index)
{
    buildingInfo = t1::bc::buildingsInfoTable[index];

    title.setString(buildingInfo.buildingTitle);

    std::ostringstream strDurability;
    strDurability << buildingInfo.durability;
    sf::String durb = strDurability.str();
    durability.setString(L"прочность " + durb);

    for (auto& resI : resInfo)
    {
        resI.second.update(buildingInfo.costToBuild.allResources[resI.first]);
    }

    description.setString(buildingInfo.description);
}


void SpecificationsPanel::draw(sf::RenderWindow& window)
{
    this->drawSubWindowBase(window);
    title.setPosition(40, position.y + 10);
	window.draw(title);

    unsigned int posY = position.y + 30;
    for (auto& resI : resInfo)
    {
        if (resI.second.getQuantity() != 0)
        {
            resI.second.draw(window, position.x + 16, posY);
            posY += 20;
        }
    }
   
    if(buildingInfo.durability != 0)
    {
        durability.setPosition(10, posY);
        window.draw(durability);
        posY += 20;
    }

    description.setPosition(10, posY);
	window.draw(description);
}

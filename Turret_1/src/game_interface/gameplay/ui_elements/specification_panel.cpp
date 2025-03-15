
#include <string>
#include <sstream>

#include "specification_panel.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/pre-settings/pre-settings.h"


BuildingInfo SpecificationPanel::nullInfo = { L" ", 0, 0, {0, 0, 0, 0, 0, 0}, sf::IntRect({0, 0}, {0, 0}), L" " };

SpecificationPanel::SpecificationPanel() : UIWindow(sf::Vector2i(340, 400))
{
    resInfo.emplace(ResType::STONE, ResInfo(ResType::STONE, 0));
    resInfo.emplace(ResType::IRON, ResInfo(ResType::IRON, 0));
    resInfo.emplace(ResType::COPPER, ResInfo(ResType::COPPER, 0));
    resInfo.emplace(ResType::SILICON, ResInfo(ResType::SILICON, 0));
    resInfo.emplace(ResType::COAL, ResInfo(ResType::COAL, 0));
    resInfo.emplace(ResType::SULFUR, ResInfo(ResType::SULFUR, 0));
    this->prepareInterfaceSprites();
    isVisible = false;
}


void SpecificationPanel::prepareInterfaceSprites()
{
    title.setFont(turretClassic);
    title.setPosition(sf::Vector2f(40, 320));
    title.setCharacterSize(16);
    title.setFillColor(standardColor);

    durability.setFont(turretClassic);
    durability.setPosition(sf::Vector2f(20, 340));
    durability.setCharacterSize(16);
    durability.setFillColor(standardColor);

    description.setFont(turretClassic);
    description.setPosition(sf::Vector2f(20, 400));
    description.setCharacterSize(16);
    description.setFillColor(standardColor);
}



void SpecificationPanel::interact(const BuildingType index, const BuildingsPre& buildingsPre)
{
    if (!isVisible)
        return;
    buildingInfo = t1::bc::buildingsInfoTable[index];
    title.setString(buildingInfo.buildingTitle);

    std::ostringstream strDurability;
    strDurability << static_cast<int16_t>(static_cast<float>(buildingInfo.durability) * buildingsPre.maxDurabilityModifier);
    sf::String durb = strDurability.str();
    durability.setString(L"прочность " + durb);

    for (auto& [type, info] : resInfo)
    {
        const uint32_t price = buildingInfo.costToBuild.allResources[type];
        const uint32_t priceModified = static_cast<uint32_t>(static_cast<float>(price) * buildingsPre.expensesModifier);
        info.update(priceModified);
    }

    description.setString(buildingInfo.description);
}


void SpecificationPanel::relocate(const sf::Vector2i windowSize)
{
    relocateCentral(windowSize);
}


void SpecificationPanel::draw(sf::RenderWindow& window)
{
    if (!isVisible)
        return;
    drawBase(window);
    title.setPosition(sf::Vector2f(position.x + 16, position.y + 10));
    window.draw(title);

    unsigned int posX = position.x + 16;
    unsigned int posY = position.y + 30;
    for (auto& [type, info] : resInfo)
    {
        if (info.getQuantity() != 0)
        {
            info.draw(window, posX, posY);
            posY += 20;
        }
    }
    
    if(buildingInfo.durability != 0)
    {
        durability.setPosition(sf::Vector2f(position.x + 10, posY));
        window.draw(durability);
        posY += 20;
    }

    description.setPosition(sf::Vector2f(position.x + 10, posY));
    window.draw(description);
}

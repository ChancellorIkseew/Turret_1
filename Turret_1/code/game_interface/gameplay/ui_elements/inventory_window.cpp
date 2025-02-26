
#include "inventory_window.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/building.h"
#include "t1_system/input/input_handler.h"


InventoryWindow::InventoryWindow() : UIPlate(sf::Vector2u(225, 120), sf::Vector2u(0, 0))
{
    isVisible = false;

    resInfo.emplace(ResType::STONE, ResInfo(ResType::STONE, 0));
    resInfo.emplace(ResType::IRON, ResInfo(ResType::IRON, 0));
    resInfo.emplace(ResType::COPPER, ResInfo(ResType::COPPER, 0));
    resInfo.emplace(ResType::SILICON, ResInfo(ResType::SILICON, 0));
    resInfo.emplace(ResType::COAL, ResInfo(ResType::COAL, 0));
    resInfo.emplace(ResType::SULFUR, ResInfo(ResType::SULFUR, 0));
}
void InventoryWindow::prepareInterfaceSprites() { }


void InventoryWindow::interact(const sf::Vector2f& mouseMapCoord, Team* team, const BuildingsMap& buildingsMap)
{
    TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);
    if (InputHandler::jactive(t1::BindName::LMB) && !buildingsMap.isVoidBuilding(selectedTile))
    {
        isVisible = !isVisible;
    }
    if (!isVisible || !buildingsMap.buildingExists(selectedTile))
        return;

    for (auto& info : resInfo)
    {
        int amount = 0;
        for (auto& res : buildingsMap.getInventory(selectedTile))
        {
            if (info.first == res.type)
            {
                amount = res.quantity;
                break;
            }
        }
        info.second.update(amount);
    }

    relocateToCoursor();
}


void InventoryWindow::relocateToCoursor()
{
    const sf::Vector2i mouseCoord = InputHandler::getMouseCoord();
    position.x = mouseCoord.x;
    position.y = mouseCoord.y;
}


void InventoryWindow::draw(sf::RenderWindow& window)
{
    if (!isVisible)
        return;
    drawBase(window);
    unsigned int posX = position.x + 16;
    unsigned int posY = position.y + 30;
    for (auto& info : resInfo)
    {
        if (info.second.getQuantity() != 0)
        {
            info.second.draw(window, posX, posY);
            posY += 20;
        }

        if (posY >= position.y + 110)
        {
            posY = position.y + 30;
            posX += 70;
        }
    }
}

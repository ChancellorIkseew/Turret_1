
#include "inventory_window.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"


InventoryWindow::InventoryWindow() : UIPlate(sf::Vector2u(225, 120), sf::Vector2u(0, 0))
{
    isVisible = false;

    resInfo.emplace(RES_STONE, ResInfo(RES_STONE, 0));
    resInfo.emplace(RES_IRON, ResInfo(RES_IRON, 0));
    resInfo.emplace(RES_COPPER, ResInfo(RES_COPPER, 0));
    resInfo.emplace(RES_SILICON, ResInfo(RES_SILICON, 0));
    resInfo.emplace(RES_COAL, ResInfo(RES_COAL, 0));
    resInfo.emplace(RES_SULFUR, ResInfo(RES_SULFUR, 0));
}
void InventoryWindow::prepareInterfaceSprites() { }


void InventoryWindow::interact(const sf::Vector2f& mouseMapCoord, Team* const team)
{
    TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);
    if (InputHandler::jactive(t1::BindName::LMB) && !BuildingsMap::isVoidBuilding(selectedTile))
    {
        isVisible = !isVisible;
    }
    if (!isVisible || !BuildingsMap::buildingExists(selectedTile))
        return;

    for (auto& info : resInfo)
    {
        int amount = 0;
        for (auto& res : BuildingsMap::getInventory(selectedTile))
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

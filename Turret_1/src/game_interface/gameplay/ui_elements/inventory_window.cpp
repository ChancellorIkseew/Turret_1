
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
    resInfo.emplace(ResType::AC_SHELLS, ResInfo(ResType::AC_SHELLS, 0));
    resInfo.emplace(ResType::HEAVY_SHELLS, ResInfo(ResType::HEAVY_SHELLS, 0));
    resInfo.emplace(ResType::ROCKET, ResInfo(ResType::ROCKET, 0));
    resInfo.emplace(ResType::RAIL_SHELLS, ResInfo(ResType::RAIL_SHELLS, 0));
}


void InventoryWindow::interact(Team* team, const BuildingsMap& buildingsMap)
{
    const sf::Vector2f mouse = InputHandler::getMouseMapCoord();
    const TileCoord newTile = t1::be::tile(mouse.x, mouse.y);
    if (InputHandler::jactive(t1::BindName::LMB))
    {
        isVisible = !isVisible;
        relocateToCoursor();
    }
    if (newTile.x != targetedTile.x || newTile.y != targetedTile.y)
    {
        targetedTile = newTile;
        isVisible = false;
    }
    if (buildingsMap.isVoidBuilding(targetedTile) || buildingsMap.getTeam(targetedTile) != team)
        isVisible = false;
    if (!isVisible)
        return;

    for (auto& [type, info] : resInfo)
    {
        int amount = 0;
        for (auto& res : buildingsMap.getInventory(targetedTile))
        {
            if (type == res.type)
            {
                amount = res.quantity;
                break;
            }
        }
        info.update(amount);
    }
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

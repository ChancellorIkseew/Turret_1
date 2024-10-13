
#include "resources_panel.h"

#include "sub_windows_util/fonts.h"
#include "sub_windows_util/res_info.h"

#include "map_structures/resources/resources.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/team/team.h"


ResourcesPanel::ResourcesPanel() : SubWindow('s', 134, 219, 600, 600)
{
    stoneInfo.setResType(RES_STONE);
    ironInfo.setResType(RES_IRON);
    copperInfo.setResType(RES_COPPER);
    siliconInfo.setResType(RES_SILICON);
    coalInfo.setResType(RES_COAL);
    sulfurInfo.setResType(RES_SULFUR);

    this->prepareInterfaceSprites();
    this->relocate(1200, 1200);
}


void ResourcesPanel::prepareInterfaceSprites()
{
    
}


void ResourcesPanel::interact(Team& team)
{
    mutex.lock();
    t1::res::AllResources balance = team.getBalance().balance;
    stoneInfo.update(balance.stone);
    ironInfo.update(balance.iron);
    copperInfo.update(balance.copper);
    siliconInfo.update(balance.silicon);
    coalInfo.update(balance.coal);
    sulfurInfo.update(balance.sulfur);
    mutex.unlock();
}


void ResourcesPanel::relocate(int windowSizeX, int windowSizeY)
{
    positionX = windowSizeX - sizeX;
    positionY = windowSizeY - 450;
}


void ResourcesPanel::draw(sf::RenderWindow &window)
{
    this->drawSubWindowBase(window);
    mutex.lock();
    stoneInfo.draw(window, positionX+16, positionY+16);
    ironInfo.draw(window, positionX + 16, positionY + 46);
    copperInfo.draw(window, positionX + 16, positionY + 76);
    siliconInfo.draw(window, positionX + 16, positionY + 106);
    coalInfo.draw(window, positionX + 16, positionY + 136);
    sulfurInfo.draw(window, positionX + 16, positionY + 166);
    mutex.unlock();
}

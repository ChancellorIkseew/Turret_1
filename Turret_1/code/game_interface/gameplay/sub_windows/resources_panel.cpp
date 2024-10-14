
#include "resources_panel.h"

#include "sub_windows_util/fonts.h"
#include "sub_windows_util/res_info.h"

#include "map_structures/resources/resources.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/team/team.h"


ResourcesPanel::ResourcesPanel() : SubWindow('s', sf::Vector2u(134, 219), sf::Vector2u(600, 600))
{
    stoneInfo.setResType(RES_STONE);
    ironInfo.setResType(RES_IRON);
    copperInfo.setResType(RES_COPPER);
    siliconInfo.setResType(RES_SILICON);
    coalInfo.setResType(RES_COAL);
    sulfurInfo.setResType(RES_SULFUR);

    this->prepareInterfaceSprites();
    this->relocate({ 0, 0 });
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


void ResourcesPanel::relocate(const sf::Vector2u windowSize)
{
    position.x = windowSize.x - size.x;
    position.y = windowSize.y - 450;
}


void ResourcesPanel::draw(sf::RenderWindow &window)
{
    this->drawSubWindowBase(window);
    mutex.lock();
    stoneInfo.draw(window, position.x +16, position.y +16);
    ironInfo.draw(window, position.x + 16, position.y + 46);
    copperInfo.draw(window, position.x + 16, position.y + 76);
    siliconInfo.draw(window, position.x + 16, position.y + 106);
    coalInfo.draw(window, position.x + 16, position.y + 136);
    sulfurInfo.draw(window, position.x + 16, position.y + 166);
    mutex.unlock();
}

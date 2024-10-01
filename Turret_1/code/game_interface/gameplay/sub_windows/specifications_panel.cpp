
#include <string>
#include <sstream>
#include <SFML\Graphics.hpp>

#include "specifications_panel.h"

#include "sub_windows_util/fonts.h"
#include "sub_windows_util/res_info.h"
#include "map_structures/resources/res_enum.h"


BuildingInfo SpecificationsPanel::nullInfo = { L" ", 0, 0, {0, 0, 0, 0, 0, 0}, L" " };

SpecificationsPanel::SpecificationsPanel() : SubWindow('s', 260, 400, 0, 310)
{
    stoneInfo.setResType(RES_STONE);
    ironInfo.setResType(RES_IRON);
    copperInfo.setResType(RES_COPPER);
    siliconInfo.setResType(RES_SILICON);
    coalInfo.setResType(RES_COAL);
    sulfurInfo.setResType(RES_SULFUR);

    this->prepareInterfaceSprites();
}


void SpecificationsPanel::prepareInterfaceSprites()
{
	titleText.setFont(turretClassic);						//Text_title
    titleText.setPosition(40, 320);
    titleText.setCharacterSize(16);
    titleText.setFillColor(sf::Color(68, 52, 52));
	
    durabilityText.setFont(turretClassic);					//Text_durability
    durabilityText.setPosition(20, 340);
    durabilityText.setCharacterSize(16);
    durabilityText.setFillColor(sf::Color(68, 52, 52));

    descriptionText.setFont(turretClassic);					//Text_description
    descriptionText.setPosition(20, 400);
    descriptionText.setCharacterSize(16);
    descriptionText.setFillColor(sf::Color(68, 52, 52));
}



void SpecificationsPanel::interact(const int index)
{
    buildingInfo = t1::bc::buildingsInfoTable[index];

    titleText.setString(buildingInfo.buildingTitle);  //Title

    std::ostringstream strDurability;                               //Durability
    strDurability << buildingInfo.durability;
    sf::String durb = strDurability.str();
    durabilityText.setString(L"прочность " + durb);

    stoneInfo.update(buildingInfo.costToBuild.stoneQuant);
    ironInfo.update(buildingInfo.costToBuild.ironQuant);
    copperInfo.update(buildingInfo.costToBuild.copperQuant);
    siliconInfo.update(buildingInfo.costToBuild.siliconQuant);
    coalInfo.update(buildingInfo.costToBuild.coalQuant);
    sulfurInfo.update(buildingInfo.costToBuild.sulfurQuant);
    
    descriptionText.setString(buildingInfo.description);  //Description
}



void SpecificationsPanel::relocate(int windowSizeX, int windowSizeY)
{
	
}



void SpecificationsPanel::draw(sf::RenderWindow& window)
{
    this->drawSubWindowBase(window);
	
	window.draw(titleText);

    int deltaY = 340;

	if(buildingInfo.costToBuild.stoneQuant != 0)
    {
        stoneInfo.draw(window, 20, deltaY);
        deltaY = deltaY + 20;
	}
    
    if(buildingInfo.costToBuild.ironQuant != 0)
    {
        ironInfo.draw(window, 20, deltaY);
        deltaY = deltaY + 20;
	}
    
    if(buildingInfo.costToBuild.copperQuant != 0)
    {
        copperInfo.draw(window, 20, deltaY);
        deltaY = deltaY + 20;
	}
    
    if(buildingInfo.costToBuild.siliconQuant != 0)
    {
        siliconInfo.draw(window, 20, deltaY);
        deltaY = deltaY + 20;
	}
    
    if(buildingInfo.costToBuild.coalQuant != 0)
    {
        coalInfo.draw(window, 20, deltaY);
        deltaY = deltaY + 20;
	}
    
    if(buildingInfo.costToBuild.sulfurQuant != 0)
    {
        sulfurInfo.draw(window, 20, deltaY);
        deltaY = deltaY + 20;
	}
	
    if(buildingInfo.durability != 0)
    {
        durabilityText.setPosition(10, deltaY);
        window.draw(durabilityText);
        deltaY = deltaY + 20;
    }

    descriptionText.setPosition(10, deltaY);
	window.draw(descriptionText);
}

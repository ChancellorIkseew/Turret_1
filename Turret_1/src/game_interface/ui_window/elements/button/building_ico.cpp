
#include "building_ico.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"
#include "content/texturepacks.h"

using Info = BuildingsInfoTable;

BuildingIco::BuildingIco(const BuildingType buildingType, const sf::Vector2i position) :
	position(position), buildingType(buildingType)
{
	this->icoRect = Info::at(buildingType).icoRect;
	scale = 1.0f / sqrt(Info::at(buildingType).size);
	ico.setTexture(texture);
}

BuildingIco::BuildingIco(const BuildingType buildingType) :
	buildingType(buildingType)
{
	this->icoRect = Info::at(buildingType).icoRect;
	scale = 1.0f / sqrt(Info::at(buildingType).size);
	ico.setTexture(texture);
}


bool BuildingIco::select() const
{
	sf::Vector2i mouseCoord = InputHandler::getMouseCoord();
	return position.x <= mouseCoord.x && (position.x + 32) >= mouseCoord.x &&
		position.y <= mouseCoord.y && (position.y + 32) >= mouseCoord.y;
}

bool BuildingIco::press()
{
	if (!select() || !(InputHandler::jactive(t1::BindName::LMB) || InputHandler::active(t1::BindName::Pipette)))
		return false;
	t1::system::sleep(150); // Unable to use "jactive(t1::BindName::Pipette)", because it is already used in BuildingPanel.
	return true;
}

BuildingType BuildingIco::getBuildingType() const
{
	return buildingType;
}

void BuildingIco::setPosition(const sf::Vector2i position)
{
	this->position = position;
}

void BuildingIco::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	position -= this->ownerPosition;
	this->ownerPosition = ownerPosition;
	position += this->ownerPosition;
}

void BuildingIco::draw(sf::RenderWindow& window)
{
	ico.setTextureRect(icoRect);
	ico.setScale(sf::Vector2f(scale, scale));
	ico.setPosition(sf::Vector2f(position.x, position.y));
	window.draw(ico);
}

void BuildingIco::prepareSprites()
{
	image.loadFromFile(Texturepacks::findImage("buildings_ico.bmp"));
	image.createMaskFromColor(sf::Color(0, 255, 0));
	texture.loadFromImage(image);
}


#include "building_ico.h"
#include "t1_system/sleep.h"
#include "t1_system/system.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/buildings/building/buildings_info.h"


BuildingIco::BuildingIco(const uint16_t buildingType, const sf::Vector2u position)
{
	this->position = position;
	this->buildingType = buildingType;
	this->icoRect = t1::bc::buildingsInfoTable[buildingType].icoRect;
	scale = 1.0f / sqrt(t1::bc::buildingsInfoTable[buildingType].size);

	ico.setTexture(texture);
	ico.setOrigin(0.0f, 0.0f);
}

BuildingIco::BuildingIco(const uint16_t buildingType)
{
	position = sf::Vector2u(0, 0);
	this->buildingType = buildingType;
	this->icoRect = t1::bc::buildingsInfoTable[buildingType].icoRect;
	scale = 1.0f / sqrt(t1::bc::buildingsInfoTable[buildingType].size);

	ico.setTexture(texture);
	ico.setOrigin(0.0f, 0.0f);
}


bool BuildingIco::select(const sf::Vector2i& mouseCoord) const
{
	return position.x <= mouseCoord.x && (position.x + 32) >= mouseCoord.x &&
		position.y <= mouseCoord.y && (position.y + 32) >= mouseCoord.y;
}

bool BuildingIco::press(const sf::Vector2i& mouseCoord)
{
	if (select(mouseCoord) && LMB_Pressed)
	{
		t1::system::sleep(150);
		return true;
	}
	return false;
}

uint16_t BuildingIco::getBuildingType() const
{
	return buildingType;
}

void BuildingIco::setPosition(const sf::Vector2u position)
{
	this->position = position;
}

void BuildingIco::relocateWithOwner(const sf::Vector2u ownerPosition)
{
	position -= this->ownerPosition;
	this->ownerPosition = ownerPosition;
	position += this->ownerPosition;
}

void BuildingIco::draw(sf::RenderWindow& window)
{
	ico.setTextureRect(icoRect);
	ico.setScale(scale, scale);
	ico.setPosition(position.x, position.y);
	window.draw(ico);
}

void BuildingIco::prepareSprites()
{
	image.loadFromFile("images/buildings_ico.bmp");
	image.createMaskFromColor(sf::Color(0, 255, 0));
	texture.loadFromImage(image);
}

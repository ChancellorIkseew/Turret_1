
#include <sstream>
#include <SFML\Graphics.hpp>

#include "res_info.h"

#include "fonts.h"
#include "map_structures/resources/res_enum.h"

ResInfo::ResInfo(int resType, int resQuantity)
{
	this->resType = resType;
	this->resQuantity = resQuantity;

	resQuantText.setFont(turretClassic);					//Text_stone_resQuantityility
	resQuantText.setCharacterSize(16);
	resQuantText.setFillColor(sf::Color(68, 52, 52));
}

ResInfo::ResInfo()
{
	resType = 0;
	resQuantity = 0;

	resQuantText.setFont(turretClassic);					//Text_stone_resQuantityility
	resQuantText.setCharacterSize(16);
	resQuantText.setFillColor(sf::Color(68, 52, 52));
}



void ResInfo::prepareSprites()
{
	resIcoImage.loadFromFile("images/resources_icons.bmp");				//Resources_icons
	resIcoImage.createMaskFromColor(sf::Color(0, 255, 0));
	resIcoTexture.loadFromImage(resIcoImage);
	resIcoSprite.setTexture(resIcoTexture);

	
}



void ResInfo::update(int qurrentQuantity)
{
	resQuantity = qurrentQuantity;
	
	std::ostringstream strQuant;		//Resourses_panel
	strQuant << resQuantity;
	resQuantText.setString(strQuant.str());
}



void ResInfo::draw(sf::RenderWindow& window, int positionX, int positionY)
{
	if (true) // there was "resQuantity > 0"
	{
		switch (resType)
		{
		case RES_STONE:
			resIcoSprite.setTextureRect(sf::IntRect(0, 0, 18, 18));
			break;

		case RES_IRON:
			resIcoSprite.setTextureRect(sf::IntRect(18, 0, 18, 18));
			break;

		case RES_COPPER:
			resIcoSprite.setTextureRect(sf::IntRect(36, 0, 18, 18));
			break;

		case RES_SILICON:
			resIcoSprite.setTextureRect(sf::IntRect(54, 0, 18, 18));
			break;

		case RES_COAL:
			resIcoSprite.setTextureRect(sf::IntRect(72, 0, 18, 18));
			break;

		case RES_SULFUR:
			resIcoSprite.setTextureRect(sf::IntRect(90, 0, 18, 18));
			break;

		case RES_AC_SHELLS:
			resIcoSprite.setTextureRect(sf::IntRect(108, 0, 18, 18));
			break;

		case RES_ROCKET:
			resIcoSprite.setTextureRect(sf::IntRect(126, 0, 18, 18));
			break;

		default:
			resIcoSprite.setTextureRect(sf::IntRect(0, 0, 18, 18));
			break;
		}

		resIcoSprite.setPosition(positionX, positionY);
		resQuantText.setPosition(positionX + 25, positionY);

		window.draw(resIcoSprite);
		window.draw(resQuantText);
	}
}



void ResInfo::setResType(int resType)
{
	this->resType = resType;
}

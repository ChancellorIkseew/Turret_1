
#include <sstream>
#include <SFML\Graphics.hpp>

#include "res_info.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/resources/res_enum.h"

ResInfo::ResInfo(const ResType resType, const int resQuantity) :
	resType(resType), resQuantity(resQuantity)
{
	resQuantText.setFont(turretClassic);					//Text_resQuantityility
	resQuantText.setCharacterSize(16);
	resQuantText.setFillColor(standardColor);
}

ResInfo::ResInfo()
{
	resQuantText.setFont(turretClassic);					//Texte_resQuantityility
	resQuantText.setCharacterSize(16);
	resQuantText.setFillColor(standardColor);
}



void ResInfo::prepareSprites()
{
	resIcoImage.loadFromFile("images/resources_icons.bmp");	//Resources_icons
	resIcoImage.createMaskFromColor(sf::Color(0, 255, 0));
	resIcoTexture.loadFromImage(resIcoImage);
	resIcoSprite.setTexture(resIcoTexture);
}



void ResInfo::update(const int qurrentQuantity)
{
	resQuantity = qurrentQuantity;
	
	std::ostringstream strQuant;		//Resourses_panel
	strQuant << resQuantity;
	resQuantText.setString(strQuant.str());
}

int ResInfo::getQuantity() const { return resQuantity; }



void ResInfo::draw(sf::RenderWindow& window, int positionX, int positionY)
{
	if (true) // there was "resQuantity > 0"
	{
		switch (resType)
		{
		case ResType::STONE:
			resIcoSprite.setTextureRect(sf::IntRect(0, 0, 18, 18));
			break;

		case ResType::IRON:
			resIcoSprite.setTextureRect(sf::IntRect(18, 0, 18, 18));
			break;

		case ResType::COPPER:
			resIcoSprite.setTextureRect(sf::IntRect(36, 0, 18, 18));
			break;

		case ResType::SILICON:
			resIcoSprite.setTextureRect(sf::IntRect(54, 0, 18, 18));
			break;

		case ResType::COAL:
			resIcoSprite.setTextureRect(sf::IntRect(72, 0, 18, 18));
			break;

		case ResType::SULFUR:
			resIcoSprite.setTextureRect(sf::IntRect(90, 0, 18, 18));
			break;

		case ResType::AC_SHELLS:
			resIcoSprite.setTextureRect(sf::IntRect(108, 0, 18, 18));
			break;

		case ResType::ROCKET:
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



void ResInfo::setResType(const ResType resType)
{
	this->resType = resType;
}

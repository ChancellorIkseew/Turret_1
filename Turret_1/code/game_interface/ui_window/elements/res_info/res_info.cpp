
#include <sstream>
#include <SFML\Graphics.hpp>

#include "res_info.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/resources/res_enum.h"

ResInfo::ResInfo(const ResType resType, const int resQuantity) :
	resType(resType), resQuantity(resQuantity)
{
	ico.setResType(resType);
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
		ico.setPosition(sf::Vector2u(positionX, positionY));
		resQuantText.setPosition(positionX + 25, positionY);

		ico.draw(window);
		window.draw(resQuantText);
	}
}



void ResInfo::setResType(const ResType resType)
{
	this->resType = resType;
}

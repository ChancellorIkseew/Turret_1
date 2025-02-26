#pragma once
#ifndef RES_INFO_H
#define RES_INDO_H

#include <SFML\Graphics.hpp>
#include "map_structures/resources/res_enum.h"
#include "game_interface/ui_window/elements/res_ico/res_ico.h"


class ResInfo
{
private:
	ResIco ico;
	sf::Text resQuantText;

	ResType resType = ResType::NO_RESOURCES;
	int resQuantity = 0;

public:
	ResInfo(const ResType resType, const int resQuantity);
	ResInfo();
	~ResInfo() = default;

	void setResType(const ResType resType);
	void update(const int qurrentQuantity);
	int getQuantity() const;

	void draw(sf::RenderWindow& window, int positionX, int powitionY);

};


#endif // RES_INFO_H

#pragma once
#ifndef RES_INFO_H
#define RES_INDO_H

#include <SFML\Graphics.hpp>
#include "map_structures/resources/res_enum.h"
#include "game_interface/ui_window/elements/res_ico/res_ico.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"


class ResInfo
{
private:
	ResIco ico;
	sf::Text resQuantText = sf::Text(turretClassic);

	ResType resType = ResType::NO_RESOURCES;
	uint32_t resQuantity = 0;

public:
	ResInfo(const ResType resType, const uint32_t resQuantity);
	ResInfo();
	~ResInfo() = default;

	void setResType(const ResType resType);
	void update(const uint32_t qurrentQuantity);
	uint32_t getQuantity() const { return resQuantity; }

	void draw(sf::RenderWindow& window, int positionX, int positionY);

};


#endif // RES_INFO_H

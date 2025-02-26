#pragma once
#ifndef RES_INFO_H
#define RES_INDO_H

#include <SFML\Graphics.hpp>
#include "map_structures/resources/res_enum.h"


class ResInfo
{
private:
	static inline sf::Image resIcoImage;
	static inline sf::Texture resIcoTexture;
	static inline sf::Sprite resIcoSprite;

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

	static void prepareSprites();
	void draw(sf::RenderWindow& window, int positionX, int powitionY);

};


#endif // RES_INFO_H

#pragma once
#ifndef RES_INFO_H
#define RES_INDO_H

#include <SFML\Graphics.hpp>


class ResInfo
{
private:
	static inline sf::Image resIcoImage;
	static inline sf::Texture resIcoTexture;
	static inline sf::Sprite resIcoSprite;

	sf::Text resQuantText;

	int resType;
	int resQuantity;

public:
	ResInfo(int resType, int resQuantity);
	ResInfo();
	~ResInfo() = default;

	void setResType(int resType);
	void update(int qurrentQuantity);

	static void prepareSprites();
	void draw(sf::RenderWindow& window, int positionX, int powitionY);

};


#endif // RES_INFO_H

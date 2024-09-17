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

	int type;
	int quant;

	//int subWinPositionX;
	//int subWinPositionY;

public:

	ResInfo(int v_type, int v_quant);
	ResInfo();
	~ResInfo() = default;

	void setResType(int v_type);
	void update(int qurrentQuantity);

	static void prepareSprites();
	void draw(sf::RenderWindow& window, int positionX, int powitionY);

};


#endif // RES_INFO_H

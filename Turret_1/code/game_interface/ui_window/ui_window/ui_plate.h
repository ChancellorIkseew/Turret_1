#pragma once
#ifndef UI_PLATE
#define UI_PLATE

#include <SFML/Graphics.hpp>


class UIPlate
{
private:
	static void prepareWindowBaseSprites();

protected:
	sf::Vector2u size;
	sf::Vector2u position;

	bool isSelected;
	bool isVisible;

	//Base
	static inline sf::Texture baseTexture;
	static inline sf::Sprite base;

	//Borders
	static inline sf::Texture upperBorderTexture;
	static inline sf::Texture lowerBorderTexture;
	static inline sf::Texture leftBorderTexture;
	static inline sf::Texture rightBorderTexture;
	static inline sf::Sprite upperBorder;
	static inline sf::Sprite lowerBorder;
	static inline sf::Sprite leftBorder;
	static inline sf::Sprite rightBorder;

	//Corners
	static inline sf::Texture upperLeftCornerTexture;
	static inline sf::Texture lowerLeftCornerTexture;
	static inline sf::Texture upperRightCornerTexture;
	static inline sf::Texture lowerRightCornerTexture;
	static inline sf::Sprite upperLeftCorner;
	static inline sf::Sprite lowerLeftCorner;
	static inline sf::Sprite upperRightCorner;
	static inline sf::Sprite lowerRightCorner;

	void drawBase(sf::RenderWindow& window) const;

public:
	UIPlate(const sf::Vector2u size, const sf::Vector2u position);
	virtual ~UIPlate() = default;

	void setVisible(const bool value);
	virtual bool containsCoursor(const sf::Vector2i& mouseCoord) const;

	static void init();
	virtual void prepareInterfaceSprites() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

};

#endif // UI_PLATE

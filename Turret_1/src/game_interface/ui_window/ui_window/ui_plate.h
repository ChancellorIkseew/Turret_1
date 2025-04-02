#pragma once
#ifndef UI_PLATE
#define UI_PLATE

#include <SFML/Graphics.hpp>


class UIPlate
{
private:
	//Base
	static inline sf::Texture baseTexture;

	//Borders
	static inline sf::Texture upperBorderTexture;
	static inline sf::Texture lowerBorderTexture;
	static inline sf::Texture leftBorderTexture;
	static inline sf::Texture rightBorderTexture;
	static inline sf::Sprite upperBorder = sf::Sprite(upperBorderTexture);
	static inline sf::Sprite lowerBorder = sf::Sprite(lowerBorderTexture);
	static inline sf::Sprite leftBorder = sf::Sprite(leftBorderTexture);
	static inline sf::Sprite rightBorder = sf::Sprite(rightBorderTexture);

	//Corners
	static inline sf::Texture upperLeftCornerTexture;
	static inline sf::Texture lowerLeftCornerTexture;
	static inline sf::Texture upperRightCornerTexture;
	static inline sf::Texture lowerRightCornerTexture;
	static inline sf::Sprite upperLeftCorner = sf::Sprite(upperLeftCornerTexture);
	static inline sf::Sprite lowerLeftCorner = sf::Sprite(lowerLeftCornerTexture);
	static inline sf::Sprite upperRightCorner = sf::Sprite(upperRightCornerTexture);
	static inline sf::Sprite lowerRightCorner = sf::Sprite(lowerRightCornerTexture);

	static void prepareWindowBaseSprites();

protected:
	static inline sf::Sprite base = sf::Sprite(baseTexture);
	sf::Vector2i size;
	sf::Vector2i position;
	bool isSelected = false;
	bool isVisible = true;

	void drawBase(sf::RenderWindow& window) const;

public:
	UIPlate(const sf::Vector2i size, const sf::Vector2i position);
	UIPlate(const sf::Vector2i size);
	virtual ~UIPlate() = default;

	void setVisible(const bool value);
	virtual bool containsCoursor() const;

	static void init();
	virtual void prepareInterfaceSprites() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

};

#endif // UI_PLATE

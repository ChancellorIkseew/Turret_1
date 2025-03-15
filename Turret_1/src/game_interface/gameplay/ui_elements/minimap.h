#pragma once
#ifndef MINIMAP_H
#define MINIMAP_H

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "map_structures/base_engine/base_engine.h"

class World;

class Minimap : public UIWindow
{
private:
	sf::Image mapImage;
	sf::Texture mapTexture;
	sf::Sprite map = sf::Sprite(mapTexture);

	TileCoord mapSize;

	Minimap(const Minimap&) = delete;
	Minimap& operator=(const Minimap&) = delete;
	void prepareInterfaceSprites() override final { /*Interface is being created in "initMapSize"*/ }

public:
	Minimap();
	~Minimap() = default;

	void initMapSize(const TileCoord mapSize);
	void interact(const World& world);
	void relocate(const sf::Vector2i windowSize) override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // MINIMAP_H

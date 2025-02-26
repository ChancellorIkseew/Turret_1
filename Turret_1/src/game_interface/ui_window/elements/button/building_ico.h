#pragma once
#ifndef T1_BUILDING_ICO_H
#define T1_BUILDING_ICO_H

#include <SFML/Graphics.hpp>
#include "map_structures/buildings/building/buildings_enum.h"


class BuildingIco
{
private:
    sf::Vector2u position;
    sf::Vector2u ownerPosition;

    static inline sf::Image image;
    static inline sf::Texture texture;
    sf::Sprite ico;

    BuildingType buildingType;
    sf::IntRect icoRect;
    float scale;

    bool select() const;

public:
    BuildingIco() = default;
    BuildingIco(const BuildingType buildingType, const sf::Vector2u position);
    BuildingIco(const BuildingType buildingType);
    ~BuildingIco() = default;
   
    bool press();
    BuildingType getBuildingType() const;

    void setPosition(const sf::Vector2u position);
    void relocateWithOwner(const sf::Vector2u ownerPosition);
    static void prepareSprites();
    void draw(sf::RenderWindow& window);

};

#endif // T1_BUILDING_ICO_H

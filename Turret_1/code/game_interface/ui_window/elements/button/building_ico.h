#pragma once
#ifndef T1_BUILDING_ICO_H
#define T1_BUILDING_ICO_H

#include <SFML/Graphics.hpp>


class BuildingIco
{
private:
    sf::Vector2u position;
    sf::Vector2u ownerPosition;

    static inline sf::Image image;
    static inline sf::Texture texture;
    sf::Sprite ico;

    uint16_t buildingType;
    sf::IntRect icoRect;
    float scale;

    bool select(const sf::Vector2i& mouseCoord) const;

public:
    BuildingIco() = default;
    BuildingIco(const uint16_t buildingType, const sf::Vector2u position);
    BuildingIco(const uint16_t buildingType);
    ~BuildingIco() = default;
   
    bool press(const sf::Vector2i& mouseCoord);

    void setPosition(const sf::Vector2u position);
    void relocateWithOwner(const sf::Vector2u ownerPosition);
    static void prepareSprites();
    void draw(sf::RenderWindow& window);

};

#endif // T1_BUILDING_ICO_H


#include "resource_unit.h"

#include "res_enum.h"

constexpr sf::Vector2f RES_UNIT_CENTRE(4.5f, 4.5f);
constexpr sf::Vector2i RES_UNIT_RECT(9, 9);

ResourceUnit::ResourceUnit(const ResType type, const char direction, const PixelCoord coord) :
	type(type), direction(direction), coord(coord) { }

ResourceUnit::ResourceUnit(const ResourceUnit& other) :
	type(other.type), direction(other.direction), coord(other.coord) { }


void ResourceUnit::save(cereal::BinaryOutputArchive& archive) const {
	archive(type, direction, coord);
}
void ResourceUnit::load(cereal::BinaryInputArchive& archive) {
	archive(type, direction, coord);
}


void ResourceUnit::prepareSprites()
{
	resourcesImage.loadFromFile("images/resources.bmp");			//Resources
	resourcesImage.createMaskFromColor(sf::Color(0, 255, 0));
	resourcesTexture.loadFromImage(resourcesImage);
	resourceSprite.setOrigin(RES_UNIT_CENTRE);
}


void ResourceUnit::draw(sf::RenderWindow& window, const TileCoord tile) const
{
	switch (type)
	{
	case ResType::STONE:
		resourceSprite.setTextureRect(sf::IntRect({ 9, 0 }, RES_UNIT_RECT));
		break;
	case ResType::IRON:
		resourceSprite.setTextureRect(sf::IntRect({ 18, 0 }, RES_UNIT_RECT));
		break;
	case ResType::COPPER:
		resourceSprite.setTextureRect(sf::IntRect({ 27, 0 }, RES_UNIT_RECT));
		break;
	case ResType::SILICON:
		resourceSprite.setTextureRect(sf::IntRect({ 36, 0 }, RES_UNIT_RECT));
		break;
	case ResType::COAL:
		resourceSprite.setTextureRect(sf::IntRect({ 45, 0 }, RES_UNIT_RECT));
		break;
	case ResType::SULFUR:
		resourceSprite.setTextureRect(sf::IntRect({ 54, 0 }, RES_UNIT_RECT));
		break;

	case ResType::AC_SHELLS:
		resourceSprite.setTextureRect(sf::IntRect({ 0, 18 }, RES_UNIT_RECT));
		break;
	case ResType::HEAVY_SHELLS:
		resourceSprite.setTextureRect(sf::IntRect({ 9, 18 }, RES_UNIT_RECT));
		break;
	case ResType::ROCKET:
		resourceSprite.setTextureRect(sf::IntRect({ 18, 18 }, RES_UNIT_RECT));
		break;

	default:
		resourceSprite.setTextureRect(sf::IntRect({ 0, 0 }, RES_UNIT_RECT));
		break;
	}

	resourceSprite.setPosition(sf::Vector2f(t1::be::pixelF(tile.x) + coord.x, t1::be::pixelF(tile.y) + coord.y));
	window.draw(resourceSprite);
}

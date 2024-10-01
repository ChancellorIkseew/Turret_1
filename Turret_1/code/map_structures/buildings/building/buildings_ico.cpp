
#include "buildings_ico.h"
#include "buildings_enum.h"

sf::Image t1::bc::buildingsIcoImage;
sf::Texture t1::bc::buildingsIcoTexture;


void t1::bc::initBuildingIco()
{
	buildingsIcoImage.loadFromFile("images/buildings.bmp");				//Building Base_texture for all buildings
	buildingsIcoImage.createMaskFromColor(sf::Color(0, 255, 0));
	buildingsIcoTexture.loadFromImage(buildingsIcoImage);
}

std::map<int, BuildingIco> t1::bc::buildingsIcoTable
{
	std::pair<int, BuildingIco>
	{ REMOVE, { { buildingsIcoTexture, sf::IntRect(32, 0, 16, 16) }, sf::IntRect(96, 288, 32, 32) } },

	{ STONE_WALL, { { buildingsIcoTexture, sf::IntRect(16, 0, 16, 16) }, sf::IntRect(0, 448, 32, 32) } },
	{ STEEL_WALL, { { buildingsIcoTexture, sf::IntRect(0, 0, 0, 0) }, sf::IntRect(0, 0, 0, 0) } },

	{ STONE_TOWER, { { buildingsIcoTexture, sf::IntRect(0, 0, 16, 16) }, sf::IntRect(0, 416, 32, 32) } },
	{ STEEL_TOWER, { { buildingsIcoTexture, sf::IntRect(0, 0, 0, 0) }, sf::IntRect(0, 0, 0, 0) } },
	
	{ STANDARD_CONVEYER, { { buildingsIcoTexture, sf::IntRect(0, 144, 16, 16) }, sf::IntRect(128, 96, 32, 32) } },
	{ SHIELDED_CONVEYER, { { buildingsIcoTexture, sf::IntRect(64, 144, 16, 16) }, sf::IntRect(160, 96, 32, 32) } },

	{ BRIDGE, { { buildingsIcoTexture, sf::IntRect(32, 64, 16, 16) }, sf::IntRect(0, 224, 32, 32) } },
	{ ROUTER, { { buildingsIcoTexture, sf::IntRect(32, 48, 16, 16) }, sf::IntRect(0, 256, 32, 32) } },
	{ SORTER, { { buildingsIcoTexture, sf::IntRect(0, 0, 0, 0) }, sf::IntRect(0, 0, 0, 0) } },

	{ SMALL_DRILL, { { buildingsIcoTexture, sf::IntRect(64, 0, 16, 16) }, sf::IntRect(32, 0, 32, 32) } },
	{ BIG_DRILL, { { buildingsIcoTexture, sf::IntRect(0, 80, 32, 32) }, sf::IntRect(64, 32, 64, 64) } },
	{ EFFECTIVE_DRILL, { { buildingsIcoTexture, sf::IntRect(0, 0, 0, 0) }, sf::IntRect(0, 0, 0, 0) } },
	{ REINFORCED_DRILL, { { buildingsIcoTexture, sf::IntRect(0, 0, 0, 0) }, sf::IntRect(0, 0, 0, 0) } },

	{ SHELL_FACTORY, { { buildingsIcoTexture, sf::IntRect(32, 112, 32, 32) }, sf::IntRect(0, 320, 64, 64) } },
	{ ROCKET_FACTORY, { { buildingsIcoTexture, sf::IntRect(96, 0, 48, 48) }, sf::IntRect(256, 384, 96, 96) } },

	{ AUTOCANNON_TURRET, { { buildingsIcoTexture, sf::IntRect(34, 18, 12, 20) }, sf::IntRect(34, 18, 12, 20) } },
	{ ROCKET_TURRET, { { buildingsIcoTexture, sf::IntRect(48, 16, 16, 18) }, sf::IntRect(48, 16, 16, 18) } },

	{ COAL_GENERATOR, { { buildingsIcoTexture, sf::IntRect(0, 112, 32, 32) }, sf::IntRect(0, 0, 0, 0) } },
};
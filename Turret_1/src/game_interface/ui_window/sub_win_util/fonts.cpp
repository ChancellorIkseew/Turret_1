
#include "fonts.h"

sf::Font turretClassic;
sf::Font nunito;
sf::Font spectral;

sf::Color standardColor(68, 52, 52);
sf::Color darkGray(68, 52, 52);
sf::Color darkRed(180, 52, 52);
sf::Color lightGreen(40, 128, 40);

sf::Color whiteTransparent(255, 255, 255, 200);
sf::Color darkRedTransparent(180, 52, 52, 200);

void initFonts()
{
	turretClassic.loadFromFile("fonts/turret_classic_full.ttf");
	nunito.loadFromFile("fonts/ofont.ru_Nunito.ttf");
	spectral.loadFromFile("fonts/ofont.ru_Spectral.ttf");
}
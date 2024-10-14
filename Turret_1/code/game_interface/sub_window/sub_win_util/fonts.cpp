
#include "fonts.h"

sf::Font turretClassic;
sf::Font nunito;
sf::Font spectral;

void initFonts()
{
	turretClassic.loadFromFile("fonts/turret_classic_full.ttf");
	nunito.loadFromFile("fonts/ofont.ru_Nunito.ttf");
	spectral.loadFromFile("fonts/ofont.ru_Spectral.ttf");
}
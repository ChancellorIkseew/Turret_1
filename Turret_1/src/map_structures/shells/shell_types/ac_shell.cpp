
#include "ac_shell.h"

constexpr float SPEED = 1.6f;
constexpr uint16_t MAX_LIFI_TIME = 200;

AutocannonShell::AutocannonShell(const PixelCoord coord, const float angleRad, Team* team) :
	Shell(coord, angleRad, team)
{
	restLifeTime = MAX_LIFI_TIME;
	lineMotion.x = sin(angleRad) * SPEED;
	lineMotion.y = cos(angleRad) * SPEED;
}


void AutocannonShell::draw(sf::RenderWindow& window)
{
	shellSprite.setTextureRect(sf::IntRect({ 0, 0 }, { 1, 2 }));
	shellSprite.setOrigin({ 0, 1 });
	shellSprite.setPosition({ coord.x, coord.y });
	shellSprite.setRotation(sf::radians(PI - angleRad));
	window.draw(shellSprite);
}

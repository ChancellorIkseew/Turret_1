
#include "ac_shell.h"

constexpr float SPEED = 1.6f;

AutocannonShell::AutocannonShell(PixelCoord coord, float angleRad, float angleDeg, Team* const team) :
	Shell(coord, angleRad, angleDeg, team)
{
	damage = 1;
	maxLifeTime = 200;
	lineMotion.x = sin(angleRad) * SPEED;
	lineMotion.y = cos(angleRad) * SPEED;
}


void AutocannonShell::draw(sf::RenderWindow& window)
{
	shellSprite.setTextureRect(sf::IntRect(0, 0, 1, 2));
	shellSprite.setOrigin(0, 1);
	shellSprite.setPosition(coord.x, coord.y);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}

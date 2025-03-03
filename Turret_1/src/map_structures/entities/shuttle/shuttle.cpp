#include "shuttle.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"
#include "t1_system/input/input_handler.h"

constexpr int TILE_RANGE = 20;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];
constexpr float MAX_SPEED = 2.2;

Shuttle::Shuttle(Team* const team) : Entity(team)
{
	durability = 270 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void Shuttle::motion(const BuildingsMap& buildingsMap)
{
	PixelCoord delta(0.0f, 0.0f);

	if (InputHandler::active(t1::BindName::Move_up))
		delta.y -= 1.0f;
	if (InputHandler::active(t1::BindName::Move_left))
		delta.x -= 1.0f;
	if (InputHandler::active(t1::BindName::Move_down))
		delta.y += 1.0f;
	if (InputHandler::active(t1::BindName::Move_right))
		delta.x += 1.0f;

	motionAngleRad = atan2f(delta.x, delta.y);
	motionAngleDeg = t1::be::radToDegree(motionAngleRad);
	
	coord.x += sin(motionAngleRad) * MAX_SPEED;
	coord.y += cos(motionAngleRad) * MAX_SPEED;
}


void Shuttle::shoot(const BuildingsMap& buildingsMap)
{
	Entity::reloadWeapon();
	//Entity::aim(SPYRAL_RANGE, PIXEL_RANGE);

	sf::Vector2f newAim;
	if (InputHandler::active(t1::BindName::LMB))
		newAim = InputHandler::getMouseMapCoord();
	aimCoord = PixelCoord(newAim.x, newAim.y);

	if (aimCoord.valid())
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 15.0f;
			float correctionY = sin(shootingAngleRad) * 15.0f;

			team->spawnShell(ShellType::HEAVY_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
			team->spawnShell(ShellType::HEAVY_SHELL, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad, shootingAngleDeg);
			reloadTimer = 30;
		}
	}
}


void Shuttle::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(0, 18, 43, 43));
	entitySprite.setOrigin(22, 22);

	if (aimCoord.valid())
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);

	if (durability > 150)    //Boss_energy_shield
	{
		shieldSprite.setPosition(coord.x, coord.y);
		window.draw(shieldSprite);
	}
}

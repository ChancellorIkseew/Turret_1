
#include "mob_controller.h"

#include <SFML/Graphics.hpp>
#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/team/team.h"


void MobController::shoot()
{
	PixelCoord newAim = INCORRECT_PIXEL_COORD;
	if (InputHandler::active(t1::BindName::Shoot))
	{
		const sf::Vector2f mouse = InputHandler::getMouseMapCoord();
		newAim = PixelCoord(mouse.x, mouse.y);
	}
	targetedEntity->setShootingAim(newAim);
}

void MobController::mine()
{

}

void MobController::move()
{
	PixelCoord delta(0.0f, 0.0f);

	if (InputHandler::active(t1::BindName::Move_up))
		delta.y -= 10.0f;
	if (InputHandler::active(t1::BindName::Move_left))
		delta.x -= 10.0f;
	if (InputHandler::active(t1::BindName::Move_down))
		delta.y += 10.0f;
	if (InputHandler::active(t1::BindName::Move_right))
		delta.x += 10.0f;

	PixelCoord current = targetedEntity->getCoord();
	targetedEntity->setDestCoord(current + delta);
}


void MobController::interact(const Team& player)
{
	captureEntity(player);
	if (targetedEntity == nullptr)
		return;
	move();
	shoot();
	mine();
}



void MobController::captureEntity(const Team& player)
{
	if (!InputHandler::active(t1::BindName::Control_unit))
		return;
	if (targetedEntity != nullptr)
	{
		targetedEntity->setDestCoord(INCORRECT_PIXEL_COORD);
		targetedEntity = nullptr;
		return;
	}

	const sf::Vector2f mouse = InputHandler::getMouseMapCoord();
	PixelCoord mouseC(mouse.x, mouse.y);

	const auto& entities = player.getEneities().getList();
	PixelCoord coord;
	for (auto& entity : entities)
	{
		coord = entity->getCoord();
		if (abs(mouseC.x - coord.x) < _HALF_TILE_ && abs(mouseC.y - coord.y) < _HALF_TILE_)
		{
			targetedEntity = entity.get();
			t1::system::sleep(150);
			return;
		}
	}
}


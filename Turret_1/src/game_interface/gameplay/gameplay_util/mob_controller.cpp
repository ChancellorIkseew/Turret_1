
#include "mob_controller.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/team/team.h"
#include "game_interface/gameplay/gameplay.h"


void MobController::shoot(const Gameplay& gameplay)
{
	const sf::Vector2f mouse = InputHandler::getMouseMapCoord();
	aimCoord.store(PixelCoord(mouse.x, mouse.y), std::memory_order_relaxed);

	const bool flag = InputHandler::active(t1::BindName::Shoot) && gameplay.noSubWindowSelected();
	shooting.store(flag, std::memory_order_relaxed);
}

void MobController::mine()
{

}

void MobController::move()
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

	motionVector.store(delta, std::memory_order_relaxed);
}


void MobController::interact(const Team& player, const Gameplay& gameplay)
{
	captureEntity(player);
	if (targetedEntity == nullptr)
		return;
	move();
	shoot(gameplay);
	mine();
}



void MobController::captureEntity(const Team& player)
{
	if (!InputHandler::active(t1::BindName::Control_unit))
		return;
	if (targetedEntity != nullptr)
	{
		targetedEntity->setControlType(preveousControlType);
		targetedEntity->setDestCoord(INCORRECT_TILE_COORD);
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
		if (t1::be::areCloser(mouseC, coord, static_cast<float>(_HALF_TILE_)))
		{
			targetedEntity = entity.get();
			preveousControlType = targetedEntity->getControlType();
			targetedEntity->setControlType(Control::HARD); 
			t1::system::sleep(150);
			return;
		}
	}
}


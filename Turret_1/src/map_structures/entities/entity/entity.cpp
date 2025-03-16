
#include "entity.h"

#include "map_structures/world/world.h"
#include "map_structures/team/team.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/entities/behavior/aiming.h"
#include "t1_system/events/events_handler.h"
#include "game_interface/gameplay/gameplay_util/mob_controller.h"


constexpr float BASIC_COLLISION_RADIUS = 30.0f;
constexpr float MAX_SPEED = 0.1; // temporary desision

Entity::Entity(Team* team) : team(team), reloadTimer(0) { }

void Entity::save(cereal::BinaryOutputArchive& archive) const {
	archive(coord, motionAngleRad, durability);
}
void Entity::load(cereal::BinaryInputArchive& archive) {
	archive(coord, motionAngleRad, durability);
}

void Entity::interact()
{
	reloadWeapon();

	if (control == Control::HARD)
	{
		moveByDirectControl(MobController::getMotionVector());
		aimCoord = MobController::getAimCoord();
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		if (MobController::shootingActive())
			shoot();
		return;
	}

	moveByOwnAI();
	shootByOwnAI();
}


void Entity::aim(const int spyralRange, const float pixelRange)
{
	if (control != Control::NONE)
		return;
	aimCoord = INCORRECT_PIXEL_COORD; // reset aim
	aimCoord = Aiming::aimOnEntity(*this, pixelRange, *world);
	if (aimCoord.valid())
		return;
	aimCoord = Aiming::aimOnBuilding(*this, spyralRange, world->getBuildingsMap());
}


void Entity::reloadWeapon()
{
	if (reloadTimer > 0)
		--reloadTimer;
}

void Entity::setTeam(Team* team) {
	this->team = team;
}
void Entity::setDurability(const int16_t durability) {
	this->durability = durability;
}
void Entity::setDamage(const int16_t damage) {
	durability -= damage;
}
void Entity::setDamage(const float damage) {
	durability -= static_cast<int16_t>(damage);
}

void Entity::setControlType(Control controlType) {
	control = controlType;
}
void Entity::setCoord(const PixelCoord coord) {
	this->coord = coord;
}
void Entity::setDestCoord(const TileCoord destCoord) {
	this->destCoord = destCoord;
}
void Entity::setShootingAim(const PixelCoord aimCoord) {
	this->aimCoord = aimCoord;
}

// visual
void Entity::prepareSprites()
{
	entityImage.loadFromFile("images/mobs.bmp");
	entityImage.createMaskFromColor(sf::Color(0, 255, 0));
	entityTexture.loadFromImage(entityImage);

	shieldImage.loadFromFile("images/shield.bmp");
	shieldImage.createMaskFromColor(sf::Color(0, 255, 0));
	shieldTexture.loadFromImage(shieldImage);
	shieldSprite.setTextureRect(sf::IntRect({ 0, 0 }, { 49, 48 }));
	shieldSprite.setOrigin({ 24, 24 });
	shieldSprite.setColor(sf::Color(255, 255, 255, 128));
}

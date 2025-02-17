
#include "weapon.h"

#include "map_structures/entities/entity/entity.h"
#include "map_structures/shells/shell/shell.h"
#include "map_structures/team/team.h"


void Weapon::shoot(const Entity& owner)
{
	PixelCoord shooterCor;

	shooterCor.x = coord.x + shooter.x * sin(angleRad);
	shooterCor.y = coord.y + shooter.y * cos(angleRad);

	owner.getTeam()->spawnShell(shellType, shooterCor, angleRad, angleDeg);
}

void Weapon::rotate(const Entity& owner)
{

}
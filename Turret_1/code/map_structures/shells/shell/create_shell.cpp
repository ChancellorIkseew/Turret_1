
#include "shell.h"
#include "shell_enum.h"
#include "map_structures/shells/shell_types/heavy_shell.h"
#include "map_structures/shells/shell_types/rocket.h"


std::unique_ptr<Shell> Shell::createShell(const ShellType type, const PixelCoord coord, float angleRad, float angleDeg, Team* const team)
{
	switch (type)
	{
	case ShellType::AC_SHELL:
		return std::make_unique<Shell>(coord, angleRad, angleDeg, team);
	case ShellType::HEAVY_SHELL:
		return std::make_unique<HeavyShell>(coord, angleRad, angleDeg, team);
	case ShellType::ROCKET:
		return std::make_unique<Rocket>(coord, angleRad, angleDeg, team);

	default:
		throw std::exception("shell_type does not exist");
	}
}

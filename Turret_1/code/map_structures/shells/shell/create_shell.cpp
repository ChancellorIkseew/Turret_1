
#include "shell.h"
#include "shell_enum.h"
#include "map_structures/shells/shell_types/heavy_shell.h"
#include "map_structures/shells/shell_types/rocket.h"

std::unique_ptr<Shell> Shell::createShell(short type, const PixelCoord coord, float angleRad, float angleDeg)
{
	switch (type)
	{
	case AC_SHELL:
		return std::make_unique<Shell>(type, coord, angleRad, angleDeg);
	case HEAVY_SHELL:
		return std::make_unique<HeavyShell>(type, coord, angleRad, angleDeg);
	case ROCKET:
		return std::make_unique<Rocket>(type, coord, angleRad, angleDeg);

	default:
		return nullptr;
	}
}

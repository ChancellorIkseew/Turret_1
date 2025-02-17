#pragma once
#ifndef SHELLS_LIST_H
#define SHELLS_LIST_H

#include <list>
#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/shells/shell/shell.h"

class Camera;

class ShellsList
{
private:
	std::list<std::unique_ptr<Shell>> shellsList;
	
public:
	ShellsList() = default;
	~ShellsList() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	void spawnShell(const ShellType type, const PixelCoord coord, float angleRad, float angleDeg, Team* const team);
	void move();

	void draw(sf::RenderWindow& window, const Camera& camera);

	void clean() noexcept;

};

#endif // SHELLS_LIST_H

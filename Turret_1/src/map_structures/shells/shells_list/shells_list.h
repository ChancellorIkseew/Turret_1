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

	void spawnShell(const ShellType type, const PixelCoord coord, const float angleRad, Team* team);
	void clear() noexcept { shellsList.clear(); }

	void interact();
	void draw(sf::RenderWindow& window, const Camera& camera);

	const std::list<std::unique_ptr<Shell>>& getList() const { return shellsList; }

};

#endif // SHELLS_LIST_H

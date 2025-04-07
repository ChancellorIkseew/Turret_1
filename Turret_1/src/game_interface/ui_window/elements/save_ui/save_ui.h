#pragma once
#ifndef T1_SAVE_UI_H
#define T1_SAVE_UI_H

#include "game_interface/ui_window/elements/button/button.h"
#include "game_interface/ui_window/elements/label/label.h"
#include "game_interface/ui_window/ui_window/ui_window.h"

class SaveUI
{
private:
	sf::Vector2i position;
	Button button;
	Label label;
	std::string folder;

	SaveUI(const SaveUI& other) = delete;
	SaveUI(const SaveUI&& other) = delete;
	SaveUI& operator=(const SaveUI& other) = delete;

public:
	SaveUI(const std::string name, const sf::Vector2i position);
	SaveUI& operator= (const SaveUI&& other) noexcept;
	SaveUI() = default;
	~SaveUI() = default;

	bool press();
	const std::string& getFolder() const { return folder; }

	void relocateWithOwner(const sf::Vector2i ownerPosition);
	void draw(sf::RenderWindow& window);

};

#endif // T1_SAVE_UI_H

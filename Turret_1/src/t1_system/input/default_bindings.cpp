
#include "input_handler.h"

static constexpr int intCode(sf::Mouse::Button sfMB) {
	return static_cast<int>(sfMB);
}
static constexpr int intCode(sf::Keyboard::Key sfKey) {
	return static_cast<int>(sfKey);
}

using namespace t1;
std::unordered_map<BindName, Binding> InputHandler::bindings
{
	{BindName::LMB, Binding(intCode(sf::Mouse::Button::Left), InputType::mouse)},
	{BindName::RMB, Binding(intCode(sf::Mouse::Button::Right), InputType::mouse)},
	{BindName::MidMB, Binding(intCode(sf::Mouse::Button::Middle), InputType::mouse)},

	{BindName::Build, Binding(intCode(sf::Mouse::Button::Left), InputType::mouse)},
	{BindName::Rotate_building, Binding(intCode(sf::Keyboard::Key::R), InputType::keyboard)},
	{BindName::Pipette, Binding(intCode(sf::Keyboard::Key::Q), InputType::keyboard)},
	{BindName::Demolish, Binding(intCode(sf::Keyboard::Key::LControl), InputType::keyboard)},

	{BindName::Control_unit, Binding(intCode(sf::Keyboard::Key::V), InputType::keyboard)},
	{BindName::Shoot, Binding(intCode(sf::Mouse::Button::Left), InputType::mouse)},

	{BindName::Move_up, Binding(intCode(sf::Keyboard::Key::W), InputType::keyboard)},
	{BindName::Move_left, Binding(intCode(sf::Keyboard::Key::A), InputType::keyboard)},
	{BindName::Move_down, Binding(intCode(sf::Keyboard::Key::S), InputType::keyboard)},
	{BindName::Move_right, Binding(intCode(sf::Keyboard::Key::D), InputType::keyboard)},

	{BindName::Pause, Binding(intCode(sf::Keyboard::Key::Space), InputType::keyboard)},
	{BindName::Cancel, Binding(intCode(sf::Keyboard::Key::Escape), InputType::keyboard)},
	{BindName::Escape, Binding(intCode(sf::Keyboard::Key::Escape), InputType::keyboard)},
	{BindName::Hide_GUI, Binding(intCode(sf::Keyboard::Key::F1), InputType::keyboard)},
	{BindName::Console_cheat, Binding(intCode(sf::Keyboard::Key::RAlt), InputType::keyboard)}
};

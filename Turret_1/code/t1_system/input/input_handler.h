#pragma once
#ifndef T1_SYSTEM_INPUT_HANDLER_H
#define T1_SYSTEM_INPUT_HANDLER_H

#include <queue>
#include <unordered_map>
#include "t1_input.h"


class InputHandler
{
private:
	static std::unordered_map<t1::KeyName, t1::Binding> bindings;

public:
	InputHandler() = default;
	~InputHandler() = default;

	static void updateInput(const sf::Event& event);

	static bool active(const t1::KeyName keyName);
	static bool jactive(const t1::KeyName keyName);

	static void rebind(const t1::KeyName keyName, const sf::Event& event);
};

#endif // T1_SYSTEM_INPUT_HANDLER_H

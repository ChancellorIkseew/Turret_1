#pragma once
#ifndef T1_SYSTEM_EVENTS
#define T1_SYSTEM_EVENTS

#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "map_structures/base_engine/base_engine.h"


class Event
{
protected:
	bool active;
	bool justChanged;
public:
	Event() = default;
	virtual ~Event() = default;
	virtual void process() = 0;
};


class InputEvent : public Event
{
private:
	
public:
	sf::Event sfEvent;
	InputEvent(sf::Event sfEvent) : sfEvent(sfEvent) {}
	void process() override final {}
};




enum class KeyName
{
	LMB,
	RMB,
	MidMB,

	Build,
	Demolish,
	Shoot,
	Control_unit,

	Move_up,
	Move_left,
	Move_down,
	Move_Right
};

enum class InputType
{
	keyboard,
	mouse,
};

class Binding
{
public:
	const int code;
	const InputType inputType;
	bool active = false;
	bool justChanged = false;

	Binding() = default;
	Binding(const int code, const InputType inputType) : code(code), inputType(inputType) {}
};



inline std::unordered_map<KeyName, Binding> bindings
{
	{ KeyName::LMB, Binding(sf::Mouse::Left, InputType::mouse) },
	{ KeyName::RMB, Binding(sf::Mouse::Right, InputType::mouse) },
	{ KeyName::MidMB, Binding(sf::Mouse::Middle, InputType::mouse) }


};



#endif // T1_SYSTEM_EVENTS

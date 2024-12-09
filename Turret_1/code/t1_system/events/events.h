#pragma once
#ifndef T1_SYSTEM_EVENTS
#define T1_SYSTEM_EVENTS

#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "map_structures/base_engine/base_engine.h"

namespace t1
{
	class Event
	{
	public:
		bool active = false;
		bool justChanged = false;
		Event() = default;
		virtual ~Event() = default;
		virtual void process() = 0;
	};


	class InputRegistred : public Event
	{
	private:

	public:
		sf::Event sfEvent;
		InputRegistred() = default;
		InputRegistred(sf::Event sfEvent) : sfEvent(sfEvent) {}
		void process() override final {}
	};

	class MapChanged : public Event
	{
	private:
		std::vector<TileCoord> tiles;
	public:
		MapChanged() = default;
		MapChanged(std::vector<TileCoord> tiles) : tiles(std::move(tiles))
		{
			active = true;
			justChanged = true;
		}
		void process() override final {}
	};


	enum class EventType
	{
		INPUT_REGISTRED,
		MAP_CHANGED



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
}


#endif // T1_SYSTEM_EVENTS

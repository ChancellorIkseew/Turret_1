#pragma once
#ifndef T1_SYSTEM_INPUT
#define T1_SYSTEM_INPUT

#include <SFML/Graphics.hpp>

namespace t1
{
	enum class KeyName
	{
		LMB,
		RMB,
		MidMB,

		Build,
		Demolish,
		Rotate_building,
		Shoot,
		Control_unit,

		Move_up,
		Move_left,
		Move_down,
		Move_right,

		Console_cheat
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
		bool justTriggered = false;

		Binding(const int code, const InputType inputType) : code(code), inputType(inputType) {}
		Binding() = default;
		~Binding() = default;
	};
}


#endif // T1_SYSTEM_INPUT
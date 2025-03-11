#pragma once
#ifndef T1_SYSTEM_INPUT
#define T1_SYSTEM_INPUT

#include <SFML/Graphics.hpp>

namespace t1
{
	enum class BindName
	{
		LMB,
		RMB,
		MidMB,

		Build,
		Demolish,
		Rotate_building,
		Pipette,
		Shoot,
		Control_unit,

		Move_up,
		Move_left,
		Move_down,
		Move_right,

		Pause,
		Cancel,
		Escape,
		Hide_GUI,
		Console_cheat
	};

	enum class InputType
	{
		keyboard,
		mouse,
	};

	enum class MouseWheelScroll
	{
		none = 0,
		up = 1,
		down = -1
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

#pragma once
#ifndef T1_CONTROL_H
#define T1_CONTROL_H

#include <typeinfo>

enum class Control : uint8_t
{
	NONE = 0,
	SOFT = 1,
	HARD = 2
};

#endif // T1_CONTROL_H

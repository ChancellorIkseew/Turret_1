
#include "system.h"


bool numKeyPressed()
{
	if (KEY_0_Pressed || KEY_1_Pressed || KEY_2_Pressed || KEY_3_Pressed || KEY_4_Pressed ||
		KEY_5_Pressed || KEY_6_Pressed || KEY_7_Pressed || KEY_8_Pressed || KEY_9_Pressed)
	{
		return true;
	}

	return false;
}

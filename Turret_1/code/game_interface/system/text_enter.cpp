
#include <iostream>

#include "text_enter.h"

#include "system.h"


void enterText(sf::Text& text)
{
	if (numKeyPressed() || BACKSPASE_Pressed)
	{
		std::cout << "numPressed" << '\n';


		if (BACKSPASE_Pressed)
		{
			std::string str = text.getString();
			std::string new_str = str.substr(0, str.length() - 1);

			text.setString(new_str);
		}

		if (KEY_0_Pressed)
		{
			text.setString(text.getString() + "0");
		}

		if (KEY_1_Pressed)
		{
			text.setString(text.getString() + "1");
		}

		if (KEY_2_Pressed)
		{
			text.setString(text.getString() + "2");
		}

		if (KEY_3_Pressed)
		{
			text.setString(text.getString() + "3");
		}

		if (KEY_4_Pressed)
		{
			text.setString(text.getString() + "4");
		}

		if (KEY_5_Pressed)
		{
			text.setString(text.getString() + "5");
		}

		if (KEY_6_Pressed)
		{
			text.setString(text.getString() + "6");
		}

		if (KEY_7_Pressed)
		{
			text.setString(text.getString() + "7");
		}

		if (KEY_8_Pressed)
		{
			text.setString(text.getString() + "8");
		}

		if (KEY_9_Pressed)
		{
			text.setString(text.getString() + "9");
		}

		Sleep(150);
	}
}
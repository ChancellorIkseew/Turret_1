#pragma once
#ifndef T1_SYSTEM_H
#define T1_SYSTEM_H

#include <Windows.h>


#define LMB_Pressed (GetKeyState(VK_LBUTTON) < 0)
#define LMB_Free (GetKeyState(VK_LBUTTON) >= 0)

#define RMB_Pressed (GetKeyState(VK_RBUTTON) < 0)
#define RMB_Free (GetKeyState(VK_RBUTTON) >= 0)

#define MidMB_Pressed (GetKeyState(VK_MBUTTON) < 0)
#define MidMB_Free (GetKeyState(VK_MBUTTON) >= 0)


#define LEFT_ALT_Pressed (GetKeyState(VK_LMENU) < 0)

#define BACKSPASE_Pressed (GetKeyState(VK_BACK) < 0)

#define DELETE_Pressed (GetKeyState(VK_DELETE) < 0)



#define KEY_0_Pressed (GetKeyState(VK_NUMPAD0) < 0)
#define KEY_1_Pressed (GetKeyState(VK_NUMPAD1) < 0)
#define KEY_2_Pressed (GetKeyState(VK_NUMPAD2) < 0)
#define KEY_3_Pressed (GetKeyState(VK_NUMPAD3) < 0)
#define KEY_4_Pressed (GetKeyState(VK_NUMPAD4) < 0)
#define KEY_5_Pressed (GetKeyState(VK_NUMPAD5) < 0)
#define KEY_6_Pressed (GetKeyState(VK_NUMPAD6) < 0)
#define KEY_7_Pressed (GetKeyState(VK_NUMPAD7) < 0)
#define KEY_8_Pressed (GetKeyState(VK_NUMPAD8) < 0)
#define KEY_9_Pressed (GetKeyState(VK_NUMPAD9) < 0)

bool numKeyPressed();


#endif // !T1_SYSTEM_H

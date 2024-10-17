
#include <windows.h>
#include "sleep.h"

void t1::system::sleep(const int timeInMilliseconds)
{
	Sleep(timeInMilliseconds);
}
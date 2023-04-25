#define TK_PLATFORM_WINDOWS 1

#if TK_PLATFORM_WINDOWS

#ifndef _WINDOWS
#define _WINDOWS
#endif

#include <Windows.h>

#include <windef.h>  // Basuc type definitions.
#include <winnt.h>   // Type definitions for unicode support.
#include <WinBase.h> // Kernel functions.
#include <WinUser.h> // User interface functions.
#include <wingdi.h>  // Graphics device interface functions.

INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CmdLine, INT CmdShow)
{
	const INT Result = MessageBoxA(HWND_DESKTOP, "Hello Windows!", "Test message", 0);

	return 0;
}

#else

#ifndef _CONSOLE
#define _CONSOLE
#endif

#include <stdio.h>
#include <stdint.h>

int32_t main(int32_t ArgC, const char** ArgV)
{
	printf("Hello!\n");

	return 0;
}

#endif
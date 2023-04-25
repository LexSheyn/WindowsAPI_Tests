#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

INT32 CDECL MessageBoxPrintF (CHAR* Caption, CHAR* Format, ...);

INT32 WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CmdLine, INT32 CmdShow)
{
	const INT32 ScreenX = GetSystemMetrics(SM_CXSCREEN);
	const INT32 ScreenY = GetSystemMetrics(SM_CYSCREEN);

	const INT32 MessageBoxResult = MessageBoxPrintF("Screen size", "Width:\t%i\tpixels\nHeight:\t%i\tpixels", ScreenX, ScreenY);

	return 0;
}

INT32 MessageBoxPrintF(CHAR* Caption, CHAR* Format, ...)
{
	CHAR Buffer[1024] = { 0 };

	va_list p_VariadicArgumentList;

	// The va_start macro defined in <stdarg.h> is usually equivalent to: p_VariadicArgumentList = (char*)&Format + sizeof(Format).

	va_start(p_VariadicArgumentList, Format);

	// The last argument to vsprintf points to the arguments.

	vsnprintf(Buffer, 1024, Format, p_VariadicArgumentList);

	va_end(p_VariadicArgumentList);

	return MessageBoxA(HWND_DESKTOP, Buffer, Caption, MB_OK);
}

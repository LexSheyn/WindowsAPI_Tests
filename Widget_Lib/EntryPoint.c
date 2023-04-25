#include "GUI/TrickWidgetSystem.h"
#include "GUI/TrickWidget.h"

#include <Windows.h>

void OnClose(TkWindow Window, void* p_UserData)
{
	tk_bool8_t* b_Running = p_UserData;

	*b_Running = TK_FALSE;
}

tk_int32_t main(tk_int32_t ArgumentCount, const tk_char8_t** ArgumentValues)
{
	tk_bool8_t b_Running = TK_TRUE;

	tkInitializeWidgetSystem();

	TkWindowClassCreateInfo WindowClassCreateInfo = { 0 };

	WindowClassCreateInfo.StructType      = 0;
	WindowClassCreateInfo.p_Next          = 0;
	WindowClassCreateInfo.Icon            = TK_NULLPTR;
	WindowClassCreateInfo.IconSmall       = TK_NULLPTR;
	WindowClassCreateInfo.Cursor          = TK_NULLPTR;
	WindowClassCreateInfo.FrameColor      = 0;
	WindowClassCreateInfo.BackgroundColor = 0;
	WindowClassCreateInfo.TextColor       = 0;

	TkWindowClass WindowClass = TK_NULLPTR;

	const TkResult CreateWindowClassResult = tkCreateWindowClass(&WindowClassCreateInfo, &WindowClass);

	TkWindowCreateInfo WindowCreateInfo = { 0 };

	WindowCreateInfo.StructType        = 0;
	WindowCreateInfo.p_Next            = 0;
	WindowCreateInfo.WindowClass       = WindowClass;
	WindowCreateInfo.Parent            = TK_NULLPTR;
	WindowCreateInfo.Name              = "Test window";
	WindowCreateInfo.PosX              = 100;
	WindowCreateInfo.PosY              = 100;
	WindowCreateInfo.Width             = 640;
	WindowCreateInfo.Height            = 360;
	WindowCreateInfo.pfn_CloseCallback = OnClose;
	WindowCreateInfo.p_UserData        = &b_Running;

	TkWindow Window = TK_NULLPTR;

	const TkResult CreateWidgetResult = tkCreateWindow(&WindowCreateInfo, &Window);

	while (b_Running)
	{
		tkWidgetUpdate((TkWidget)Window);

		Sleep(16);
	}

	tkDestroyWindow(Window);

	tkDestroyWindowClass(WindowClass);

	tkTerminateWidgetSystem();

	return 0;
}
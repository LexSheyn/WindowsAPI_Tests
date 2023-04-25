#undef UNICODE

#include <Windows.h>
#pragma comment(lib,"winmm.lib")

LRESULT CALLBACK WindowProcedure (HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);

INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CmdLine, INT CmdShow)
{
	BOOL b_ApplicationRunning = TRUE;

	CHAR ApplicationName[14] = "Hello Windows\0";

	HWND Window = NULL;

	MSG  Msg = { 0 };

	WNDCLASSEXA WindowClass = { 0 };

	WindowClass.cbSize        = sizeof(WNDCLASSEXA);
	WindowClass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WindowClass.lpfnWndProc   = WindowProcedure;
	WindowClass.cbClsExtra    = 0;
	WindowClass.cbWndExtra    = 0;
	WindowClass.hInstance     = Instance;
	WindowClass.hIcon         = LoadIconA(NULL, IDI_APPLICATION);
	WindowClass.hCursor       = LoadCursorA(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WindowClass.lpszMenuName  = NULL;
	WindowClass.lpszClassName = ApplicationName;
	WindowClass.hIconSm       = LoadIconA(NULL, IDI_APPLICATION);

	const ATOM WindowClassId = RegisterClassExA(&WindowClass);

	if (!WindowClassId)
	{
		const INT MessageBoxResult = MessageBoxA(HWND_DESKTOP, "This program requires Windows NT!", ApplicationName, MB_ICONERROR);

		return 0;
	}

	Window = CreateWindowExA(0                         // Window extended style
	                       , WindowClass.lpszClassName // Window class name
	                       , "The Hello Program"       // Window caption
	                       , WS_OVERLAPPEDWINDOW       // Window style
	                       , CW_USEDEFAULT             // Initial x position
	                       , CW_USEDEFAULT             // Initial y position
	                       , CW_USEDEFAULT             // Initial x size
	                       , CW_USEDEFAULT             // Initial y size
	                       , HWND_DESKTOP              // Parent window handle
	                       , NULL                      // Window menu handle
	                       , Instance                  // Program instance handle
	                       , &b_ApplicationRunning);   // Create parameters

	const BOOL b_Displayed    = ShowWindow(Window, SW_SHOWNORMAL);
	const BOOL b_UpdateResult = UpdateWindow(Window);

	while (b_ApplicationRunning)
	{
		while (PeekMessageA(&Msg, Window, 0, 0, PM_REMOVE))
		{
			const BOOL b_Translated = TranslateMessage(&Msg);

			const LRESULT DispatchResult = DispatchMessageA(&Msg);
		}
	}

//	while (GetMessageA(&Msg, Window, 0, 0))
//	{
//		const BOOL b_Translated = TranslateMessage(&Msg);
//
//		const LRESULT DispatchResult = DispatchMessageA(&Msg);
//	}

	return (INT)Msg.wParam;
}

LRESULT WindowProcedure(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	HDC         DeviceContext = NULL;
	PAINTSTRUCT PaintStruct   = { 0 };
	RECT        Rect          = { 0 };

	switch (Message)
	{
		case WM_NCCREATE:
		{
			CREATESTRUCTA* CreateStruct = (CREATESTRUCTA*)LParam;

			const LONG_PTR PreviousValue = SetWindowLongPtrA(Window, GWLP_USERDATA, (LONG_PTR)CreateStruct->lpCreateParams);

			break;
		}

		case WM_CREATE:
		{
		//	const BOOL b_PlayResult = PlaySoundA("D:\\Royalty FREE Music\\Music Loops Mini Set\\Rock Music Loops\\Fatality Racer.wav", NULL, SND_FILENAME | SND_ASYNC);

			return 0;
		}

		case WM_PAINT:
		{
			DeviceContext = BeginPaint(Window, &PaintStruct);

			const BOOL b_GetClientRectResult = GetClientRect(Window, &Rect);

		//	const INT DrawResult = DrawTextA(DeviceContext, "Hello Windows 98!", -1, &Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			const INT BackgroundMode = SetBkMode(DeviceContext, TRANSPARENT);

			const COLORREF TextColor = SetTextColor(DeviceContext, RGB(255, 255, 255));

			const BOOL b_TextOutResult = TextOutA(DeviceContext, Rect.left + (Rect.right / 2), Rect.top + (Rect.bottom / 2), "Hello Windows 10!", 18);

			const BOOL b_EndPaintResult = EndPaint(Window, &PaintStruct);

			return 0;
		}

		case WM_CLOSE:
		{
			BOOL* pb_ApplicationRunning = (BOOL*)GetWindowLongPtrA(Window, GWLP_USERDATA);

			*pb_ApplicationRunning = FALSE;

		//	PostQuitMessage(0);

			break;
		}

		case WM_DESTROY:
		{
		//	PostQuitMessage(0);

			return 0;
		}
	}

	return DefWindowProcA(Window, Message, WParam, LParam);
}
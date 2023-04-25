#include <Windows.h>

#include <stdint.h>
#include <stdio.h>

#define BTN_ID 101

#define WM_PUSHBUTTONDOWN   WM_APP + 1
#define WM_PUSHBUTTONUP     WM_APP + 2

LONG PercentageL32(LONG Value, LONG PercentCount)
{
	const FLOAT OnePercentF = (FLOAT)Value / 100.0f;
	const FLOAT PercentageF = OnePercentF * (FLOAT)PercentCount;
	const LONG  Percentage  = (LONG)PercentageF;

	return Percentage;
}

LRESULT WINAPI WindowProcedure(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);

LRESULT HandleDrawItem(HWND hWnd, WPARAM wParam, LPARAM lParam);

static int32_t b_Running = TRUE;

int32_t main(int32_t ArgumentCount, const char** ArgumentValues)
{
	HMODULE Module = GetModuleHandleA(NULL);

	WNDCLASSEXA WindowClass = { 0 };

	WindowClass.cbSize        = sizeof(WNDCLASSEXA);
	WindowClass.style         = CS_DBLCLKS;
	WindowClass.lpfnWndProc   = WindowProcedure;
	WindowClass.cbClsExtra    = 0;
	WindowClass.cbWndExtra    = 0;
	WindowClass.hInstance     = Module;
	WindowClass.hIcon         = NULL;
	WindowClass.hCursor       = NULL;
	WindowClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	WindowClass.lpszMenuName  = NULL;
	WindowClass.lpszClassName = "ClassName";
	WindowClass.hIconSm       = NULL;

	ATOM WindowClassId = RegisterClassExA(&WindowClass);

	HWND Window = CreateWindowExA(WS_EX_APPWINDOW, WindowClass.lpszClassName, "Test window", WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 100, 100, 400, 400, NULL, NULL, Module, NULL);

//	WNDCLASSEXA ButtonClass = { 0 };
//
//	ButtonClass.cbSize        = sizeof(WNDCLASSEXA);
//	ButtonClass.style         = CS_DBLCLKS;
//	ButtonClass.lpfnWndProc   = WindowProcedure;
//	ButtonClass.cbClsExtra    = 0;
//	ButtonClass.cbWndExtra    = 0;
//	ButtonClass.hInstance     = Module;
//	ButtonClass.hIcon         = NULL;
//	ButtonClass.hCursor       = NULL;
//	ButtonClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
//	ButtonClass.lpszMenuName  = NULL;
//	ButtonClass.lpszClassName = "ButtonClass";
//	ButtonClass.hIconSm       = NULL;

//	HWND Button = CreateWindowExA(0, ButtonClass.lpszClassName , "Test button", BS_OWNERDRAW | WS_CHILD | WS_VISIBLE, 20, 20, 50, 50, Window, 0, Module, 0);
	HWND Button = CreateWindowExA(0, "button" , "Test button", BS_OWNERDRAW | WS_CHILD | WS_VISIBLE, 20, 20, 100, 100, Window, (HMENU)BTN_ID, Module, NULL);
//	HWND Button = CreateWindowExA(0, "button" , "Test button", WS_CHILD | WS_VISIBLE, 20, 20, 50, 50, Window, (HMENU)BTN_ID, Module, NULL);

	const BOOL b_ShowWindowResult = ShowWindow(Window, SW_SHOW);
	const BOOL b_ShowButtonResult = ShowWindow(Button, SW_SHOW);

	const BOOL b_UpdateWindowResult = UpdateWindow(Window);
	const BOOL b_UpdateButtonResult = UpdateWindow(Button);

	while (b_Running)
	{
		MSG Message = { 0 };

		while (PeekMessageA(&Message, Window, 0, 0, PM_REMOVE))
		{
			const BOOL    b_TranslateResult = TranslateMessage(&Message);
			const LRESULT DispatchResult    = DispatchMessageA(&Message);

			if (Message.message == WM_QUIT)
			{
				b_Running = FALSE;

				break;
			}
		}
		
	//	Sleep(10);
	}

	return 0;
}

LRESULT __stdcall WindowProcedure(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
		case WM_DRAWITEM:
		{
			int a = 0;
		} return HandleDrawItem(Window, WParam, LParam);


		case WM_PUSHBUTTONDOWN:
		{
			printf("Button down event\n");
		} break;

		case WM_PUSHBUTTONUP:
		{
			printf("Button up event\n");
		} break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} return 0;

		case WM_CLOSE:
		{
			b_Running = FALSE;
		} return 0;
	}

	return DefWindowProcA(Window, Message, WParam, LParam);
}

LRESULT HandleDrawItem(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	DRAWITEMSTRUCT* dis = (DRAWITEMSTRUCT*)(lParam);

	if (dis->CtlType != ODT_BUTTON)
	{
		return 0;
	}

	UINT style = (dis->itemState & ODS_SELECTED) ? DFCS_BUTTONPUSH | DFCS_PUSHED : DFCS_BUTTONPUSH;

	RECT rect = dis->rcItem;

	DrawFrameControl(dis->hDC, &rect, DFC_BUTTON, style);

	char text[512];

	int n = GetWindowTextA(dis->hwndItem, text, 512);

//	rect.left   += 2;
//	rect.top    += 2;
	rect.right  -= PercentageL32(rect.right, 3);
	rect.bottom -= PercentageL32(rect.bottom, 3);

	DrawTextA(dis->hDC, text, n, &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_NOCLIP);

	if (dis->itemAction == ODA_SELECT)
	{
		
		PostMessageA(hWnd
			      , (dis->itemState & ODS_SELECTED) ? WM_PUSHBUTTONDOWN : WM_PUSHBUTTONUP
			      , dis->CtlID
			      , 0
		);
	}

	return 0;
}
#include "SystemMetrics.h"

#include <string.h>
#include <stdio.h>

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

	const BOOL b_DestroyWindowResult = DestroyWindow(Window);

	return (INT)Msg.wParam;
}

LRESULT WindowProcedure(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	static INT CharWidth          = 0;
	static INT CharHeight         = 0;
	static INT UppercaseCharWidth = 0;

	HDC         DeviceContext  = NULL;
	PAINTSTRUCT PaintStruct    = { 0 };
	CHAR        CharBuffer[10] = { 0 };
	TEXTMETRICA TextMetric     = { 0 };

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
			DeviceContext = GetDC(Window);

			const BOOL b_GetTextMetricResult = GetTextMetricsA(DeviceContext, &TextMetric);

			CharWidth          = TextMetric.tmAveCharWidth;
			CharHeight         = TextMetric.tmHeight + TextMetric.tmExternalLeading;
			UppercaseCharWidth = (TextMetric.tmPitchAndFamily & 1 ? 3 : 2) * CharWidth / 2;

			const INT ReleaseDeviceContextResult = ReleaseDC(Window, DeviceContext);

			return 0;
		}

		case WM_PAINT:
		{
			DeviceContext = BeginPaint(Window, &PaintStruct);

			const INT LineCount = SYSTEM_METRICS_LINE_COUNT;

			for (INT i = 0; i < LineCount; ++i)
			{
				const INT BackgroundMode = SetBkMode(DeviceContext, TRANSPARENT);

				const COLORREF TextColor = SetTextColor(DeviceContext, RGB(255, 255, 255));

				const BOOL b_LabelOutResult = TextOutA(DeviceContext, 0, CharHeight * i, SystemMetrics[i].Label, strlen(SystemMetrics[i].Label));

				const BOOL b_DescriptionOutResult = TextOutA(DeviceContext, 22 * UppercaseCharWidth, CharHeight * i, SystemMetrics[i].Description, strlen(SystemMetrics[i].Description));

				const UINT b_SetAlignRightResult = SetTextAlign(DeviceContext, TA_RIGHT | TA_TOP);

#pragma warning(suppress: 4996)
				const BOOL b_ValueOutResult = TextOutA(DeviceContext, 22 * UppercaseCharWidth + 40 * CharWidth, CharHeight * i, CharBuffer, sprintf(CharBuffer, "%5d", GetSystemMetrics(SystemMetrics[i].Index)));

				const BOOL b_SetLeftAlignResult = SetTextAlign(DeviceContext, TA_LEFT | TA_TOP);
			}

			const BOOL b_EndPaintResult = EndPaint(Window, &PaintStruct);

			return 0;
		}

		case WM_CLOSE:
		{
			BOOL* pb_ApplicationRunning = (BOOL*)GetWindowLongPtrA(Window, GWLP_USERDATA);

			*pb_ApplicationRunning = FALSE;

			return 0; // Cancel DestroyWindow(_) to perform it manually later.
		}
	}

	return DefWindowProcA(Window, Message, WParam, LParam);
}
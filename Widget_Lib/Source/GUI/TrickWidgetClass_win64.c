//#include "PCH/trickpch.h"
#include "GUI/TrickWidgetClass.h"

#include "GUI/TrickWidget.h"

#if TK_PLATFORM_WINDOWS

#include "GUI/TrickWidgetClass_win64.h"
#include "GUI/TrickWidgetSystem_win64.h"
#include "GUI/TrickWidget_win64.h"

#include <stdlib.h>

typedef struct TkWidgetClassCreateInfo
{
	TkStructureType      StructType;
	const void*          p_Next;
	const tk_char8_t*    Name;
	WNDPROC              Procedure;
	HBRUSH               BackgroundBrush;
	HICON                Icon;
	HICON                IconSmall;
	HCURSOR              Cursor;
} TkWidgetClassCreateInfo;

TkResult tk_CreateWidgetClass(const TkWidgetClassCreateInfo* p_CreateInfo, TkWidgetClass WidgetClass)
{
	WidgetClass->ProgranInstance = GetModuleHandleA(NULL);
	
	memset(WidgetClass->Name, 0, TK_WIDGET_CLASS_NAME_LENGTH_NT);

	tk_size_t NameLength = strlen(p_CreateInfo->Name);

	if (NameLength > TK_WIDGET_CLASS_NAME_LENGTH)
	{
		NameLength = TK_WIDGET_CLASS_NAME_LENGTH;
	}

	memcpy(WidgetClass->Name, p_CreateInfo->Name, NameLength);

	WNDCLASSEXA WindowClass = { 0 };

	WindowClass.cbSize        = sizeof(WNDCLASSEXA);
	WindowClass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WindowClass.lpfnWndProc   = p_CreateInfo->Procedure;
	WindowClass.cbClsExtra    = 0;
	WindowClass.cbWndExtra    = 0;
	WindowClass.hInstance     = WidgetClass->ProgranInstance;
	WindowClass.hIcon         = p_CreateInfo->Icon;
	WindowClass.hCursor       = p_CreateInfo->Cursor;
	WindowClass.hbrBackground = p_CreateInfo->BackgroundBrush;
	WindowClass.lpszMenuName  = NULL; // TO DO
	WindowClass.lpszClassName = WidgetClass->Name;
	WindowClass.hIconSm       = p_CreateInfo->IconSmall;

	WidgetClass->Handle = RegisterClassExA(&WindowClass);

	if (!WidgetClass->Handle)
	{
		return TK_ERROR_INITIALIZATION_FAILED;
	}

	return TK_SUCCESS;
}

void tk_DestroyWidgetClass(TkWidgetClass WidgetClass)
{
	const BOOL b_Result = UnregisterClassA(WidgetClass->Name, WidgetClass->ProgranInstance);
}

LRESULT CALLBACK tk_WindowProcedure (HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

TkResult tkCreateWindowClass(const TkWindowClassCreateInfo* p_CreateInfo, TkWindowClass* p_WindowClass)
{
	*p_WindowClass = malloc(sizeof(TkWindowClass_T));

	TkWindowClass WindowClass = *p_WindowClass;

	if (!WindowClass)
	{
		return TK_ERROR_OUT_OF_HOST_MEMORY;
	}

	TkWidgetClassCreateInfo WidgetClassCreateInfo = { 0 };

	WidgetClassCreateInfo.StructType      = 0;
	WidgetClassCreateInfo.p_Next          = 0;
	WidgetClassCreateInfo.Name            = "TrickWindowClass";
	WidgetClassCreateInfo.Procedure       = tk_WindowProcedure;
	WidgetClassCreateInfo.BackgroundBrush = (HBRUSH)GetStockObject(BLACK_BRUSH); // TO DO
	WidgetClassCreateInfo.Icon            = NULL;
	WidgetClassCreateInfo.IconSmall       = NULL;
	WidgetClassCreateInfo.Cursor          = NULL;

	const TkResult CreateWidgetClassResult = tk_CreateWidgetClass(&WidgetClassCreateInfo, &WindowClass->WidgetClass);

	if (CreateWidgetClassResult != TK_SUCCESS)
	{
		return TK_ERROR_INITIALIZATION_FAILED;
	}

	WindowClass->Icon       = NULL; // TO DO
	WindowClass->IconSmall  = NULL; // TO DO
	WindowClass->Cursor     = NULL; // TO DO
	WindowClass->FrameBrush = NULL; // TO DO

	return TK_SUCCESS;
}

void tkDestroyWindowClass(TkWindowClass WindowClass)
{
	tk_DestroyWidgetClass(&WindowClass->WidgetClass);

	free(WindowClass);
}

LRESULT tk_WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	HDC         DeviceContext = NULL;
	PAINTSTRUCT PaintStruct   = { 0 };
	RECT        Rect          = { 0 };

	switch (Message)
	{
		case WM_NCCREATE:
		{
			CREATESTRUCTA* p_WindowCreateStruct = TK_CAST(CREATESTRUCTA*, LParam);

			SetWindowLongPtrA(Handle, GWLP_USERDATA, (LONG_PTR)p_WindowCreateStruct->lpCreateParams);

			break; // Forward to DefWindowProcA(_), otherwise window title information will be lost.
		}

		case WM_CREATE:
		{
			

			return 0;
		}

		case WM_NCPAINT:
		{
			break;
		}

		case WM_PAINT:
		{
			DeviceContext = BeginPaint(Handle, &PaintStruct);

			const INT BackgroundMode = SetBkMode(DeviceContext, TRANSPARENT);

			const COLORREF TextColor = SetTextColor(DeviceContext, RGB(255, 255, 255));

			tk_char8_t WindowText[256] = { 0 };
			tk_int32_t WindowTextLength = GetWindowTextLengthA(Handle);

			GetWindowTextA(Handle, WindowText, WindowTextLength + 1);

		//	const BOOL b_LabelOutResult = TextOutA(DeviceContext, 10, 10, WindowText, WindowTextLength);
			const tk_int32_t DrawTextResult = DrawTextA(DeviceContext, "Test line 0\n Test line 1", -1, &PaintStruct.rcPaint, DT_CENTER);

			const BOOL b_EndPaintResult = EndPaint(Handle, &PaintStruct);

			return 0;
		//	break;
		}

		case WM_CLOSE:
		{
			TkWindow Window = (TkWindow)GetWindowLongPtrA(Handle, GWLP_USERDATA);

			Window->pfn_CloseCallback(Window, Window->p_UserData);

			return 0;
		}

		case WM_DESTROY:
		{
			//

			break;
		}
	}

	return DefWindowProcA(Handle, Message, WParam, LParam);
}

#endif // TK_PLATFORM_WINDOWS
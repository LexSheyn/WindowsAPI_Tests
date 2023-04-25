//#include "PCH/trickpch.h"
#include "GUI/TrickWidget.h"

#if TK_PLATFORM_WINDOWS

#include "GUI/TrickWidget_win64.h"
#include "GUI/TrickWidgetClass_win64.h"

#include <stdlib.h>

typedef struct TkWidgetCreateInfo
{
	TkStructureType      StructType;
	const void*          p_Next;
	TkWidgetClass        WidgetClass;
	TkWidget             Parent;
	DWORD                Style;
	DWORD                StyleEx;
	HMENU                Menu;
	const tk_char8_t*    Name;
	tk_int32_t           PosX;
	tk_int32_t           PosY;
	tk_int32_t           Width;
	tk_int32_t           Height;
} TkWidgetCreateInfo;

TkResult tk_CreateWidget(const TkWidgetCreateInfo* p_CreateInfo, TkWidget Widget)
{
	const tk_char8_t* WidgetClassName = TK_NULLPTR;
	HINSTANCE         ProgramInstance = NULL;
	HWND              Parent          = HWND_DESKTOP;

	if (p_CreateInfo->WidgetClass)
	{
		WidgetClassName = p_CreateInfo->WidgetClass->Name;
		ProgramInstance = p_CreateInfo->WidgetClass->ProgranInstance;
	}

	if (p_CreateInfo->Parent)
	{
		Parent = p_CreateInfo->Parent->Handle;
	}

	Widget->Handle = CreateWindowExA(p_CreateInfo->StyleEx
	                               , WidgetClassName
	                               , p_CreateInfo->Name
	                               , p_CreateInfo->Style
	                               , p_CreateInfo->PosX
	                               , p_CreateInfo->PosY
	                               , p_CreateInfo->Width
	                               , p_CreateInfo->Height
	                               , Parent
	                               , p_CreateInfo->Menu
	                               , ProgramInstance
	                               , Widget);

	if (!Widget->Handle)
	{
		return TK_ERROR_INITIALIZATION_FAILED;
	}

	const DWORD ErrorCode = GetLastError();

	const BOOL b_Displayed    = ShowWindow  (Widget->Handle, SW_SHOWNORMAL);
	const BOOL b_UpdateResult = UpdateWindow(Widget->Handle);

	return TK_SUCCESS;
}

void tk_DestroyWidget(TkWidget Widget)
{
	const BOOL b_DestroyResult = DestroyWindow(Widget->Handle);
}

void tkWidgetUpdate(TkWidget Widget)
{
	BOOL    b_Translated   = 0;
	LRESULT DispatchResult = 0;

	while (PeekMessageA(&Widget->MessageStruct, Widget->Handle, 0, 0, PM_REMOVE))
	{
		b_Translated   = TranslateMessage(&Widget->MessageStruct);
		DispatchResult = DispatchMessageA(&Widget->MessageStruct);
	}
}

TkResult tkCreateWindow(const TkWindowCreateInfo* p_CreateInfo, TkWindow* p_Window)
{
	*p_Window = malloc(sizeof(TkWindow_T));

	TkWindow Window = *p_Window;

	if (!Window)
	{
		return TK_ERROR_OUT_OF_HOST_MEMORY;
	}

	TkWidgetCreateInfo WidgetCreateInfo = { 0 };

	WidgetCreateInfo.StructType  = 0;
	WidgetCreateInfo.p_Next      = 0;
	WidgetCreateInfo.WidgetClass = p_CreateInfo->WindowClass;
	WidgetCreateInfo.Parent      = p_CreateInfo->Parent;
	WidgetCreateInfo.Style       = WS_OVERLAPPEDWINDOW; // TO DO
	WidgetCreateInfo.StyleEx     = 0; // TO DO
	WidgetCreateInfo.Menu        = NULL; // TO DO
	WidgetCreateInfo.Name        = p_CreateInfo->Name;
	WidgetCreateInfo.PosX        = p_CreateInfo->PosX;
	WidgetCreateInfo.PosY        = p_CreateInfo->PosY;
	WidgetCreateInfo.Width       = p_CreateInfo->Width;
	WidgetCreateInfo.Height      = p_CreateInfo->Height;

	const TkResult CreateWidgetResult = tk_CreateWidget(&WidgetCreateInfo, &Window->Widget);

	if (CreateWidgetResult != TK_SUCCESS)
	{
		return TK_ERROR_INITIALIZATION_FAILED;
	}

	Window->pfn_CloseCallback = p_CreateInfo->pfn_CloseCallback;
	Window->p_UserData        = p_CreateInfo->p_UserData;

	return TK_SUCCESS;
}

void tkDestroyWindow(TkWindow Window)
{
	tk_DestroyWidget(&Window->Widget);

	free(Window);
}

#endif // TK_PLATFORM_WINDOWS
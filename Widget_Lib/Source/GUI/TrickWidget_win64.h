#pragma once

#include "Platform/Trick_win64.h"

#if TK_PLATFORM_WINDOWS

typedef struct TkWidget_T
{
	HWND    Handle;
	MSG     MessageStruct;
} TkWidget_T;

typedef struct TkWindow_T
{
	TkWidget_T Widget;
	void (TK_CALL *pfn_CloseCallback) (void* Window, void* p_UserData);
	void* p_UserData;
} TkWindow_T;

#endif // TK_PLATFORM_WINDOWS
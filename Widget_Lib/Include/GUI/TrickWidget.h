#pragma once

#include "TrickWidgetClass.h"

TK_DEFINE_HANDLE(TkWidget);

TK_API void TK_CALL tkWidgetUpdate (TkWidget Widget);
// TO DO: Show, hide, set position, set size, etc...

TK_DEFINE_HANDLE(TkWindow);

typedef void (TK_CALL *PFN_tkWindowCallback) (TkWindow Window, void* p_UserData);

typedef struct TkWindowCreateInfo
{
	TkStructureType         StructType;
	const void*             p_Next;
	TkWindowClass           WindowClass;
	TkWidget                Parent;
	const tk_char8_t*       Name;
	tk_int32_t              PosX;
	tk_int32_t              PosY;
	tk_int32_t              Width;
	tk_int32_t              Height;
	PFN_tkWindowCallback    pfn_CloseCallback;
	void*                   p_UserData;
} TkWindowCreateInfo;

TK_API TkResult TK_CALL tkCreateWindow  (const TkWindowCreateInfo* p_CreateInfo, TkWindow* p_Window);
TK_API void     TK_CALL tkDestroyWindow (TkWindow Window);
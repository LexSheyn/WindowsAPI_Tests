#pragma once

#include "Core/TrickBase.h"

TK_DEFINE_HANDLE(TkWidgetClass);

TK_DEFINE_HANDLE(TkWindowClass);

typedef struct TkWindowClassCreateInfo
{
	TkStructureType    StructType;
	const void*        p_Next;
	const void*        Icon;
	const void*        IconSmall;
	const void*        Cursor;
	tk_uint32_t        FrameColor;
	tk_uint32_t        BackgroundColor;
	tk_uint32_t        TextColor;
} TkWindowClassCreateInfo;

TK_API TkResult TK_CALL tkCreateWindowClass  (const TkWindowClassCreateInfo* p_CreateInfo, TkWindowClass* p_WindowClass);
TK_API void     TK_CALL tkDestroyWindowClass (TkWindowClass WindowClass);
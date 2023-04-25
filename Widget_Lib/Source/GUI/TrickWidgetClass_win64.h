#pragma once

#include "Platform/Trick_win64.h"

#if TK_PLATFORM_WINDOWS

#define TK_WIDGET_CLASS_NAME_LENGTH_NT 64u
#define TK_WIDGET_CLASS_NAME_LENGTH    63u

typedef struct TkWidgetClass_T
{
	ATOM          Handle;
	HINSTANCE     ProgranInstance;
	tk_char8_t    Name[TK_WIDGET_CLASS_NAME_LENGTH_NT];
	HBRUSH        BackgroundBrush;
} TkWidgetClass_T;

typedef struct TkWindowClass_T
{
	TkWidgetClass_T    WidgetClass;
	HICON              Icon;
	HICON              IconSmall;
	HCURSOR            Cursor;
	HBRUSH             FrameBrush;
} TkWindowClass_T;

#endif // TK_PLATFORM_WINDOWS
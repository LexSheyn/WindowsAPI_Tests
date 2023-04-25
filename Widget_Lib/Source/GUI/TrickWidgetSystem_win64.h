#pragma once

#include "Platform/Trick_win64.h"

#if TK_PLATFORM_WINDOWS

typedef struct TkWidgetSystem_T
{
	TEXTMETRICA    TextMetric;
	tk_int32_t     CharTotalWidth;
	tk_int32_t     CharTotalHeight;
	tk_int32_t     ScreenWidth;
	tk_int32_t     ScreenHeight;
	tk_int32_t     VerticalScrollWidth;
	tk_int32_t     HorizontalScrollHeight;
	// TO DO: Add system metrics here.
} TkWidgetSystem_T;

#endif // TK_PLATFORM_WINDOWS
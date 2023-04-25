//#include "PCH/trickpsh.h"
#include "GUI/TrickWidgetSystem.h"

#if TK_PLATFORM_WINDOWS

#include "GUI/TrickWidgetSystem_win64.h"

#include <stdlib.h>

static TkWidgetSystem WidgetSystem;

void tkInitializeWidgetSystem()
{
	WidgetSystem = malloc(sizeof(TkWidgetSystem_T));

	HDC DeviceContext = GetDC(HWND_DESKTOP);

	int a = GetSystemMetrics(0); // TO DO: Acquire all necessary system metrics.

	const BOOL b_GetTextMetricsResult = GetTextMetricsA(DeviceContext, &WidgetSystem->TextMetric);

	WidgetSystem->CharTotalWidth  = WidgetSystem->TextMetric.tmAveCharWidth;
	WidgetSystem->CharTotalHeight = WidgetSystem->TextMetric.tmHeight + WidgetSystem->TextMetric.tmExternalLeading;

	const tk_int32_t ReleaseResult = ReleaseDC(HWND_DESKTOP, DeviceContext);
}

void tkTerminateWidgetSystem()
{
	free(WidgetSystem);
}

#endif // TK_PLATFORM_WINDOWS
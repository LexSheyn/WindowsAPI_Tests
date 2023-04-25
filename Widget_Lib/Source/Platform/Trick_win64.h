#pragma once

#include "Core/TrickBase.h"

#if TK_PLATFORM_WINDOWS
#pragma warning( push )
#pragma warning( disable : 4996 ) // Function unsafe.

#include <Windows.h>
#include <Windowsx.h> // Parameter input extraction and GUI.
#include <strsafe.h>  // StringCchPrintfA

#pragma warning( pop )

TK_INLINE TkResult TK_CALL tk_win64_GetLastError()
{
	const DWORD ErrorCode = GetLastError();

	switch (ErrorCode)
	{
		case 0:                       return TK_SUCCESS;
		case ERROR_NOT_ENOUGH_MEMORY: return TK_ERROR_OUT_OF_HOST_MEMORY;
		case ERROR_ACCESS_DENIED:     return TK_ERROR_ACCESS_DENIED;
		case ERROR_FILE_NOT_FOUND:    return TK_ERROR_FILE_NOT_FOUND;
		case ERROR_PATH_NOT_FOUND:    return TK_ERROR_PATH_NOT_FOUND;
		case ERROR_FILE_EXISTS:       return TK_ERROR_FILE_EXISTS;
		case ERROR_ALREADY_EXISTS:    return TK_ERROR_ALREADY_EXISTS;
		
		default:                      return TK_ERROR_UNKNOWN;
	}
}

TK_INLINE void TK_CALL tk_win64_GetErrorMessage(tk_char8_t* MessageBuffer, tk_uint64_t Size)
{
	const DWORD LastError = GetLastError();

	const DWORD CharCount = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM
	                                     | FORMAT_MESSAGE_IGNORE_INSERTS
	                                     , NULL
	                                     , LastError
	                                     , MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
	                                     , (LPSTR)MessageBuffer
	                                     , (DWORD)Size
	                                     , NULL);

	if (CharCount == 0)
	{
		const DWORD FormatMessageError = GetLastError();
	}
}

#endif // TK_PLATFORM_WINDOWS
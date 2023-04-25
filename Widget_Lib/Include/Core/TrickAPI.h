#pragma once

#if _WIN64 && _MSC_VER
	#define TK_PLATFORM_WINDOWS 1
#elif __linux__
	#define TK_PLATFORM_LINUX 1
#endif // _WIN64 && _MSC_VER

#if _M_X64
#define TK_CPU_AMD64 1
#else
#define TK_CPU_AMD64 0
#endif // _M_X64

#if TK_BUILD_DLL
	#if TK_PLATFORM_WINDOWS
		#define TK_API __declspec(dllexport)
	#elif TK_PLATFORM_LINUX
		#define TK_API
	#else
		#define TK_API
	#endif
#else
	#if TK_PLATFORM_WINDOWS
		#define TK_API __declspec(dllimport)
	#elif TK_PLATFORM_LINUX
		#define TK_API
	#else
		#define TK_API
	#endif
#endif // TK_BUILD_DLL

#if _DEBUG
	#define TK_DEBUG 1
#else
	#define TK_DEBUG 0
#endif // _DEBUG

#if TK_DEBUG
#define TK_USE_SIMD 0
#else
#define TK_USE_SIMD 1
#endif

#if TK_PLATFORM_WINDOWS
#define TK_ALIGN(X)     __declspec(align(X))
#define TK_ALIGNMENT(X) __alignof(X)
#else
#define TK_ALIGN(X)     alignas(X)
#define TK_ALIGNMENT(X) alignof(X)
#endif

#define TK_CAST(Type, Value) ((##Type)(Value))

#define TK_BYTES_TO_KIBIBYTES(Bytes) ((Bytes) / 1024.0f)
#define TK_BYTES_TO_MIBIBYTES(Bytes) ((Bytes) / 1024.0f / 1024.0f)
#define TK_BYTES_TO_GIBIBYTES(Bytes) ((Bytes) / 1024.0f / 1024.0f / 1024.0f)

#define TK_KIBIBYTES_TO_BYTES(Kibibytes) ((Kibibytes) * 1024)
#define TK_MIBIBYTES_TO_BYTES(Mibibytes) ((Mibibytes) * 1024 * 1024)
#define TK_GIBIBYTES_TO_BYTES(Gibibytes) ((Gibibytes) * 1024 * 1024 * 1024)

#define TK_CLAMP(Value, Min, Max) ((Value) < (Min)) ? (Min) : ((Value) > (Max)) ? (Max) : (Value)

#define TK_DEFINE_HANDLE(Object) typedef struct Object##_T* Object

#define TK_NULL_HANDLE ((void*)0)

#define TK_TEXT(Value) #Value

#if TK_PLATFORM_WINDOWS
#define TK_INLINE    __forceinline
#define TK_NO_INLINE __declspec(noinline)
#elif TK_PLATFORM_LINUX
#define TK_INLINE    __always_inline
#define TK_NO_INLINE noinline
#else
#define TK_INLINE    static inline
#define TK_NO_INLINE
#endif

#define TK_CALL    __fastcall
#define TK_VA_CALL __cdecl

#if _MSC_VER
	#define TK_FUNCTION __FUNCTION__
#else
	#define TK_FUNCTION __func__
#endif

// Launch arguments:

#define TK_LAUNCH_LOG_PARALLEL "log_parallel"
#define TK_LAUNCH_LOG_TO_FILE  "log_to_file"

//#define TK_ENDIAN_LITTLE (0x01'02'03'04 == 16909060)
//#define TK_ENDIAN_BIG    (0x04'03'02'01 == 16909060)
//#define TK_ENDIAN_PDP    (0x02'01'04'03 == 16909060)
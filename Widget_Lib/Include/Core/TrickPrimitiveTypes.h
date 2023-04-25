#pragma once

typedef signed   char      tk_int8_t;
typedef signed   short     tk_int16_t;
typedef signed   int       tk_int32_t;
typedef signed   long long tk_int64_t;

typedef unsigned char      tk_uint8_t;
typedef unsigned short     tk_uint16_t;
typedef unsigned int       tk_uint32_t;
typedef unsigned long long tk_uint64_t;

typedef char               tk_char8_t;
typedef tk_uint16_t        tk_char16_t;
typedef tk_uint32_t        tk_char32_t;

typedef signed   long      tk_long32_t;
typedef unsigned long      tk_ulong32_t;

typedef float              tk_float32_t;
typedef double             tk_float64_t;

static_assert(sizeof(tk_int8_t)    == 1, "Expected to be 1 byte.");
static_assert(sizeof(tk_int16_t)   == 2, "Expected to be 2 bytes.");
static_assert(sizeof(tk_int32_t)   == 4, "Expected to be 4 bytes.");
static_assert(sizeof(tk_int64_t)   == 8, "Expected to be 8 bytes.");

static_assert(sizeof(tk_uint8_t)   == 1, "Expected to be 1 byte.");
static_assert(sizeof(tk_uint16_t)  == 2, "Expected to be 2 bytes.");
static_assert(sizeof(tk_uint32_t)  == 4, "Expected to be 4 bytes.");
static_assert(sizeof(tk_uint64_t)  == 8, "Expected to be 8 bytes.");

static_assert(sizeof(tk_char8_t)   == 1, "Expected to be 1 byte.");
static_assert(sizeof(tk_char16_t)  == 2, "Expected to be 2 bytes.");
static_assert(sizeof(tk_char32_t)  == 4, "Expected to be 4 bytes.");

static_assert(sizeof(tk_long32_t)  == 4, "Expected to be 4 bytes.");
static_assert(sizeof(tk_ulong32_t) == 4, "Expected to be 4 bytes.");

static_assert(sizeof(tk_float32_t) == 4, "Expected to be 4 bytes.");
static_assert(sizeof(tk_float64_t) == 8, "Expected to be 8 bytes.");

typedef tk_uint8_t  tk_bool8_t;
typedef tk_uint32_t tk_bool32_t;
typedef tk_uint64_t tk_bool64_t;

typedef tk_uint8_t  tk_byte8_t;

typedef tk_uint64_t tk_size_t;
typedef tk_uint32_t TkFlags;

#define TK_FALSE 0
#define TK_TRUE  1
#define TK_NULLPTR ((void*)0)

// Limits:

//#include <limits.h>

#define TK_INT8_MAX  0x7F
#define TK_INT16_MAX 0x7FFF
#define TK_INT32_MAX 0x7FFFFFFF
#define TK_INT64_MAX 0x7FFFFFFFFFFFFFFF

#define TK_INT8_MIN  (-TK_INT8_MAX  - 1)
#define TK_INT16_MIN (-TK_INT16_MAX - 1)
#define TK_INT32_MIN (-TK_INT32_MAX - 1)
#define TK_INT64_MIN (-TK_INT64_MAX - 1)

#define TK_UINT8_MAX  0xFF
#define TK_UINT16_MAX 0xFFFF
#define TK_UINT32_MAX 0xFFFFFFFF
#define TK_UINT64_MAX 0xFFFFFFFFFFFFFFFF

//#include <float.h>

#define TK_FLOAT32_MAX 3.402823466e+38f
#define TK_FLOAT64_MAX 1.7976931348623158e+308

#define TK_FLOAT32_EPSILON 1.192092896e-7f
#define TK_FLOAT64_EPSILON 2.2204460492503131e-16

// Little endian
// Sign 1 bit    Value 31 bits
// [0]           [0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0]
// 31            30                                                                                        0
#define TK_INT32_BINARY

// Little endian
// Sign 1 bit    Exponent 8 bits             Fraction 23 bits
// [0]           [0][1][1][1][1][1][0][0]    [0][1][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0]
// 31            30                   23     22                                                                0
// This is a representation of 0.15625
#define TK_FLOAT32_BINARY_IEEE_754

// Little endian
// Sign 1 bit    Exponent 11 bits    Fraction 52 bits
// 0             00000000000         0000000000000000000000000000000000000000000000000000
// 63            62        52        51                                                 0
#define TK_FLOAT64_BINARY_IEEE_754

typedef enum TkMaskFloat32
{
	  TK_MASK_FLOAT32_EXPONENT = 0b1111111100000000000000000000000
	, TK_MASK_FLOAT32_FRACTION = 0b0000000011111111111111111111111
} TkMaskFloat32;
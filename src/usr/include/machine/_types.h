// This file is placed in the public domain.
//
// This file is a replacement for sys/_types.h.

#pragma once

// Some unusual type names used in include/<arch>/_types.h.
// Defined here again, similarly to how they're defined in stdint.h.
typedef __INT8_TYPE__    __int8_t;
typedef __INT16_TYPE__   __int16_t;
typedef __INT32_TYPE__   __int32_t;
typedef __INT64_TYPE__   __int64_t;
typedef __UINT8_TYPE__   __uint8_t;
typedef __UINT16_TYPE__  __uint16_t;
typedef __UINT32_TYPE__  __uint32_t;
typedef __UINT64_TYPE__  __uint64_t;

// Old spelling, used in some older source files as alternative to the standard
// uintN_t spelling.
typedef __UINT8_TYPE__  u_int8_t;
typedef __UINT16_TYPE__ u_int16_t;
typedef __UINT32_TYPE__ u_int32_t;
typedef __UINT64_TYPE__ u_int64_t;

// Some typedefs for types that have since been standardized.
typedef __INTPTR_TYPE__   __darwin_intptr_t;
typedef __SIZE_TYPE__     __darwin_size_t;
typedef __builtin_va_list __darwin_va_list;
typedef __WCHAR_TYPE__    __darwin_wchar_t;

// These types are defined separately for i386 and arm, but are actually
// defined as the same type.
typedef unsigned long    __darwin_clock_t;
typedef int              __darwin_ct_rune_t;
typedef unsigned int     __darwin_natural_t;
typedef __darwin_wchar_t __darwin_rune_t;
typedef long             __darwin_ssize_t;
typedef long             __darwin_time_t;

// This file is placed in the public domain.
//
// This file replaces include/stdint.h from the Libc source package. The reason
// is that the original stdint.h header file has an unclear copyright: while
// the source Libc package is licensed under the APSL 2.0, the file itself only
// says "all rights reserved".

#pragma once

// This file is based on stdint.h as specified here:
//   https://pubs.opengroup.org/onlinepubs/009604599/basedefs/stdint.h.html
// The macros used here can be found in the GCC documentation:
//   https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
// Note that Clang doesn't support all of these predefined macros.

// Exact-width integer types:
typedef __INT8_TYPE__   int8_t;
typedef __INT16_TYPE__  int16_t;
typedef __INT32_TYPE__  int32_t;
typedef __INT64_TYPE__  int64_t;
typedef __UINT8_TYPE__  uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT64_TYPE__ uint64_t;

// Minimum-width integer types:
typedef __INT_LEAST8_TYPE__   int_least8_t;
typedef __INT_LEAST16_TYPE__  int_least16_t;
typedef __INT_LEAST32_TYPE__  int_least32_t;
typedef __INT_LEAST64_TYPE__  int_least64_t;
typedef __UINT_LEAST8_TYPE__  uint_least8_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;
typedef __UINT_LEAST64_TYPE__ uint_least64_t;

// Fastest minimum-width integer types:
typedef __INT_FAST8_TYPE__   int_fast8_t;
typedef __INT_FAST16_TYPE__  int_fast16_t;
typedef __INT_FAST32_TYPE__  int_fast32_t;
typedef __INT_FAST64_TYPE__  int_fast64_t;
typedef __UINT_FAST8_TYPE__  uint_fast8_t;
typedef __UINT_FAST16_TYPE__ uint_fast16_t;
typedef __UINT_FAST32_TYPE__ uint_fast32_t;
typedef __UINT_FAST64_TYPE__ uint_fast64_t;

// Integer types capable of holding object pointers:
typedef __INTPTR_TYPE__  intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

// Greatest-width integer types:
typedef __INTMAX_TYPE__  intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;

// Limits of exact-width integer types:
#define INT8_MIN (-INT8_MAX - 1)
#define INT16_MIN (-INT16_MAX - 1)
#define INT32_MIN (-INT32_MAX - 1)
#define INT64_MIN (-INT64_MAX - 1)
#define INT8_MAX __INT8_MAX__
#define INT16_MAX __INT16_MAX__
#define INT32_MAX __INT32_MAX__
#define INT64_MAX __INT64_MAX__
#define UINT8_MAX __UINT8_MAX__
#define UINT16_MAX __UINT16_MAX__
#define UINT32_MAX __UINT32_MAX__
#define UINT64_MAX __UINT64_MAX__

// Limits of minimum-width integer types:
#define INT_LEAST8_MIN (-INT_LEAST8_MAX - 1)
#define INT_LEAST16_MIN (-INT_LEAST16_MAX - 1)
#define INT_LEAST32_MIN (-INT_LEAST32_MAX - 1)
#define INT_LEAST64_MIN (-INT_LEAST64_MAX - 1)
#define INT_LEAST8_MAX __INT_LEAST8_MAX__
#define INT_LEAST16_MAX __INT_LEAST16_MAX__
#define INT_LEAST32_MAX __INT_LEAST32_MAX__
#define INT_LEAST64_MAX __INT_LEAST64_MAX__
#define UINT_LEAST8_MAX __UINT_LEAST8_MAX__
#define UINT_LEAST16_MAX __UINT_LEAST16_MAX__
#define UINT_LEAST32_MAX __UINT_LEAST32_MAX__
#define UINT_LEAST64_MAX __UINT_LEAST64_MAX__

// Limits of fastest minimum-width integer types:
#define INT_FAST8_MIN (-INT_FAST8_MAX - 1)
#define INT_FAST16_MIN (-INT_FAST16_MAX - 1)
#define INT_FAST32_MIN (-INT_FAST32_MAX - 1)
#define INT_FAST64_MIN (-INT_FAST64_MAX - 1)
#define INT_FAST8_MAX __INT_FAST8_MAX__
#define INT_FAST16_MAX __INT_FAST16_MAX__
#define INT_FAST32_MAX __INT_FAST32_MAX__
#define INT_FAST64_MAX __INT_FAST64_MAX__
#define UINT_FAST8_MAX __UINT_FAST8_MAX__
#define UINT_FAST16_MAX __UINT_FAST16_MAX__
#define UINT_FAST32_MAX __UINT_FAST32_MAX__
#define UINT_FAST64_MAX __UINT_FAST64_MAX__

// Limits of pointer and greatest-width integer types:
#define INTPTR_MIN (-INTPTR_MAX - 1)
#define INTPTR_MAX __INTPTR_MAX__
#define UINTPTR_MAX __UINTPTR_MAX__
#define INTMAX_MIN (-INTMAX_MAX - 1)
#define INTMAX_MAX __INTMAX_MAX__
#define UINTMAX_MAX __UINTMAX_MAX__

// Limits of ptrdiff_t:
#define PTRDIFF_MIN (-__PTRDIFF_MAX__ - 1)
#define PTRDIFF_MAX __PTRDIFF_MAX__

// Limits of sig_atomic_t:
#define SIG_ATOMIC_MIN (-__SIG_ATOMIC_MAX__ - 1)
#define SIG_ATOMIC_MAX __SIG_ATOMIC_MAX__

// Limits of size_t:
#define SIZE_MAX __SIZE_MAX__

// Limits of wchar_t:
#define WCHAR_MIN __WCHAR_MIN__
#define WCHAR_MAX __WCHAR_MAX__

// Limits of wint_t:
#define WINT_MIN __WINT_MIN__
#define WINT_MAX __WINT_MAX__

// Integer constant expressions:
// Suffixes are fixed for 64-bit Darwin. Pasting __INT64_C_SUFFIX__ breaks if
// user code defines L or LL. https://github.com/llvm/llvm-project/issues/85995
#define INT8_C(value) value
#define INT16_C(value) value
#define INT32_C(value) value
#define INT64_C(value) value##LL
#define UINT8_C(value) value
#define UINT16_C(value) value
#define UINT32_C(value) value##U
#define UINT64_C(value) value##ULL
#define INTMAX_C(value) value##L
#define UINTMAX_C(value) value##UL

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

// TODO: define constants like INT64_C and UINTMAX_C.

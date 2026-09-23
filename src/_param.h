// This file is placed in the public domain.
//
// This file is a replacement for arm/_param.h.

#pragma once

#include <machine/_types.h>

// Round p (pointer or byte index) up to a correctly-aligned value for all
// data types (int, long, ...). The result is unsigned and must be cast to
// any desired pointer type.
#define __DARWIN_ALIGNBYTES     (sizeof(__darwin_size_t) - 1)
#define __DARWIN_ALIGN(p)       ((__darwin_size_t)((__darwin_size_t)(p) + __DARWIN_ALIGNBYTES) &~ __DARWIN_ALIGNBYTES)

#define __DARWIN_ALIGNBYTES32   (sizeof(__uint32_t) - 1)
#define __DARWIN_ALIGN32(p)     ((__darwin_size_t)((__darwin_size_t)(p) + __DARWIN_ALIGNBYTES32) &~ __DARWIN_ALIGNBYTES32)

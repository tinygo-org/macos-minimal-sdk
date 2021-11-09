// This file is placed in the public domain.
//
// This file replaces machine/signal.h, and with that avoids the need for
// i386/signal.h and arm/signal.h.

#pragma once

// Defined as int on both i386 and arm.
typedef int sig_atomic_t;

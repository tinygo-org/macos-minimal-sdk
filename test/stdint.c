// User macros must not change the integer constants.
// https://github.com/llvm/llvm-project/issues/85995
#define L "L"
#define U "U"
#define UL "UL"
#define LL "LL"
#define ULL "ULL"

#include <stdint.h>

#ifdef __cplusplus
template <typename A, typename B> struct same_type { static const bool value = false; };
template <typename A> struct same_type<A, A> { static const bool value = true; };
#define SAME_TYPE(a, b) same_type<__typeof__(a), __typeof__(b)>::value
#define CHECK(expression) static_assert(expression, #expression)
#else
#define SAME_TYPE(a, b) __builtin_types_compatible_p(__typeof__(a), __typeof__(b))
#define CHECK(expression) _Static_assert(expression, #expression)
#endif

#define CHECK_LIMITS(name, signed_type, unsigned_type) \
    CHECK(name##_MAX == (signed_type)(((unsigned_type)-1) >> 1)); \
    CHECK(name##_MIN == -name##_MAX - 1); \
    CHECK(U##name##_MAX == (unsigned_type)-1)

CHECK_LIMITS(INT8, int8_t, uint8_t);
CHECK_LIMITS(INT16, int16_t, uint16_t);
CHECK_LIMITS(INT32, int32_t, uint32_t);
CHECK_LIMITS(INT64, int64_t, uint64_t);
CHECK_LIMITS(INT_LEAST8, int_least8_t, uint_least8_t);
CHECK_LIMITS(INT_LEAST16, int_least16_t, uint_least16_t);
CHECK_LIMITS(INT_LEAST32, int_least32_t, uint_least32_t);
CHECK_LIMITS(INT_LEAST64, int_least64_t, uint_least64_t);
CHECK_LIMITS(INT_FAST8, int_fast8_t, uint_fast8_t);
CHECK_LIMITS(INT_FAST16, int_fast16_t, uint_fast16_t);
CHECK_LIMITS(INT_FAST32, int_fast32_t, uint_fast32_t);
CHECK_LIMITS(INT_FAST64, int_fast64_t, uint_fast64_t);
CHECK_LIMITS(INTPTR, intptr_t, uintptr_t);
CHECK_LIMITS(INTMAX, intmax_t, uintmax_t);

#define CHECK_CONSTANT(name, type) \
    CHECK(name##_C(123) == 123); \
    CHECK(SAME_TYPE(name##_C(123), +(type)0))

CHECK_CONSTANT(INT8, int_least8_t);
CHECK_CONSTANT(INT16, int_least16_t);
CHECK_CONSTANT(INT32, int_least32_t);
CHECK_CONSTANT(INT64, int_least64_t);
CHECK_CONSTANT(UINT8, uint_least8_t);
CHECK_CONSTANT(UINT16, uint_least16_t);
CHECK_CONSTANT(UINT32, uint_least32_t);
CHECK_CONSTANT(UINT64, uint_least64_t);
CHECK_CONSTANT(INTMAX, intmax_t);
CHECK_CONSTANT(UINTMAX, uintmax_t);

#if INT32_MIN != (-2147483647 - 1) || UINT32_MAX != UINT32_C(4294967295)
#error incorrect 32-bit integer macros
#endif

#if INT64_MAX != INT64_C(9223372036854775807) || UINT64_MAX != UINT64_C(18446744073709551615)
#error incorrect 64-bit integer macros
#endif

#ifndef HELPERS_H

#define HELPERS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "log.h"

#define XSTRINGIZE(a) STRINGIZE(a)
#define STRINGIZE(a) #a
#define UNUSED(x) (void)(x)

#define ASSERT(expr) \
    if (expr) \
        {} \
    else \
    { \
        log_error("Assertion failed with %s!!!", XSTRINGIZE(expr)); \
        print_trace(); \
    } \

void print_trace(void);

#ifdef __cplusplus
}
#endif

#endif
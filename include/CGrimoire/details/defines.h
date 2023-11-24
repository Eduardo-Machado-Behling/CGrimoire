#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t byte_t;

#define CG_SAFE_ALLOC(ptr, size, onFail)                                                                                                                       \
    ptr = malloc(size);                                                                                                                                        \
    if (!ptr) {                                                                                                                                                \
        onFail;                                                                                                                                                \
    }

#define CG_AS_MEMORY(x) (byte_t *)&(x)

#define CG_SAFE_CALL(x, onFail)                                                                                                                                \
    if (!(x)) {                                                                                                                                                \
        onFail;                                                                                                                                                \
    }
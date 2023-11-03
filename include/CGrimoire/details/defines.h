#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t byte_t;

#define SAFE_ALLOC(ptr, size, onFail)                                                                                                                          \
    ptr = malloc(size);                                                                                                                                        \
    if (!ptr) {                                                                                                                                                \
        onFail;                                                                                                                                                \
    }

#define AS_MEMORY(x) (byte_t *)&x
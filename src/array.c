#include "CGrimoire/array.h"
#include <stdio.h>

typedef struct cg_array_t {
    struct {
        byte_t *mem;
        size_t size;
    } data;
    size_t capacity;
} cg_array_t;

cg_array_t *cg_array_create(size_t capacity, size_t element_size_in_bytes) {
    cg_array_t *array;
    CG_SAFE_ALLOC(array, sizeof(cg_array_t), return NULL);

    CG_SAFE_ALLOC(array->data.mem, element_size_in_bytes * capacity, free(array); return NULL);
    array->data.size = element_size_in_bytes;

    array->capacity = capacity;

    return array;
}

cg_array_t *cg_array_copy(const cg_array_t *other) {
    if (!other)
        return NULL;

    cg_array_t *array;
    CG_SAFE_ALLOC(array, sizeof(cg_array_t), return NULL);

    array->data.size = other->data.size;
    array->capacity = other->capacity;

    CG_SAFE_ALLOC(array->data.mem, array->capacity * array->data.size, free(array); return NULL);
    memcpy(array->data.mem, other->data.mem, array->capacity * array->data.size);

    return array;
}

bool cg_array_reserve(cg_array_t *array, size_t new_size) {
    if (!array)
        return false;

    array->capacity = new_size;
    if (!array->data.mem)
        array->data.mem = calloc(array->capacity, array->data.size);
    else
        array->data.mem = realloc(array->data.mem, array->capacity * array->data.size);

    if (!array->data.mem)
        return false;

    return true;
}

bool cg_array_at(const cg_array_t *array, size_t index, byte_t *dest) {
    if (!array || !array->data.mem)
        return false;

    if (!(index < array->capacity))
        return false;

    byte_t *start_data = array->data.mem + index * array->data.size;
    for (size_t i = 0; i < array->data.size; i++)
        dest[i] = start_data[i];

    return true;
}

bool cg_array_insert(cg_array_t *array, size_t index, const byte_t *data) {
    if (!array || !array->data.mem)
        return false;

    if (!(index < array->capacity))
        return false;

    size_t is = index * array->data.size;
    for (size_t i = 0; i < array->data.size; i++)
        array->data.mem[is + i] = data[i];

    return true;
}

size_t cg_array_capacity(const cg_array_t *array) {
    if (!array)
        return CG_ARRAY_INVALID_POS;
    return array->capacity;
}

size_t cg_array_element_size(const cg_array_t *array) {
    if (!array)
        return CG_ARRAY_INVALID_POS;
    return array->data.size;
}

bool cg_array_assign(cg_array_t *array, const byte_t *c_array) {
    if (!array || !c_array)
        return false;

    memcpy(array->data.mem, c_array, array->capacity * array->data.size);
    return true;
}

bool cg_array_assign_range(cg_array_t *array, size_t start, const byte_t *c_array, size_t c_array_sizes) {
    if (!array || !c_array)
        return false;

    int diff = start + c_array_sizes - array->capacity;
    if (diff > 0)
        cg_array_reserve(array, array->capacity + diff);

    byte_t *array_start = array->data.mem + start * array->data.size;
    memcpy(array_start, c_array, c_array_sizes * array->data.size);
    return true;
}

bool cg_array_swap(cg_array_t *dest, cg_array_t *source) {
    byte_t *mem_temp = dest->data.mem;
    dest->data.mem = source->data.mem;
    source->data.mem = mem_temp;

    size_t data_size_temp = dest->data.size;
    dest->data.size = source->data.size;
    source->data.size = data_size_temp;

    size_t capacity_temp = dest->capacity;
    dest->capacity = source->capacity;
    source->capacity = capacity_temp;

    return true;
}
bool cg_array_fill(cg_array_t *array, const byte_t *value) {
    if (!array || !value)
        return false;

    for (size_t i = 0; i < array->capacity; i++) {
        size_t index = i * array->data.size;
        memcpy(array->data.mem + index, value, array->data.size);
    }

    return true;
}

bool cg_array_resize(cg_array_t *array, size_t new_size, const byte_t *data) {
    if (!array || !data)
        return false;

    if (new_size > array->capacity) {
        if (!array->data.mem)
            array->data.mem = calloc(new_size, array->data.size);
        else
            array->data.mem = realloc(array->data.mem, new_size * array->data.size);

        if (!array->data.mem)
            return false;

        for (size_t i = array->capacity; i < new_size; i++)
            memcpy(array->data.mem + (i * array->data.size), data, array->data.size);

        array->capacity = new_size;
    }

    return true;
}

void cg_array_destroy(cg_array_t *array) {
    if (!array)
        return;

    if (array->data.mem)
        free(array->data.mem);
    free(array);
}
#include "CGrimoire/array.h"

typedef struct cg_array_t {
    struct {
        byte_t *mem;
        size_t size;
    } data;
    size_t capacity;
} cg_array_t;

cg_array_t *cg_array_create(size_t capacity, size_t element_size_in_bytes) {
    cg_array_t *array;
    SAFE_ALLOC(array, sizeof(cg_array_t), return NULL);

    SAFE_ALLOC(array->data.mem, element_size_in_bytes * capacity, free(array); return NULL);
    array->data.size = element_size_in_bytes;

    array->capacity = capacity;

    return array;
}

cg_array_t *cg_array_copy(const cg_array_t *other) {
    if (!other)
        return NULL;

    cg_array_t *array;
    SAFE_ALLOC(array, sizeof(cg_array_t), return NULL);

    array->data.size = other->data.size;
    array->capacity = other->capacity;

    SAFE_ALLOC(array->data.mem, array->capacity * array->data.size, free(array); return NULL);
    memcpy(array->data.mem, other->data.mem, array->capacity * array->data.size);

    return array;
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

size_t cg_array_size(const cg_array_t *array) {
    if (!array)
        return CG_ARRAY_NPOS;
    return array->capacity;
}

bool cg_array_assign(cg_array_t *array, const byte_t *c_array) {
    if (!array || !c_array)
        return false;

    memcpy(array->data.mem, c_array, array->capacity * array->data.size);
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

void cg_array_destroy(cg_array_t *array) {
    if (!array)
        return;

    if (array->data.mem)
        free(array->data.mem);
    free(array);
}
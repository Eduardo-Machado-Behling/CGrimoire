#include "CGrimoire/array.h"
#include <stdio.h>

typedef struct cg_array_t {
    struct {
        byte_t *mem;
        size_t size;
    } data;
    size_t capacity;

    iterator_t *end;
    iterator_t *begin;

} cg_array_t;

cg_array_t *cg_array_create(size_t capacity, size_t element_size_in_bytes) {
    cg_array_t *array;
    CG_SAFE_ALLOC(array, sizeof(cg_array_t), return NULL);

    CG_SAFE_ALLOC(array->data.mem, element_size_in_bytes * capacity, free(array); return NULL);
    array->data.size = element_size_in_bytes;

    array->capacity = capacity;
    array->end = NULL;
    array->begin = NULL;

    return array;
}

cg_array_t *cg_array_copy(cg_array_t *array, const cg_array_t *other) {
    if (!array)
        array = cg_array_create(other->capacity, other->data.size);

    memcpy(array->data.mem, other->data.mem, array->capacity * array->data.size);

    return array;
}

cg_array_t *cg_array_move(cg_array_t *array, cg_array_t **other) {
    if (!array)
        CG_SAFE_ALLOC(array, sizeof(cg_array_t), return NULL);

    array->data.mem = (*other)->data.mem;
    array->data.size = (*other)->data.size;
    array->capacity = (*other)->capacity;
    array->end = (*other)->end;
    array->begin = (*other)->begin;

    (*other)->data.mem = NULL;
    (*other)->end = NULL;
    (*other)->begin = NULL;

    cg_array_destroy(*other);
    *other = NULL;

    return array;
}

cg_array_t *cg_array_reserve(cg_array_t *array, size_t new_size) {
    if (!array)
        return NULL;

    array->capacity = new_size;
    if (!array->data.mem)
        array->data.mem = calloc(array->capacity, array->data.size);
    else
        array->data.mem = realloc(array->data.mem, array->capacity * array->data.size);

    if (!array->data.mem)
        return NULL;

    return array;
}

const cg_array_t *cg_array_at(const cg_array_t *array, size_t index, byte_t *dest) {
    if (!array || !array->data.mem)
        return NULL;

    if (!(index < array->capacity))
        return NULL;

    byte_t *start_data = array->data.mem + index * array->data.size;
    for (size_t i = 0; i < array->data.size; i++)
        dest[i] = start_data[i];

    return array;
}

cg_array_t *cg_array_change(cg_array_t *array, size_t index, const byte_t *data) {
    if (!array || !array->data.mem)
        return NULL;

    if (!(index < array->capacity))
        return NULL;

    size_t is = index * array->data.size;
    for (size_t i = 0; i < array->data.size; i++)
        array->data.mem[is + i] = data[i];

    return array;
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

cg_array_t *cg_array_assign(cg_array_t *array, const byte_t *c_array) {
    if (!array || !c_array)
        return NULL;

    memcpy(array->data.mem, c_array, array->capacity * array->data.size);
    return array;
}

cg_array_t *cg_array_assign_range(cg_array_t *array, size_t start, const byte_t *c_array, size_t c_array_sizes) {
    if (!array || !c_array)
        return NULL;

    int diff = start + c_array_sizes - array->capacity;
    if (diff > 0)
        cg_array_reserve(array, array->capacity + diff);

    byte_t *array_start = array->data.mem + start * array->data.size;
    memcpy(array_start, c_array, c_array_sizes * array->data.size);
    return array;
}

iterator_t *cg_array_begin(cg_array_t *array, iterator_t *iterator) {
    if (!iterator)
        iterator = cg_iterator_create();

    cg_iterator_set_addr(iterator, array->data.mem);
    cg_iterator_set_element_size(iterator, array->data.size);

    return iterator;
}
iterator_t *cg_array_end(cg_array_t *array, iterator_t *iterator) {
    if (!iterator)
        iterator = cg_iterator_create();

    cg_iterator_set_addr(iterator, array->data.mem + (array->capacity * array->data.size));
    cg_iterator_set_element_size(iterator, array->data.size);

    return iterator;
}

const iterator_t *cg_array_cbegin(cg_array_t *array) {
    if (!array)
        return NULL;

    if (!array->begin) {
        CG_SAFE_CALL(array->begin = cg_iterator_create(), return NULL;);
        cg_iterator_set_addr(array->begin, array->data.mem);
        cg_iterator_set_element_size(array->begin, array->data.size);
    }
    return array->begin;
}
const iterator_t *cg_array_cend(cg_array_t *array) {
    if (!array)
        return NULL;

    if (!array->end) {
        CG_SAFE_CALL(array->end = cg_iterator_create(), return NULL;);
        cg_iterator_set_element_size(array->end, array->data.size);
    }

    cg_iterator_set_addr(array->end, array->data.mem + (array->capacity * array->data.size));

    return array->end;
}

cg_array_t *cg_array_swap(cg_array_t *dest, cg_array_t *source) {
    byte_t *mem_temp = dest->data.mem;
    dest->data.mem = source->data.mem;
    source->data.mem = mem_temp;

    size_t data_size_temp = dest->data.size;
    dest->data.size = source->data.size;
    source->data.size = data_size_temp;

    size_t capacity_temp = dest->capacity;
    dest->capacity = source->capacity;
    source->capacity = capacity_temp;

    return dest;
}
cg_array_t *cg_array_fill(cg_array_t *array, const byte_t *value) {
    if (!array || !value)
        return NULL;

    for (size_t i = 0; i < array->capacity; i++) {
        size_t index = i * array->data.size;
        memcpy(array->data.mem + index, value, array->data.size);
    }

    return array;
}

cg_array_t *cg_array_resize(cg_array_t *array, size_t new_size, const byte_t *data) {
    if (!array || !data)
        return NULL;

    if (new_size > array->capacity) {
        if (!array->data.mem)
            array->data.mem = calloc(new_size, array->data.size);
        else
            array->data.mem = realloc(array->data.mem, new_size * array->data.size);

        if (!array->data.mem)
            return NULL;

        for (size_t i = array->capacity; i < new_size; i++)
            memcpy(array->data.mem + (i * array->data.size), data, array->data.size);

        array->capacity = new_size;
    }

    return array;
}

void cg_array_destroy(cg_array_t *array) {
    if (!array)
        return;

    if (array->data.mem)
        free(array->data.mem);
    if (array->end)
        cg_iterator_destroy(array->end);
    if (array->begin)
        cg_iterator_destroy(array->begin);
    free(array);
}
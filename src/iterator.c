#include "CGrimoire/iterator.h"

typedef struct iterator_t {
    byte_t *data;
    size_t element_size;
} iterator_t;

iterator_t *cg_iterator_create() {
    iterator_t *iter;
    CG_SAFE_ALLOC(iter, sizeof(iterator_t), return NULL;);

    iter->data = NULL;
    iter->element_size = 0;

    return iter;
}

iterator_t *cg_iterator_set_element_size(iterator_t *iterator, size_t data_size) {
    if (!iterator)
        return NULL;

    iterator->element_size = data_size;
    return iterator;
}
iterator_t *cg_iterator_set_addr(iterator_t *iterator, void *data) {
    if (!iterator)
        return NULL;

    iterator->data = data;
    return iterator;
}

iterator_t *cg_iterator_set_data(iterator_t *iterator, const void *data) {
    if (!cg_iterator_valid(iterator) || !data)
        return NULL;

    memcpy(iterator->data, data, iterator->element_size);
    return iterator;
}

const void *cg_iterator_get_data(iterator_t *iterator) {
    if (!iterator || !iterator->data)
        return NULL;

    return iterator->data;
}

iterator_t *cg_iterator_next(iterator_t *iterator, size_t amount) {
    if (!cg_iterator_valid(iterator))
        return NULL;

    iterator->data += iterator->element_size * amount;
    return iterator;
}
iterator_t *cg_iterator_prev(iterator_t *iterator, size_t amount) {
    if (!cg_iterator_valid(iterator))
        return NULL;

    iterator->data -= iterator->element_size * amount;
    return iterator;
}

size_t cg_iterator_distance(const iterator_t *from, const iterator_t *to) {
    if (!cg_iterator_valid(from) || !cg_iterator_valid(to))
        return NOT_A_DISTANCE;

    return to->data - from->data;
}

bool cg_iterator_valid(const iterator_t *iterator) { return iterator && iterator->data && iterator->element_size > 0; }

void cg_iterator_destroy(iterator_t *iterator) {
    if (!iterator)
        return;
    iterator->data = NULL;

    free(iterator);
}
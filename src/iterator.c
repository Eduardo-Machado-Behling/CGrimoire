#include "CGrimoire/iterator.h"

typedef struct cg_iterator_t {
    byte_t *data;
    size_t element_size;
} cg_iterator_t;

cg_iterator_t *cg_iterator_create() {
    cg_iterator_t *iter;
    CG_SAFE_ALLOC(iter, sizeof(cg_iterator_t), return NULL;);

    iter->data = NULL;
    iter->element_size = 0;

    return iter;
}

cg_iterator_t *cg_iterator_set_element_size(cg_iterator_t *iterator, size_t data_size) {
    if (!iterator)
        return NULL;

    iterator->element_size = data_size;
    return iterator;
}
cg_iterator_t *cg_iterator_set_addr(cg_iterator_t *iterator, void *data) {
    if (!iterator)
        return NULL;

    iterator->data = data;
    return iterator;
}

cg_iterator_t *cg_iterator_set_data(cg_iterator_t *iterator, const void *data) {
    if (!cg_iterator_valid(iterator) || !data)
        return NULL;

    memcpy(iterator->data, data, iterator->element_size);
    return iterator;
}

const void *cg_iterator_get_data(cg_iterator_t *iterator) {
    if (!iterator || !iterator->data)
        return NULL;

    return iterator->data;
}

cg_iterator_t *cg_iterator_next(cg_iterator_t *iterator, size_t amount) {
    if (!cg_iterator_valid(iterator))
        return NULL;

    iterator->data += iterator->element_size * amount;
    return iterator;
}
cg_iterator_t *cg_iterator_prev(cg_iterator_t *iterator, size_t amount) {
    if (!cg_iterator_valid(iterator))
        return NULL;

    iterator->data -= iterator->element_size * amount;
    return iterator;
}

size_t cg_iterator_distance(const cg_iterator_t *from, const cg_iterator_t *to) {
    if (!cg_iterator_valid(from) || !cg_iterator_valid(to))
        return NOT_A_DISTANCE;

    return to->data - from->data;
}

bool cg_iterator_valid(const cg_iterator_t *iterator) { return iterator && iterator->data && iterator->element_size > 0; }

void cg_iterator_destroy(cg_iterator_t *iterator) {
    if (!iterator)
        return;
    iterator->data = NULL;

    free(iterator);
}
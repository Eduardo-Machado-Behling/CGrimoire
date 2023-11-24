#pragma once

#include "CGrimoire/details/defines.h"

typedef struct iterator_t iterator_t;

#define NOT_A_DISTANCE SIZE_MAX
#define CG_ITERATOR_GET_DATA(iter, datatype) *((datatype *)cg_iterator_get_data(iter))

iterator_t *cg_iterator_create();

iterator_t *cg_iterator_set_element_size(iterator_t *iterator, size_t data_size);
iterator_t *cg_iterator_set_addr(iterator_t *iterator, void *data);
iterator_t *cg_iterator_set_data(iterator_t *iterator, const void *data);

const void *cg_iterator_get_data(iterator_t *iterator);

iterator_t *cg_iterator_next(iterator_t *iterator, size_t amount);
iterator_t *cg_iterator_prev(iterator_t *iterator, size_t amount);
size_t cg_iterator_distance(const iterator_t *from, const iterator_t *to);

bool cg_iterator_valid(const iterator_t *iterator);

void cg_iterator_destroy(iterator_t *iterator);

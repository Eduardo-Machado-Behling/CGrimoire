#pragma once

#include "CGrimoire/details/defines.h"

typedef struct cg_iterator_t cg_iterator_t;

#define NOT_A_DISTANCE SIZE_MAX
#define CG_ITERATOR_GET_DATA(iter, datatype) *((datatype *)cg_iterator_get_data(iter))

cg_iterator_t *cg_iterator_create();

cg_iterator_t *cg_iterator_set_element_size(cg_iterator_t *iterator, size_t data_size);
cg_iterator_t *cg_iterator_set_addr(cg_iterator_t *iterator, void *data);
cg_iterator_t *cg_iterator_set_data(cg_iterator_t *iterator, const void *data);

const void *cg_iterator_get_data(cg_iterator_t *iterator);

cg_iterator_t *cg_iterator_next(cg_iterator_t *iterator, size_t amount);
cg_iterator_t *cg_iterator_prev(cg_iterator_t *iterator, size_t amount);
size_t cg_iterator_distance(const cg_iterator_t *from, const cg_iterator_t *to);

bool cg_iterator_valid(const cg_iterator_t *iterator);

void cg_iterator_destroy(cg_iterator_t *iterator);

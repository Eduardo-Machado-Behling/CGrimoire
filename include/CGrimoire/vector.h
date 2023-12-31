#pragma once

#include "CGrimoire/details/defines.h"
#include "CGrimoire/iterator.h"

#define CG_VECTOR_NPOS SIZE_MAX

typedef struct cg_vector_t cg_vector_t;

size_t cg_vector_sizeof(void);

cg_vector_t *cg_vector_create(size_t capacity, size_t element_size_in_bytes);
cg_vector_t *cg_vector_copy(cg_vector_t *vector, const cg_vector_t *other);
cg_vector_t *cg_vector_move(cg_vector_t *vector, cg_vector_t **other);

bool cg_vector_fill(cg_vector_t *vector, const byte_t *data, size_t amount);
bool cg_vector_assign(cg_vector_t *vector, const byte_t *data, size_t amount);

bool cg_vector_at(const cg_vector_t *vector, size_t index, byte_t *dest);
bool cg_vector_front(const cg_vector_t *vector, byte_t *dest);
bool cg_vector_back(const cg_vector_t *vector, byte_t *dest);

bool cg_vector_empty(const cg_vector_t *vector);
size_t cg_vector_size(const cg_vector_t *vector);
size_t cg_vector_capacity(const cg_vector_t *vector);
size_t cg_vector_element_size(const cg_vector_t *vector);
bool cg_vector_reserve(const cg_vector_t *vector, size_t amount);

bool cg_vector_insert(cg_vector_t *vector, size_t index, const byte_t *data);
bool cg_vector_insert_range(cg_vector_t *vector, size_t index, byte_t *data, size_t data_amount);
bool cg_vector_change(cg_vector_t *vector, size_t index, const byte_t *data);
bool cg_vector_change_range(cg_vector_t *vector, size_t index, byte_t *data, size_t data_amount);

cg_iterator_t *cg_vector_begin(cg_vector_t *vector, cg_iterator_t *iterator);
cg_iterator_t *cg_vector_end(cg_vector_t *vector, cg_iterator_t *iterator);
const cg_iterator_t *cg_vector_cbegin(cg_vector_t *vector);
const cg_iterator_t *cg_vector_cend(cg_vector_t *vector);

bool cg_vector_push_back(cg_vector_t *vector, const byte_t *data);
bool cg_vector_push_back_range(cg_vector_t *vector, const byte_t *data, size_t data_amount);
bool cg_vector_push_front(cg_vector_t *vector, const byte_t *data);
bool cg_vector_push_front_range(cg_vector_t *vector, const byte_t *data, size_t data_amount);

bool cg_vector_pop_back(cg_vector_t *vector);
bool cg_vector_pop_front(cg_vector_t *vector);
bool cg_vector_erase(cg_vector_t *vector, size_t index);
void cg_vector_clear(cg_vector_t *vector);

bool cg_vector_resize(cg_vector_t *vector, size_t amount, const byte_t *data);

void cg_vector_destroy(cg_vector_t **vector);
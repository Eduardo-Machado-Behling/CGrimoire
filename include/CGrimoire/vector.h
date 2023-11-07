#pragma once

#include "CGrimoire/details/defines.h"

#define CG_VECTOR_NPOS SIZE_MAX

typedef struct cg_vector_t cg_vector_t;

cg_vector_t *cg_vector_create();
cg_vector_t *cg_vector_copy(const cg_vector_t *other);

bool cg_vector_assign(cg_vector_t *array, byte_t *data, size_t amount);

bool cg_vector_at(const cg_vector_t *vector, size_t index, byte_t *dest);
bool cg_vector_front(const cg_vector_t *vector, byte_t *dest);
bool cg_vector_back(const cg_vector_t *vector, byte_t *dest);

bool cg_vector_empty(const cg_vector_t *vector);
size_t cg_vector_size(const cg_vector_t *vector);
size_t cg_vector_capacity(const cg_vector_t *vector);
bool cg_vector_reserve(const cg_vector_t *vector, size_t amount);

bool cg_vector_insert(const cg_vector_t *vector, size_t index, const byte_t *data);
bool cg_vector_insert_range(const cg_vector_t *vector, size_t index, byte_t *data, size_t data_amount);
bool cg_vector_erase(const cg_vector_t *vector, size_t index);
bool cg_vector_push_back(const cg_vector_t *vector, const byte_t *data);
bool cg_vector_push_back_range(const cg_vector_t *vector, const byte_t *data, size_t data_amount);
bool cg_vector_pop_back(const cg_vector_t *vector);
bool cg_vector_resize(const cg_vector_t *vector, size_t amount, const byte_t *data);
#pragma once

#include "CGrimoire/details/defines.h"

typedef struct cg_stack_t cg_stack_t;

cg_stack_t *cg_stack_create(size_t starting_size, size_t element_size);
cg_stack_t *cg_stack_copy(cg_stack_t *stack, cg_stack_t *other);
cg_stack_t *cg_stack_move(cg_stack_t *stack, cg_stack_t **other);

cg_stack_t *cg_stack_top(cg_stack_t *stack, byte_t *dest);

bool cg_stack_empty(cg_stack_t *stack);
size_t cg_stack_size(cg_stack_t *stack);

cg_stack_t *cg_stack_push(cg_stack_t *stack, const byte_t *data);
cg_stack_t *cg_stack_push_range(cg_stack_t *stack, const byte_t *data, size_t amount);
cg_stack_t *cg_stack_pop(cg_stack_t *stack);

void cg_stack_destroy(cg_stack_t *stack);

#pragma once

#include "CGrimoire/details/defines.h"

typedef struct cg_queue_t cg_queue_t;

cg_queue_t *cg_queue_create(size_t starting_size, size_t element_size);
cg_queue_t *cg_queue_copy(cg_queue_t *queue, cg_queue_t *other);
cg_queue_t *cg_queue_move(cg_queue_t *queue, cg_queue_t **other);

cg_queue_t *cg_queue_back(cg_queue_t *queue, byte_t *dest);
cg_queue_t *cg_queue_front(cg_queue_t *queue, byte_t *dest);

bool cg_queue_empty(cg_queue_t *queue);
size_t cg_queue_size(cg_queue_t *queue);

cg_queue_t *cg_queue_push(cg_queue_t *queue, const byte_t *data);
cg_queue_t *cg_queue_push_range(cg_queue_t *queue, const byte_t *data, size_t amount);
cg_queue_t *cg_queue_pop(cg_queue_t *queue);

void cg_queue_destroy(cg_queue_t *queue);

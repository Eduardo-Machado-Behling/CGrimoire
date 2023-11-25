#pragma once

#include "CGrimoire/details/defines.h"

typedef size_t (*cg_hash_func)(const void *key, size_t key_size, void *extra_args);

typedef struct cg_hashmap_t cg_hashmap_t;

cg_hashmap_t *cg_hashmap_create(cg_hash_func hash_func, size_t initial_size, size_t element_size, size_t key_size);

bool cg_hashmap_empty(cg_hashmap_t *hashmap);
size_t cg_hashmap_size(cg_hashmap_t *hashmap);

cg_hashmap_t *cg_hashmap_clear(cg_hashmap_t *hashmap);
cg_hashmap_t *cg_hashmap_set(cg_hashmap_t *hashmap, const void *key, void *extra_args, const void *data);
cg_hashmap_t *cg_hashmap_get(cg_hashmap_t *hashmap, const void *key, void *extra_args, void *dest);

bool cg_hashmap_contains(cg_hashmap_t *hashmap, const void *key, void *extra_args);

void cg_hashmap_destroy(cg_hashmap_t **hashmap);
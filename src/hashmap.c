#include "CGrimoire/hashmap.h"
#include "CGrimoire/array.h"
#include "CGrimoire/vector.h"

typedef struct cg_hashmap_t {
    cg_array_t *container;
    cg_hash_func hash_func;
    size_t element_size;
    size_t key_size;
    size_t stored;

    cg_iterator_t *it;
} cg_hashmap_t;

typedef struct cg_bucket_t {
    byte_t *data;
    void *key;
} cg_bucket_t;

cg_bucket_t *cg_bucket_create(const byte_t *data, size_t data_size, const void *key, size_t key_size);
void cg_bucket_destroy(cg_bucket_t **bucket);

cg_bucket_t *cg_bucket_create(const byte_t *data, size_t data_size, const void *key, size_t key_size) {
    cg_bucket_t *bucket;
    CG_SAFE_ALLOC(bucket, sizeof(cg_bucket_t), return NULL);

    CG_SAFE_ALLOC(bucket->data, data_size, cg_bucket_destroy(&bucket); return NULL);
    CG_SAFE_ALLOC(bucket->key, key_size, cg_bucket_destroy(&bucket); return NULL);

    memcpy(bucket->key, key, key_size);
    memcpy(bucket->data, data, data_size);

    return bucket;
}

void cg_bucket_destroy(cg_bucket_t **bucket) {
    if (!bucket)
        return;

    cg_bucket_t *b = *bucket;
    bucket = NULL;

    if (!b)
        return;

    if (b->data)
        free(b->data);
    if (b->key)
        free(b->key);

    free(b);
}

cg_hashmap_t *cg_hashmap_create(cg_hash_func hash_func, size_t bucket_amount, size_t element_size, size_t key_size) {
    cg_hashmap_t *hashmap;
    CG_SAFE_ALLOC(hashmap, sizeof(cg_hashmap_t), return NULL);

    hashmap->container = cg_array_create(bucket_amount, sizeof(cg_vector_t *));
    if (!hashmap->container) {
        cg_hashmap_destroy(&hashmap);
        return NULL;
    }

    cg_vector_t *vec = NULL;
    cg_array_fill(hashmap->container, CG_AS_MEMORY(vec));

    hashmap->hash_func = hash_func;
    if (!hashmap->hash_func) {
        cg_hashmap_destroy(&hashmap);
        return NULL;
    }
    hashmap->it = cg_iterator_create();
    if (!hashmap->it) {
        cg_hashmap_destroy(&hashmap);
        return NULL;
    }

    hashmap->element_size = element_size;
    hashmap->key_size = key_size;
    hashmap->stored = 0;

    return hashmap;
}

bool cg_hashmap_empty(cg_hashmap_t *hashmap) { return !hashmap->stored; }
size_t cg_hashmap_size(cg_hashmap_t *hashmap) { return hashmap->stored; }

cg_hashmap_t *cg_hashmap_clear(cg_hashmap_t *hashmap) {
    hashmap->stored = 0;

    for (cg_array_begin(hashmap->container, hashmap->it); cg_iterator_distance(hashmap->it, cg_array_cend(hashmap->container)) > 0;
         cg_iterator_next(hashmap->it, 1)) {

        cg_vector_t *val = CG_ITERATOR_GET_DATA(hashmap->it, cg_vector_t *);
        if (val)
            cg_vector_clear(val);
    }

    return hashmap;
}
cg_hashmap_t *cg_hashmap_set(cg_hashmap_t *hashmap, const void *key, void *extra_args, const void *data) {
    size_t i = hashmap->hash_func(key, hashmap->key_size, extra_args) % cg_array_capacity(hashmap->container);

    cg_vector_t *bucket;
    cg_array_at(hashmap->container, i, CG_AS_MEMORY(bucket));

    if (!bucket)
        bucket = cg_vector_create(5, sizeof(cg_bucket_t *));

    cg_bucket_t *b = cg_bucket_create(data, hashmap->element_size, key, hashmap->key_size);
    cg_vector_push_back(bucket, CG_AS_MEMORY(b));
    cg_array_change(hashmap->container, i, CG_AS_MEMORY(bucket));

    return hashmap;
}

cg_hashmap_t *cg_hashmap_get(cg_hashmap_t *hashmap, const void *key, void *extra_args, void *dest) {
    size_t i = hashmap->hash_func(key, hashmap->key_size, extra_args) % cg_array_capacity(hashmap->container);

    cg_vector_t *bucket;
    cg_array_at(hashmap->container, i, CG_AS_MEMORY(bucket));
    if (bucket) {
        for (cg_vector_begin(bucket, hashmap->it); cg_iterator_distance(hashmap->it, cg_vector_cend(bucket)) > 0; cg_iterator_next(hashmap->it, 1)) {
            cg_bucket_t *val = CG_ITERATOR_GET_DATA(hashmap->it, cg_bucket_t *);
            if (memcmp(val->key, key, hashmap->key_size) == 0) {
                memcpy(dest, val->data, hashmap->element_size);
                break;
            }
        }
    } else {
        dest = NULL;
    }

    return hashmap;
}

bool cg_hashmap_contains(cg_hashmap_t *hashmap, const void *key, void *extra_args) {
    size_t i = hashmap->hash_func(key, hashmap->key_size, extra_args) % cg_array_capacity(hashmap->container);

    cg_vector_t *bucket;
    cg_array_at(hashmap->container, i, CG_AS_MEMORY(bucket));
    return bucket != NULL;
}

void cg_hashmap_destroy(cg_hashmap_t **hashmap) {
    if (!hashmap)
        return;

    cg_hashmap_t *hmap = *hashmap;
    hashmap = NULL;

    if (!hmap)
        return;

    if (hmap->container) {
        cg_iterator_t *it = cg_iterator_create();
        for (cg_array_begin(hmap->container, hmap->it); cg_iterator_distance(hmap->it, cg_array_cend(hmap->container)) > 0; cg_iterator_next(hmap->it, 1)) {

            cg_vector_t *val = CG_ITERATOR_GET_DATA(hmap->it, cg_vector_t *);

            if (!val)
                continue;

            for (cg_vector_begin(val, it); cg_iterator_distance(it, cg_vector_cend(val)) > 0; cg_iterator_next(it, 1)) {
                cg_bucket_t *b = CG_ITERATOR_GET_DATA(it, cg_bucket_t *);
                if (b) {
                    cg_bucket_destroy(&b);
                }
            }
            cg_vector_destroy(&val);
        }
        cg_iterator_destroy(it);
        cg_array_destroy(&hmap->container);
    }

    if (hmap->it)
        cg_iterator_destroy(hmap->it);

    free(hmap);
}
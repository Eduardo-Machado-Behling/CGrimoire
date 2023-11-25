#include "CGrimoire/vector.h"
#include "CGrimoire/array.h"

typedef struct cg_vector_t {
    cg_array_t *array;
    size_t used;

    // for method aux propose
    byte_t *at;

    cg_iterator_t *begin;
    cg_iterator_t *end;
} cg_vector_t;

size_t cg_vector_sizeof(void) { return sizeof(cg_vector_t); }

cg_vector_t *cg_vector_create(size_t capacity, size_t element_size_in_bytes) {
    cg_vector_t *vector;
    CG_SAFE_ALLOC(vector, sizeof(cg_vector_t), return NULL);
    CG_SAFE_ALLOC(vector->at, element_size_in_bytes, free(vector); return NULL);

    vector->array = cg_array_create(capacity, element_size_in_bytes);
    if (!vector->array) {
        free(vector);
        return NULL;
    }

    vector->used = 0;
    vector->begin = NULL;
    vector->end = NULL;

    return vector;
}

cg_vector_t *cg_vector_copy(cg_vector_t *vector, const cg_vector_t *other) {
    if (!vector)
        vector = cg_vector_create(cg_array_capacity(other->array), cg_array_element_size(other->array));

    vector->array = cg_array_copy(NULL, other->array);
    vector->used = other->used;
    memcpy(vector->at, other->at, cg_array_element_size(other->array));

    return vector;
}

cg_vector_t *cg_vector_move(cg_vector_t *vector, cg_vector_t **other) {
    if (!vector)
        CG_SAFE_ALLOC(vector, sizeof(cg_vector_t), return NULL);

    vector->array = (*other)->array;
    vector->used = (*other)->used;
    vector->at = (*other)->at;
    vector->begin = (*other)->begin;
    vector->end = (*other)->end;

    (*other)->array = NULL;
    (*other)->used = 0;
    (*other)->end = NULL;
    (*other)->begin = NULL;
    (*other)->at = NULL;

    cg_vector_destroy(other);
    *other = NULL;

    return vector;
}

bool cg_vector_fill(cg_vector_t *vector, const byte_t *data, size_t amount) {
    if (!vector || !data || !amount)
        return false;

    if (amount > cg_array_capacity(vector->array)) {
        CG_SAFE_CALL(cg_array_reserve(vector->array, amount * 2), return false);
    }

    vector->used = amount;
    for (size_t i = 0; i < vector->used; i++) {
        CG_SAFE_CALL(cg_array_change(vector->array, i, data), return false);
    }

    return true;
}

bool cg_vector_assign(cg_vector_t *vector, const byte_t *data, size_t amount) {
    if (!vector || !data || !amount)
        return false;

    if (amount > cg_array_capacity(vector->array)) {
        CG_SAFE_CALL(cg_array_reserve(vector->array, amount * 2), return false);
    }

    vector->used = amount;
    for (size_t i = 0; i < vector->used; i++) {
        CG_SAFE_CALL(cg_array_change(vector->array, i, data + i * cg_array_element_size(vector->array)), return false);
    }

    return true;
}

bool cg_vector_at(const cg_vector_t *vector, size_t index, byte_t *dest) {
    if (index >= vector->used)
        return false;
    return cg_array_at(vector->array, index, dest);
}

bool cg_vector_front(const cg_vector_t *vector, byte_t *dest) {
    if (!vector || !vector->used || !vector->array)
        return false;
    return cg_array_at(vector->array, 0, dest);
}
bool cg_vector_back(const cg_vector_t *vector, byte_t *dest) {
    if (!vector || !vector->used || !vector->array)
        return false;
    return cg_array_at(vector->array, vector->used - 1, dest);
}

bool cg_vector_empty(const cg_vector_t *vector) {
    if (!vector)
        return false;

    return !vector->used;
}
size_t cg_vector_size(const cg_vector_t *vector) {
    if (!vector)
        return false;

    return vector->used;
}
size_t cg_vector_capacity(const cg_vector_t *vector) {
    if (!vector || !vector->array)
        return false;

    return cg_array_capacity(vector->array);
}

size_t cg_vector_element_size(const cg_vector_t *vector) { return cg_array_element_size(vector->array); }

bool cg_vector_reserve(const cg_vector_t *vector, size_t amount) {
    if (!vector || !vector->array)
        return false;

    return cg_array_reserve(vector->array, amount);
}

bool cg_vector_insert(cg_vector_t *vector, size_t index, const byte_t *data) {
    if (!vector || !vector->array || !(index < vector->used))
        return false;

    if (index >= vector->used)
        return cg_vector_push_back(vector, data);

    if (vector->used + 1 >= cg_array_capacity(vector->array))
        CG_SAFE_CALL(cg_vector_reserve(vector, cg_array_capacity(vector->array) * 2), return false;);

    for (size_t i = vector->used - 1; i >= index; i--) {
        CG_SAFE_CALL(cg_array_at(vector->array, i, vector->at), return false;);
        CG_SAFE_CALL(cg_array_change(vector->array, i + 1, vector->at), return false;);
    }
    ++vector->used;
    return cg_array_change(vector->array, index, data);
}
bool cg_vector_insert_range(cg_vector_t *vector, size_t index, byte_t *data, size_t data_amount) {
    if (!vector || !vector->array || !(index < vector->used))
        return false;

    if (index == vector->used)
        return cg_vector_push_back(vector, data);

    if (vector->used + data_amount >= cg_array_capacity(vector->array))
        CG_SAFE_CALL(cg_vector_reserve(vector, cg_array_capacity(vector->array) * 2), return false;);

    for (size_t i = vector->used - 1; i >= index; i--) {
        CG_SAFE_CALL(cg_array_at(vector->array, i, vector->at), return false;);
        CG_SAFE_CALL(cg_array_change(vector->array, i + data_amount, vector->at), return false;);
    }
    vector->used += data_amount;
    for (size_t i = 0; i < data_amount; i++) {
        CG_SAFE_CALL(cg_array_change(vector->array, i + index, data + i * cg_array_element_size(vector->array)), return false;);
    }

    return cg_array_change(vector->array, index, data);
}

bool cg_vector_change(cg_vector_t *vector, size_t index, const byte_t *data) {
    if (!vector || !vector->array || !(index < vector->used))
        return false;

    return cg_array_change(vector->array, index, data);
}

bool cg_vector_change_range(cg_vector_t *vector, size_t index, byte_t *data, size_t data_amount) {
    if (!vector || !data)
        return false;

    for (size_t i = 0; i < vector->used && i < data_amount; i++)
        CG_SAFE_CALL(cg_vector_change(vector, i + index, data + i * cg_array_element_size(vector->array)), return false);

    return true;
}

cg_iterator_t *cg_vector_begin(cg_vector_t *vector, cg_iterator_t *iterator) { return cg_array_begin(vector->array, iterator); }
cg_iterator_t *cg_vector_end(cg_vector_t *vector, cg_iterator_t *iterator) {
    cg_iterator_t *it = cg_array_begin(vector->array, iterator);
    cg_iterator_next(it, vector->used);
    return it;
}

const cg_iterator_t *cg_vector_cbegin(cg_vector_t *vector) { return cg_array_cbegin(vector->array); }
const cg_iterator_t *cg_vector_cend(cg_vector_t *vector) {
    if (!vector->end) {
        CG_SAFE_CALL(vector->end = cg_iterator_create(), return NULL;);
    }
    cg_array_begin(vector->array, vector->end);
    cg_iterator_next(vector->end, vector->used);
    return vector->end;
}

bool cg_vector_erase(cg_vector_t *vector, size_t index) {
    if (!vector)
        return false;

    if (index >= vector->used)
        return cg_vector_pop_back(vector);

    --vector->used;
    for (size_t i = index; i < vector->used; ++i) {

        CG_SAFE_CALL(cg_array_at(vector->array, i + 1, vector->at), return false);
        CG_SAFE_CALL(cg_array_change(vector->array, i, vector->at), return false);
    }

    return true;
}

bool cg_vector_push_back(cg_vector_t *vector, const byte_t *data) {
    if (!vector)
        return false;

    if (++vector->used >= cg_array_capacity(vector->array))
        CG_SAFE_CALL(cg_array_reserve(vector->array, cg_array_capacity(vector->array) * 2), return false);

    return cg_array_change(vector->array, vector->used - 1, data);
}

bool cg_vector_push_back_range(cg_vector_t *vector, const byte_t *data, size_t data_amount) {
    if (!vector || !data || !data_amount)
        return false;

    for (size_t i = 0; i < data_amount; i++)
        CG_SAFE_CALL(cg_vector_push_back(vector, data + i * cg_array_element_size(vector->array)), return false);

    return true;
}

bool cg_vector_push_front(cg_vector_t *vector, const byte_t *data) {
    if (!vector)
        return false;

    if (++vector->used >= cg_array_capacity(vector->array))
        CG_SAFE_CALL(cg_array_reserve(vector->array, cg_array_capacity(vector->array) * 2), return false);

    for (size_t i = vector->used - 1; i > 0; i--) {

        CG_SAFE_CALL(cg_array_at(vector->array, i - 1, vector->at), return false);
        CG_SAFE_CALL(cg_array_change(vector->array, i, vector->at), return false);
    }

    CG_SAFE_CALL(cg_array_change(vector->array, 0, data), return false);

    return true;
}
bool cg_vector_push_front_range(cg_vector_t *vector, const byte_t *data, size_t data_amount) {
    if (!vector)
        return false;

    vector->used += data_amount;
    if (vector->used >= cg_array_capacity(vector->array))
        CG_SAFE_CALL(cg_array_reserve(vector->array, cg_array_capacity(vector->array) * 2 + data_amount), return false);

    for (size_t i = vector->used - 1; i >= data_amount; --i) {

        CG_SAFE_CALL(cg_array_at(vector->array, i - data_amount, vector->at), return false);
        CG_SAFE_CALL(cg_array_change(vector->array, i, vector->at), return false);
    }

    for (size_t i = 0; i < data_amount; i++) {
        CG_SAFE_CALL(cg_array_change(vector->array, i, data + i * cg_array_element_size(vector->array)), return false);
    }

    return true;
}

bool cg_vector_pop_back(cg_vector_t *vector) {
    if (!vector || !vector->used)
        return false;

    --vector->used;
    return true;
}

bool cg_vector_pop_front(cg_vector_t *vector) {
    if (!vector || !vector->used)
        return false;

    return cg_vector_erase(vector, 0);
}

void cg_vector_clear(cg_vector_t *vector) { vector->used = 0; }

bool cg_vector_resize(cg_vector_t *vector, size_t amount, const byte_t *data) {
    if (!vector || !amount || !data)
        return false;

    if (amount > cg_array_capacity(vector->array)) {
        vector->used = amount;
        CG_SAFE_CALL(cg_array_resize(vector->array, amount, data), return false);
    }

    return true;
}

void cg_vector_destroy(cg_vector_t **vector) {
    if (!vector)
        return;

    cg_vector_t *vec = *vector;
    vector = NULL;
    if (!vec)
        return;

    cg_array_destroy(&vec->array);

    if (vec->at)
        free(vec->at);
    if (vec->begin)
        cg_iterator_destroy(vec->begin);
    if (vec->end)
        cg_iterator_destroy(vec->end);

    free(vec);
}
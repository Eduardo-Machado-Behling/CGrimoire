#include "CGrimoire/queue.h"
#include "CGrimoire/vector.h"

typedef struct cg_queue_t {
    cg_vector_t *vector;
} cg_queue_t;

cg_queue_t *cg_queue_create(size_t starting_size, size_t element_size) {
    cg_queue_t *queue;
    CG_SAFE_ALLOC(queue, sizeof(cg_queue_t), return NULL);

    CG_SAFE_CALL(queue->vector = cg_vector_create(starting_size, element_size), cg_queue_destroy(queue); return NULL;)

    return queue;
}
cg_queue_t *cg_queue_copy(cg_queue_t *queue, cg_queue_t *other) {
    if (!queue)
        queue = cg_queue_create(cg_vector_capacity(other->vector), cg_vector_element_size(other->vector));
    CG_SAFE_CALL(queue->vector = cg_vector_copy(NULL, other->vector), return NULL;)

    return queue;
}
cg_queue_t *cg_queue_move(cg_queue_t *queue, cg_queue_t **other) {
    if (!queue)
        CG_SAFE_ALLOC(queue, sizeof(cg_queue_t), return NULL);
    queue->vector = (*other)->vector;
    (*other)->vector = NULL;

    cg_queue_destroy(*other);
    *other = NULL;

    return queue;
}

cg_queue_t *cg_queue_back(cg_queue_t *queue, byte_t *dest) {
    if (!cg_vector_back(queue->vector, dest))
        return NULL;
    return queue;
}
cg_queue_t *cg_queue_front(cg_queue_t *queue, byte_t *dest) {
    if (!cg_vector_front(queue->vector, dest))
        return NULL;
    return queue;
}

bool cg_queue_empty(cg_queue_t *queue) { return cg_vector_empty(queue->vector); }
size_t cg_queue_size(cg_queue_t *queue) { return cg_vector_size(queue->vector); }

cg_queue_t *cg_queue_push(cg_queue_t *queue, const byte_t *data) {
    if (!cg_vector_push_front(queue->vector, data))
        return NULL;
    return queue;
}
cg_queue_t *cg_queue_push_range(cg_queue_t *queue, const byte_t *data, size_t amount) {
    if (!cg_vector_push_front_range(queue->vector, data, amount))
        return NULL;
    return queue;
}
cg_queue_t *cg_queue_pop(cg_queue_t *queue) {
    if (!cg_vector_pop_front(queue->vector))
        return NULL;
    return queue;
}

void cg_queue_destroy(cg_queue_t *queue) {
    if (!queue)
        return;

    if (queue->vector)
        cg_vector_destroy(&queue->vector);
    free(queue);
}
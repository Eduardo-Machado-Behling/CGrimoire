#include "CGrimoire/stack.h"
#include "CGrimoire/vector.h"

typedef struct cg_stack_t {
    cg_vector_t *vector;
} cg_stack_t;

cg_stack_t *cg_stack_create(size_t starting_size, size_t element_size) {
    cg_stack_t *stack;
    CG_SAFE_ALLOC(stack, sizeof(cg_stack_t), return NULL);

    CG_SAFE_CALL(stack->vector = cg_vector_create(starting_size, element_size), free(stack); return NULL;);

    return stack;
}
cg_stack_t *cg_stack_copy(cg_stack_t *stack, cg_stack_t *other) {
    if (!stack)
        stack = cg_stack_create(cg_vector_capacity(other->vector), cg_vector_element_size(other->vector));
    CG_SAFE_CALL(stack->vector = cg_vector_copy(NULL, other->vector), return NULL;)

    return stack;
}

cg_stack_t *cg_stack_move(cg_stack_t *stack, cg_stack_t **other) {
    if (!stack)
        CG_SAFE_ALLOC(stack, sizeof(cg_stack_t), return NULL);
    stack->vector = (*other)->vector;
    (*other)->vector = NULL;

    cg_stack_destroy(*other);
    *other = NULL;

    return stack;
}

cg_stack_t *cg_stack_top(cg_stack_t *stack, byte_t *dest) {
    if (!stack || !dest)
        return NULL;

    if (!cg_vector_back(stack->vector, dest))
        return NULL;

    return stack;
}

bool cg_stack_empty(cg_stack_t *stack) { return cg_vector_empty(stack->vector); }
size_t cg_stack_size(cg_stack_t *stack) { return cg_vector_size(stack->vector); }

cg_stack_t *cg_stack_push(cg_stack_t *stack, const byte_t *data) {
    if (!cg_vector_push_back(stack->vector, data))
        return NULL;
    return stack;
}
cg_stack_t *cg_stack_push_range(cg_stack_t *stack, const byte_t *data, size_t amount) {
    if (!cg_vector_push_back_range(stack->vector, data, amount))
        return NULL;
    return stack;
}
cg_stack_t *cg_stack_pop(cg_stack_t *stack) {
    if (!cg_vector_pop_back(stack->vector))
        return NULL;
    return stack;
}

void cg_stack_destroy(cg_stack_t *stack) {
    if (!stack)
        return;

    if (stack->vector)
        cg_vector_destroy(&stack->vector);
    free(stack);
}

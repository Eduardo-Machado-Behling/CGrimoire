#include <CGrimoire/stack.h>
#include <unity.h>

cg_stack_t *stack;

void setUp(void) { stack = cg_stack_create(10, sizeof(int32_t)); }

void test_CGStack_usage(void) {
    int a = 50;
    int vs[] = {1, 2, 3, 4, 5};
    cg_stack_push(stack, CG_AS_MEMORY(a));
    a *= 5;
    cg_stack_push(stack, CG_AS_MEMORY(a));
    cg_stack_push_range(stack, CG_AS_MEMORY(vs), sizeof(vs) / sizeof(int));

    size_t i = 0;

    int expected[] = {5, 4, 3, 2, 1, 250, 50};
    while (!cg_stack_empty(stack)) {
        int v;
        TEST_ASSERT_NOT_NULL(cg_stack_top(stack, CG_AS_MEMORY(v)));
        TEST_ASSERT_EQUAL_INT(expected[i++], v);
        TEST_ASSERT_NOT_NULL(cg_stack_pop(stack));
    }
}

void test_CGStack_copy(void) {
    int a = 50;
    int vs[] = {1, 2, 3, 4, 5};
    cg_stack_push(stack, CG_AS_MEMORY(a));
    a *= 5;
    cg_stack_push(stack, CG_AS_MEMORY(a));
    cg_stack_push_range(stack, CG_AS_MEMORY(vs), sizeof(vs) / sizeof(int));

    cg_stack_t *copied = cg_stack_copy(NULL, stack);

    size_t i = 0;

    int expected[] = {5, 4, 3, 2, 1, 250, 50};
    while (!cg_stack_empty(copied)) {
        int v;
        TEST_ASSERT_NOT_NULL(cg_stack_top(copied, CG_AS_MEMORY(v)));
        TEST_ASSERT_EQUAL_INT(expected[i++], v);
        TEST_ASSERT_NOT_NULL(cg_stack_pop(copied));
    }
}
void test_CGStack_move(void) {
    int a = 50;
    int vs[] = {1, 2, 3, 4, 5};
    cg_stack_push(stack, CG_AS_MEMORY(a));
    a *= 5;
    cg_stack_push(stack, CG_AS_MEMORY(a));
    cg_stack_push_range(stack, CG_AS_MEMORY(vs), sizeof(vs) / sizeof(int));

    cg_stack_t *moved = cg_stack_move(NULL, &stack);

    size_t i = 0;

    int expected[] = {5, 4, 3, 2, 1, 250, 50};
    while (!cg_stack_empty(moved)) {
        int v;
        TEST_ASSERT_NOT_NULL(cg_stack_top(moved, CG_AS_MEMORY(v)));
        TEST_ASSERT_EQUAL_INT(expected[i++], v);
        TEST_ASSERT_NOT_NULL(cg_stack_pop(moved));
    }
}

void tearDown(void) { cg_stack_destroy(stack); }

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CGStack_usage);
    RUN_TEST(test_CGStack_copy);
    RUN_TEST(test_CGStack_move);

    return UNITY_END();
}
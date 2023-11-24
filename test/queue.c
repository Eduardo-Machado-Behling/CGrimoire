#include <CGrimoire/queue.h>
#include <unity.h>

cg_queue_t *queue;

void setUp(void) { queue = cg_queue_create(10, sizeof(int32_t)); }

void test_CGQueue_usage(void) {
    int a = 50;
    int vs[] = {1, 2, 3, 4, 5};
    cg_queue_push(queue, CG_AS_MEMORY(a));
    a *= 5;
    cg_queue_push(queue, CG_AS_MEMORY(a));
    cg_queue_push_range(queue, CG_AS_MEMORY(vs), sizeof(vs) / sizeof(int));

    size_t i = 0;

    int expected[] = {1, 2, 3, 4, 5, 250, 50};
    while (!cg_queue_empty(queue)) {
        int v;
        TEST_ASSERT_NOT_NULL(cg_queue_front(queue, CG_AS_MEMORY(v)));
        TEST_ASSERT_EQUAL_INT(expected[i++], v);
        TEST_ASSERT_NOT_NULL(cg_queue_pop(queue));
    }
}

void test_CGQueue_copy(void) {
    int a = 50;
    int vs[] = {1, 2, 3, 4, 5};
    cg_queue_push(queue, CG_AS_MEMORY(a));
    a *= 5;
    cg_queue_push(queue, CG_AS_MEMORY(a));
    cg_queue_push_range(queue, CG_AS_MEMORY(vs), sizeof(vs) / sizeof(int));

    cg_queue_t *copied = cg_queue_copy(NULL, queue);

    size_t i = 0;

    int expected[] = {1, 2, 3, 4, 5, 250, 50};
    while (!cg_queue_empty(copied)) {
        int v;
        TEST_ASSERT_NOT_NULL(cg_queue_front(copied, CG_AS_MEMORY(v)));
        TEST_ASSERT_EQUAL_INT(expected[i++], v);
        TEST_ASSERT_NOT_NULL(cg_queue_pop(copied));
    }
}
void test_CGQueue_move(void) {
    int a = 50;
    int vs[] = {1, 2, 3, 4, 5};
    cg_queue_push(queue, CG_AS_MEMORY(a));
    a *= 5;
    cg_queue_push(queue, CG_AS_MEMORY(a));
    cg_queue_push_range(queue, CG_AS_MEMORY(vs), sizeof(vs) / sizeof(int));

    cg_queue_t *moved = cg_queue_move(NULL, &queue);

    size_t i = 0;

    int expected[] = {1, 2, 3, 4, 5, 250, 50};
    while (!cg_queue_empty(moved)) {
        int v;
        TEST_ASSERT_NOT_NULL(cg_queue_front(moved, CG_AS_MEMORY(v)));
        TEST_ASSERT_EQUAL_INT(expected[i++], v);
        TEST_ASSERT_NOT_NULL(cg_queue_pop(moved));
    }
}

void tearDown(void) { cg_queue_destroy(queue); }

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CGQueue_usage);
    RUN_TEST(test_CGQueue_copy);
    RUN_TEST(test_CGQueue_move);

    return UNITY_END();
}
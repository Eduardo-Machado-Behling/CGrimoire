#include <CGrimoire/vector.h>
#include <unity.h>

void setUp(void) {}

void test_CGVector_general_use(void) {
    cg_vector_t *vector = cg_vector_create(10, sizeof(int));
    TEST_ASSERT_NOT_NULL(vector);

    size_t vector_capacity = cg_vector_capacity(vector);
    TEST_ASSERT_EQUAL_size_t(10, vector_capacity);

    for (size_t i = 0; i < vector_capacity; i++) {
        size_t val = i * i;
        TEST_ASSERT_TRUE(cg_vector_push_back(vector, CG_AS_MEMORY(val)));
    }

    size_t vector_size = cg_vector_size(vector);
    TEST_ASSERT_EQUAL_size_t(10, vector_size);

    for (size_t i = 0; i < vector_size; i++) {
        size_t val;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(val)));
        TEST_ASSERT_EQUAL_INT(i * i, val);
    }

    cg_vector_destroy(vector);
}

void test_CGVector_assign(void) {
    cg_vector_t *vector = cg_vector_create(5, sizeof(int));
    TEST_ASSERT_NOT_NULL(vector);

    size_t vector_capacity = cg_vector_capacity(vector);
    TEST_ASSERT_EQUAL_size_t(5, vector_capacity);

    int data[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    cg_vector_assign(vector, CG_AS_MEMORY(data), 10);

    size_t vector_size = cg_vector_size(vector);
    TEST_ASSERT_EQUAL_size_t(10, vector_size);

    for (size_t i = 0; i < vector_size; i++) {
        int val;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(val)));
        TEST_ASSERT_EQUAL_INT(data[i], val);
    }

    cg_vector_destroy(vector);
}

void test_CGVector_fill(void) {
    cg_vector_t *vector = cg_vector_create(5, sizeof(int));
    TEST_ASSERT_NOT_NULL(vector);

    size_t vector_capacity = cg_vector_capacity(vector);
    TEST_ASSERT_EQUAL_size_t(5, vector_capacity);

    int data = 654;
    cg_vector_fill(vector, CG_AS_MEMORY(data), 10);

    size_t vector_size = cg_vector_size(vector);
    TEST_ASSERT_EQUAL_size_t(10, vector_size);

    for (size_t i = 0; i < vector_size; i++) {
        int val;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(val)));
        TEST_ASSERT_EQUAL_INT(data, val);
    }

    cg_vector_destroy(vector);
}

void test_CGVector_clear(void) {
    cg_vector_t *vector = cg_vector_create(5, sizeof(int));
    int a = 50;
    cg_vector_fill(vector, CG_AS_MEMORY(a), 5);

    cg_vector_clear(vector);

    TEST_ASSERT_EQUAL_size_t(0, cg_vector_size(vector));
    int b;
    TEST_ASSERT_FALSE(cg_vector_at(vector, 0, CG_AS_MEMORY(b)));
    TEST_ASSERT_FALSE(cg_vector_front(vector, CG_AS_MEMORY(b)));
    TEST_ASSERT_FALSE(cg_vector_back(vector, CG_AS_MEMORY(b)));
    TEST_ASSERT_TRUE(cg_vector_empty(vector));
    TEST_ASSERT_FALSE(cg_vector_pop_back(vector));
}

void test_CGVector_push_front(void) {
    cg_vector_t *vector = cg_vector_create(5, sizeof(int));

    size_t size = cg_vector_capacity(vector);
    for (size_t i = 0; i < size; i++) {
        int val = 64 + i;
        TEST_ASSERT_TRUE(cg_vector_push_front(vector, CG_AS_MEMORY(val)));
        int at;
        cg_vector_at(vector, 0, CG_AS_MEMORY(at));
        TEST_ASSERT_EQUAL(val, at);
    }

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        cg_vector_at(vector, cg_vector_size(vector) - 1 - i, CG_AS_MEMORY(at));
        TEST_ASSERT_EQUAL(64 + i, at);
    }

    cg_vector_clear(vector);

    int data[] = {5, 7, 9};

    int a = 62;
    TEST_ASSERT_TRUE(cg_vector_push_back(vector, CG_AS_MEMORY(a)));
    TEST_ASSERT_TRUE(cg_vector_push_back(vector, CG_AS_MEMORY(a)));
    TEST_ASSERT_TRUE(cg_vector_push_front_range(vector, CG_AS_MEMORY(data), 3));
    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int v;
        cg_vector_at(vector, i, CG_AS_MEMORY(v));
        if (i < 3)
            TEST_ASSERT_EQUAL_INT(data[i], v);
        else
            TEST_ASSERT_EQUAL_INT(a, v);
    }

    cg_vector_destroy(vector);
}

void test_CGVector_front(void) {
    cg_vector_t *vector = cg_vector_create(5, sizeof(int));

    int data[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    cg_vector_assign(vector, CG_AS_MEMORY(data), 10);

    int val;
    TEST_ASSERT_TRUE(cg_vector_front(vector, CG_AS_MEMORY(val)));
    TEST_ASSERT_EQUAL(data[0], val);

    cg_vector_destroy(vector);
}

void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CGVector_general_use);
    RUN_TEST(test_CGVector_assign);
    RUN_TEST(test_CGVector_fill);
    RUN_TEST(test_CGVector_clear);
    RUN_TEST(test_CGVector_push_front);
    RUN_TEST(test_CGVector_front);

    return UNITY_END();
}
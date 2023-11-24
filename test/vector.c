#include <CGrimoire/vector.h>
#include <unity.h>

cg_vector_t *vector;

void setUp(void) { vector = cg_vector_create(10, sizeof(int32_t)); }

void test_CGArray_copy(void) {}

void test_CGVector_push_back(void) {
    cg_vector_clear(vector);

    size_t cap = cg_vector_capacity(vector);
    for (size_t i = 0; i < cap; i++) {
        int v = i * i;
        TEST_ASSERT_TRUE(cg_vector_push_back(vector, CG_AS_MEMORY(v)));
    }

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int v;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(v)));
        TEST_ASSERT_EQUAL_INT(i * i, v);
    }
}

void test_CGVector_push_back_range(void) {
    cg_vector_clear(vector);

    int vs[5] = {2, 5, 6, 7, 8};
    TEST_ASSERT_TRUE(cg_vector_push_back_range(vector, CG_AS_MEMORY(vs), 5));
    TEST_ASSERT_EQUAL_size_t(5, cg_vector_size(vector));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int v;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(v)));
        TEST_ASSERT_EQUAL_INT(vs[i], v);
    }
}

void test_CGVector_push_front(void) {
    cg_vector_clear(vector);

    size_t cap = cg_vector_capacity(vector);
    for (size_t i = 0; i < cap; i++) {
        int v = i;
        TEST_ASSERT_TRUE(cg_vector_push_front(vector, CG_AS_MEMORY(v)));
    }

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int v;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(v)));
        TEST_ASSERT_EQUAL_INT(cg_vector_size(vector) - i - 1, v);
    }
}

void test_CGVector_push_front_range(void) {
    cg_vector_clear(vector);

    int vs[5] = {2, 5, 6, 7, 8};
    TEST_ASSERT_TRUE(cg_vector_push_front_range(vector, CG_AS_MEMORY(vs), 2));
    TEST_ASSERT_TRUE(cg_vector_push_front_range(vector, CG_AS_MEMORY(vs), 5));
    TEST_ASSERT_EQUAL_size_t(7, cg_vector_size(vector));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int v;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(v)));
        if (i < 5)
            TEST_ASSERT_EQUAL_INT(vs[i], v);
        else
            TEST_ASSERT_EQUAL_INT(vs[i - 5], v);
    }
}

void test_CGVector_change(void) {
    cg_vector_clear(vector);

    int vs[5] = {2, 3, 6, 4, 5};
    TEST_ASSERT_TRUE(cg_vector_push_back_range(vector, CG_AS_MEMORY(vs), 5));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));
        at *= 2;
        TEST_ASSERT_TRUE(cg_vector_change(vector, i, CG_AS_MEMORY(at)));
    }

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));
        TEST_ASSERT_EQUAL_INT(vs[i] * 2, at);
    }
}

void test_CGVector_change_range(void) {
    cg_vector_clear(vector);

    int vs[8] = {2, 3, 6, 4, 5, 6, 7, 8};
    TEST_ASSERT_TRUE(cg_vector_push_back_range(vector, CG_AS_MEMORY(vs), 5));
    TEST_ASSERT_TRUE(cg_vector_change_range(vector, 0, CG_AS_MEMORY(vs[5]), 3));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));
        if (i < 3)
            TEST_ASSERT_EQUAL_INT(vs[i + 5], at);
        else
            TEST_ASSERT_EQUAL_INT(vs[i], at);
    }
}

void test_CGVector_fill(void) {
    cg_vector_clear(vector);

    int v = 64;
    TEST_ASSERT_TRUE(cg_vector_fill(vector, CG_AS_MEMORY(v), 5));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));
        TEST_ASSERT_EQUAL_INT(v, at);
    }
}

void test_CGVector_assign(void) {
    cg_vector_clear(vector);

    int v[10] = {6, 52, 4, 1, 5, 351, 2, 5, 9, -1};
    TEST_ASSERT_TRUE(cg_vector_assign(vector, CG_AS_MEMORY(v), 10));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));
        TEST_ASSERT_EQUAL_INT(v[i], at);
    }
}

void test_CGVector_pop_front(void) {
    cg_vector_clear(vector);

    int v[10] = {6, 52, 4, 1, 5, 351, 2, 5, 9, -1};
    TEST_ASSERT_TRUE(cg_vector_assign(vector, CG_AS_MEMORY(v), 10));

    TEST_ASSERT_TRUE(cg_vector_pop_front(vector));

    TEST_ASSERT_TRUE(cg_vector_push_front(vector, CG_AS_MEMORY(v[1])));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));
        if (i > 0)
            TEST_ASSERT_EQUAL_INT(v[i], at);
        else
            TEST_ASSERT_EQUAL_INT(v[1], at);
    }
}
void test_CGVector_pop_back(void) {
    cg_vector_clear(vector);

    int v[10] = {6, 52, 4, 1, 5, 351, 2, 5, 9, -1};
    TEST_ASSERT_TRUE(cg_vector_assign(vector, CG_AS_MEMORY(v), 10));

    for (size_t i = 0; i < 5; i++)
        TEST_ASSERT_TRUE(cg_vector_pop_back(vector));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));
        TEST_ASSERT_EQUAL_INT(v[i], at);
    }
}
void test_CGVector_erase(void) {
    cg_vector_clear(vector);

    int v[10] = {6, 52, 4, 1, 5, 351, 2, 5, 9, -1};
    int va[8] = {6, 52, 4, 5, 351, 5, 9, -1};
    TEST_ASSERT_TRUE(cg_vector_assign(vector, CG_AS_MEMORY(v), 10));
    TEST_ASSERT_TRUE(cg_vector_erase(vector, 3));
    TEST_ASSERT_TRUE(cg_vector_erase(vector, 5));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));
        TEST_ASSERT_EQUAL_INT(va[i], at);
    }
}

void test_CGVector_insert(void) {
    cg_vector_clear(vector);

    int v[10] = {6, 52, 4, 1, 5, 351, 2, 5, 9, -1};
    TEST_ASSERT_TRUE(cg_vector_assign(vector, CG_AS_MEMORY(v), 10));

    int val = 999;
    TEST_ASSERT_TRUE(cg_vector_insert(vector, 4, CG_AS_MEMORY(val)));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));

        int offset = i > 4 ? 1 : 0;
        if (i == 4)
            TEST_ASSERT_EQUAL_INT(val, at);
        else
            TEST_ASSERT_EQUAL_INT(v[i - offset], at);
    }
}
void test_CGVector_insert_range(void) {
    cg_vector_clear(vector);

    int v[10] = {6, 52, 4, 1, 5, 351, 2, 5, 9, -1};
    TEST_ASSERT_TRUE(cg_vector_assign(vector, CG_AS_MEMORY(v), 10));

    int va[10] = {20, 66, 18, 15, 19, 365, 16, 19, 23, 10};
    TEST_ASSERT_TRUE(cg_vector_insert_range(vector, 4, CG_AS_MEMORY(va), 10));

    for (size_t i = 0; i < cg_vector_size(vector); i++) {
        int at;
        TEST_ASSERT_TRUE(cg_vector_at(vector, i, CG_AS_MEMORY(at)));

        int offset = i > 13 ? 10 : 0;
        if (i >= 4 && i < 14)
            TEST_ASSERT_EQUAL_INT(va[i - 4], at);
        else
            TEST_ASSERT_EQUAL_INT(v[i - offset], at);
    }
}

void test_CGVector_iterator(void) {
    cg_vector_clear(vector);

    int v[10] = {6, 52, 4, 1, 5, 351, 2, 5, 9, -1};
    TEST_ASSERT_TRUE(cg_vector_assign(vector, CG_AS_MEMORY(v), 10));

    iterator_t *it = cg_vector_begin(vector, NULL);
    size_t i = 0;

    for (; cg_iterator_distance(it, cg_vector_cend(vector)) > 0; cg_iterator_next(it, 1), i++) {
        int at = CG_ITERATOR_GET_DATA(it, int);
        TEST_ASSERT_EQUAL_INT(v[i], at);
        v[i] *= 5;
        cg_iterator_set_data(it, CG_AS_MEMORY(v[i]));
    }

    for (i = 0, cg_vector_begin(vector, it); cg_iterator_distance(it, cg_vector_cend(vector)) > 0; cg_iterator_next(it, 1), i++) {
        int at = CG_ITERATOR_GET_DATA(it, int);
        TEST_ASSERT_EQUAL_INT(v[i], at);
    }

    cg_iterator_destroy(it);
}

void test_CGArray_swap(void) {}

void tearDown(void) { cg_vector_destroy(vector); }

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CGVector_push_back);
    RUN_TEST(test_CGVector_push_back_range);
    RUN_TEST(test_CGVector_push_front);
    RUN_TEST(test_CGVector_push_front_range);
    RUN_TEST(test_CGVector_change);
    RUN_TEST(test_CGVector_change_range);
    RUN_TEST(test_CGVector_fill);
    RUN_TEST(test_CGVector_assign);
    RUN_TEST(test_CGVector_pop_front);
    RUN_TEST(test_CGVector_pop_back);
    RUN_TEST(test_CGVector_erase);
    RUN_TEST(test_CGVector_insert);
    RUN_TEST(test_CGVector_insert_range);
    // RUN_TEST(test_CGVector_iterator);

    return UNITY_END();
}
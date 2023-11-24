#include <CGrimoire/array.h>
#include <unity.h>

cg_array_t *array;

void setUp(void) { array = cg_array_create(10, sizeof(int32_t)); }

void test_CGArray_copy(void) {
    for (size_t i = 0; i < cg_array_capacity(array); i++) {
        int32_t val = i * 5;
        TEST_ASSERT_TRUE_MESSAGE(cg_array_change(array, i, CG_AS_MEMORY(val)), "FAILED INSERT ON LOOP");
    }

    for (size_t i = 0; i < cg_array_capacity(array); i++) {
        int val;
        TEST_ASSERT_TRUE_MESSAGE(cg_array_at(array, i, CG_AS_MEMORY(val)), "FAILED AT ON LOOP");
        TEST_ASSERT_EQUAL_INT32_MESSAGE(i * 5, val, "AT IN LOOP RETURNED WRONG NUMBER");
    }

    cg_array_t *copied = cg_array_copy(array);
    for (size_t i = 0; i < cg_array_capacity(array); i++) {
        int val_copied, val_array;
        TEST_ASSERT_TRUE_MESSAGE(cg_array_at(array, i, CG_AS_MEMORY(val_array)), "FAILED ARRAY.AT ON COMPARE LOOP");
        TEST_ASSERT_TRUE_MESSAGE(cg_array_at(copied, i, CG_AS_MEMORY(val_copied)), "FAILED COPIED.AT ON COMPARE LOOP");
        TEST_ASSERT_EQUAL_INT32_MESSAGE(val_array, val_copied, "VALUES ARE DIFFERENT ON COPY");
    }

    cg_array_destroy(copied);
}

void test_CGArray_insert(void) {
    int a = 5;
    TEST_ASSERT_TRUE(cg_array_change(array, 0, CG_AS_MEMORY(a)));
    int b = -1;
    cg_array_at(array, 0, CG_AS_MEMORY(b));
    TEST_ASSERT_EQUAL_INT32(a, b);
}

void test_CGArray_fill(void) {
    int a = 363;
    TEST_ASSERT_TRUE(cg_array_fill(array, CG_AS_MEMORY(a)));

    for (size_t i = 0; i < cg_array_capacity(array); i++) {
        int b = -1;
        cg_array_at(array, 0, CG_AS_MEMORY(b));
        TEST_ASSERT_EQUAL_INT32(a, b);
    }
}

void test_CGArray_assign(void) {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    TEST_ASSERT_TRUE_MESSAGE(cg_array_assign(array, CG_AS_MEMORY(a)), "FAILED ASSIGN");

    for (int i = 0; i < 10; i++) {
        int v;
        cg_array_at(array, i, CG_AS_MEMORY(v));
        TEST_ASSERT_EQUAL_INT32_MESSAGE(v, i + 1, "VALUES ARE DIFFERENT AFTER ASSIGN");
    }
}

void test_CGArray_assign_range(void) {
    cg_array_t *a = cg_array_create(5, sizeof(int));
    int b = 0;
    cg_array_fill(a, CG_AS_MEMORY(b));
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    TEST_ASSERT_TRUE_MESSAGE(cg_array_assign_range(a, 5, CG_AS_MEMORY(data), 10), "FAILED ASSIGN_RANGE");

    for (int i = 0; i < cg_array_capacity(a); i++) {
        int v;
        cg_array_at(a, i, CG_AS_MEMORY(v));
        if (i < 5)
            TEST_ASSERT_EQUAL_INT32_MESSAGE(v, 0, "VALUES ARE DIFFERENT BEFORE ASSIGN_RANGE");
        else
            TEST_ASSERT_EQUAL_INT32_MESSAGE(v, i - 4, "VALUES ARE DIFFERENT AFTER ASSIGN_RANGE");
    }

    cg_array_destroy(a);
}

void test_CGArray_reserve(void) {
    cg_array_t *src = cg_array_create(10, sizeof(int32_t));

    TEST_ASSERT_TRUE_MESSAGE(cg_array_reserve(src, 15), "FAILED ASSIGN");

    TEST_ASSERT_EQUAL_size_t_MESSAGE(15, cg_array_capacity(src), "cg_array_capacity returned wrong");
    int32_t v = 24;
    TEST_ASSERT_TRUE_MESSAGE(cg_array_fill(src, CG_AS_MEMORY(v)), "cg_array_fill failed after cg_array_reserve");

    for (size_t i = 0; i < cg_array_capacity(src); i++) {
        int r;
        TEST_ASSERT_TRUE_MESSAGE(cg_array_at(src, i, CG_AS_MEMORY(r)), "cg_array_at failed after cg_array_reserve");
        TEST_ASSERT_EQUAL_INT_MESSAGE(v, r, "cg_array_at returned wrong val after cg_array_reserve");
    }

    cg_array_destroy(src);
}

void test_CGArray_resize(void) {
    cg_array_t *src = cg_array_create(10, sizeof(int32_t));

    int32_t v = 314;
    TEST_ASSERT_TRUE_MESSAGE(cg_array_fill(src, CG_AS_MEMORY(v)), "FAILED ASSIGN");
    v = 2004;
    TEST_ASSERT_TRUE_MESSAGE(cg_array_resize(src, 15, CG_AS_MEMORY(v)), "FAILED ASSIGN");

    for (size_t i = 0; i < cg_array_capacity(src); i++) {
        int r;
        TEST_ASSERT_TRUE_MESSAGE(cg_array_at(src, i, CG_AS_MEMORY(r)), "cg_array_at failed after cg_array_resize");
        if (i < 10)
            TEST_ASSERT_EQUAL_INT_MESSAGE(314, r, "cg_array_at returned wrong val after cg_array_resize");
        else
            TEST_ASSERT_EQUAL_INT_MESSAGE(2004, r, "cg_array_at returned wrong val after cg_array_resize");
    }

    cg_array_destroy(src);
}

void test_CGArray_swap(void) {
    cg_array_t *src = cg_array_create(10, sizeof(int32_t));
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    TEST_ASSERT_TRUE_MESSAGE(cg_array_assign(src, CG_AS_MEMORY(a)), "FAILED ASSIGN");

    cg_array_t *dest = cg_array_create(5, sizeof(int));

    TEST_ASSERT_TRUE_MESSAGE(cg_array_swap(dest, src), "FAILED SWAP");

    TEST_ASSERT_EQUAL_size_t_MESSAGE(cg_array_capacity(dest), 10, "WRONG SIZE ON SWAP");
    for (int i = 0; i < cg_array_capacity(dest); i++) {
        int v;
        cg_array_at(array, i, CG_AS_MEMORY(v));
        TEST_ASSERT_EQUAL_INT32_MESSAGE(v, i + 1, "VALUES ARE DIFFERENT AFTER SWAP");
    }
    cg_array_destroy(src);
}

void test_CGArray_iterator(void) {
    cg_array_t *src = cg_array_create(10, sizeof(int32_t));
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    TEST_ASSERT_TRUE_MESSAGE(cg_array_assign(src, CG_AS_MEMORY(a)), "FAILED ASSIGN");

    size_t i = 0;
    iterator_t *it = cg_array_begin(src, NULL);
    for (; cg_iterator_distance(it, cg_array_cend(src)) > 0; i++, cg_iterator_next(it, 1)) {
        int v = CG_ITERATOR_GET_DATA(it, int);
        TEST_ASSERT_EQUAL_INT(v, a[i]);
        a[i] *= 2;
        cg_iterator_set_data(it, CG_AS_MEMORY(a[i]));
    }

    i = 0;
    it = cg_array_begin(src, it);
    for (; cg_iterator_distance(it, cg_array_cend(src)) > 0; i++, cg_iterator_next(it, 1)) {
        int v = CG_ITERATOR_GET_DATA(it, int);
        TEST_ASSERT_EQUAL_INT(v, a[i]);
    }
    cg_iterator_destroy(it);
    cg_array_destroy(src);
}

void tearDown(void) { cg_array_destroy(array); }

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CGArray_insert);
    RUN_TEST(test_CGArray_copy);
    RUN_TEST(test_CGArray_fill);
    RUN_TEST(test_CGArray_reserve);
    RUN_TEST(test_CGArray_resize);
    RUN_TEST(test_CGArray_assign);
    RUN_TEST(test_CGArray_assign_range);
    RUN_TEST(test_CGArray_iterator);

    return UNITY_END();
}
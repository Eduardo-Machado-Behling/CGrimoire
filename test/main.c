#include <CGrimoire/array.h>
#include <unity.h>

cg_array_t *array;

void setUp(void) { array = cg_array_create(10, sizeof(int32_t)); }

void test_CGArray_copy(void) {
    for (size_t i = 0; i < cg_array_size(array); i++) {
        int32_t val = i * 5;
        TEST_ASSERT_TRUE_MESSAGE(cg_array_insert(array, i, AS_MEMORY(val)), "FAILED INSERT ON LOOP");
    }

    for (size_t i = 0; i < cg_array_size(array); i++) {
        int val;
        TEST_ASSERT_TRUE_MESSAGE(cg_array_at(array, i, AS_MEMORY(val)), "FAILED AT ON LOOP");
        TEST_ASSERT_EQUAL_INT32_MESSAGE(i * 5, val, "AT IN LOOP RETURNED WRONG NUMBER");
    }

    cg_array_t *copied = cg_array_copy(array);
    for (size_t i = 0; i < cg_array_size(array); i++) {
        int val_copied, val_array;
        TEST_ASSERT_TRUE_MESSAGE(cg_array_at(array, i, AS_MEMORY(val_array)), "FAILED ARRAY.AT ON COMPARE LOOP");
        TEST_ASSERT_TRUE_MESSAGE(cg_array_at(copied, i, AS_MEMORY(val_copied)), "FAILED COPIED.AT ON COMPARE LOOP");
        TEST_ASSERT_EQUAL_INT32_MESSAGE(val_array, val_copied, "VALUES ARE DIFFERENT ON COPY");
    }

    cg_array_destroy(copied);
}

void test_CGArray_insert(void) {
    int a = 5;
    TEST_ASSERT_TRUE(cg_array_insert(array, 0, AS_MEMORY(a)));
    int b = -1;
    cg_array_at(array, 0, AS_MEMORY(b));
    TEST_ASSERT_EQUAL_INT32(a, b);
}

void test_CGArray_fill(void) {
    int a = 363;
    TEST_ASSERT_TRUE(cg_array_fill(array, AS_MEMORY(a)));

    for (size_t i = 0; i < cg_array_size(array); i++) {
        int b = -1;
        cg_array_at(array, 0, AS_MEMORY(b));
        TEST_ASSERT_EQUAL_INT32(a, b);
    }
}

void test_CGArray_assign(void) {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    TEST_ASSERT_TRUE_MESSAGE(cg_array_assign(array, AS_MEMORY(a)), "FAILED ASSIGN");

    for (int i = 0; i < 10; i++) {
        int v;
        cg_array_at(array, i, AS_MEMORY(v));
        TEST_ASSERT_EQUAL_INT32_MESSAGE(v, i + 1, "VALUES ARE DIFFERENT AFTER ASSIGN");
    }
}

void test_CGArray_swap(void) {
    cg_array_t *src = cg_array_create(10, sizeof(int32_t));
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    TEST_ASSERT_TRUE_MESSAGE(cg_array_assign(src, AS_MEMORY(a)), "FAILED ASSIGN");

    cg_array_t *dest = cg_array_create(5, sizeof(int));

    TEST_ASSERT_TRUE_MESSAGE(cg_array_swap(dest, src), "FAILED SWAP");

    TEST_ASSERT_EQUAL_size_t_MESSAGE(cg_array_size(dest), 10, "WRONG SIZE ON SWAP");
    for (int i = 0; i < cg_array_size(dest); i++) {
        int v;
        cg_array_at(array, i, AS_MEMORY(v));
        TEST_ASSERT_EQUAL_INT32_MESSAGE(v, i + 1, "VALUES ARE DIFFERENT AFTER SWAP");
    }
}

void tearDown(void) { cg_array_destroy(array); }

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CGArray_insert);
    RUN_TEST(test_CGArray_copy);
    RUN_TEST(test_CGArray_fill);
    RUN_TEST(test_CGArray_assign);

    return UNITY_END();
}
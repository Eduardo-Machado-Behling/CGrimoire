#include <CGrimoire/string.h>
#include <unity.h>

cg_string_t *string;

size_t hash_func(const void *key, size_t key_size, void *extra_args) {
    size_t sum = 0;

    const byte_t *keyB = key;
    for (size_t i = 0; i < key_size; i++) {
        sum += keyB[i];
    }

    return sum;
}

void setUp(void) { string = cg_string_create(20); }

void test_CGstring_usage(void) {
    cg_string_assign(string, "Hello");

    TEST_ASSERT_TRUE(cg_string_starts_with(string, "Hel"));
    TEST_ASSERT_FALSE(cg_string_starts_with(string, "Lo"));

    TEST_ASSERT_TRUE(cg_string_ends_with(string, "lo"));
    TEST_ASSERT_FALSE(cg_string_ends_with(string, "Hel"));

    TEST_ASSERT_TRUE(cg_string_contains(string, "lo"));
    TEST_ASSERT_TRUE(cg_string_contains(string, "Hel"));
    TEST_ASSERT_FALSE(cg_string_contains(string, "m"));
    TEST_ASSERT_FALSE(cg_string_contains(string, "mnt"));

    TEST_ASSERT_TRUE(cg_string_equal(string, "Hello"));
    TEST_ASSERT_FALSE(cg_string_equal(string, "hello"));

    TEST_ASSERT_EQUAL_CHAR('H', cg_string_front(string));
    TEST_ASSERT_EQUAL_CHAR('o', cg_string_back(string));

    const char *str = "Hello";
    const size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
        TEST_ASSERT_EQUAL_CHAR(str[i], cg_string_at(string, i));

    char buf[100];

    cg_string_cstr(string, buf);
    TEST_ASSERT_EQUAL_INT(0, strcmp(str, buf));
}

void tearDown(void) { cg_string_destroy(&string); }

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CGstring_usage);

    return UNITY_END();
}
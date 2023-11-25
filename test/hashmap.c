#include <CGrimoire/hashmap.h>
#include <unity.h>

cg_hashmap_t *hashmap;

size_t hash_func(const void *key, size_t key_size, void *extra_args) {
    size_t sum = 0;

    const byte_t *keyB = key;
    for (size_t i = 0; i < key_size; i++) {
        sum += keyB[i];
    }

    return sum;
}

void setUp(void) { hashmap = cg_hashmap_create(hash_func, 10, sizeof(int32_t), sizeof(int32_t)); }

void test_CGHashmap_usage(void) {
    int32_t key = 10;
    int32_t data = 69;
    cg_hashmap_set(hashmap, CG_AS_MEMORY(key), NULL, CG_AS_MEMORY(data));

    int32_t get;
    cg_hashmap_get(hashmap, CG_AS_MEMORY(key), NULL, CG_AS_MEMORY(get));

    TEST_ASSERT_EQUAL_INT(data, get);
}

void tearDown(void) { cg_hashmap_destroy(&hashmap); }

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_CGHashmap_usage);

    return UNITY_END();
}
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_utils/hash_map.h"

/* --- Helper Callbacks (Strings) --- */

static size_t string_hash(const void *key) {
    const char *str = (const char *)key;
    size_t hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + (size_t)c; /* hash * 33 + c */
    }

    return hash;
}

static int string_compare(const void *k1, const void *k2) {
    return strcmp((const char *)k1, (const char *)k2);
}

/* --- Tests --- */

static void test_creation_and_destruction(void) {
    /* Invalid arguments */
    assert(hash_map_create(NULL, string_compare) == NULL);
    assert(hash_map_create(string_hash, NULL) == NULL);

    HashMap *map = hash_map_create(string_hash, string_compare);
    assert(map != NULL);
    assert(hash_map_is_empty(map) == true);
    assert(hash_map_size(map) == 0);

    hash_map_destroy(map, NULL);
}

static void test_put_get_and_contains(void) {
    HashMap *map = hash_map_create(string_hash, string_compare);

    char *k1 = "user1";
    char *v1 = "Gabriel";
    char *k2 = "user2";
    char *v2 = "Linux";

    assert(hash_map_put(map, k1, v1) == true);
    assert(hash_map_put(map, k2, v2) == true);

    assert(hash_map_size(map) == 2);
    assert(hash_map_is_empty(map) == false);

    assert(hash_map_contains(map, "user1") == true);
    assert(hash_map_contains(map, "user2") == true);
    assert(hash_map_contains(map, "user3") == false);

    assert(strcmp((char *)hash_map_get(map, "user1"), "Gabriel") == 0);
    assert(strcmp((char *)hash_map_get(map, "user2"), "Linux") == 0);
    assert(hash_map_get(map, "user3") == NULL);

    hash_map_destroy(map, NULL);
}

static void test_overwrite_value(void) {
    HashMap *map = hash_map_create(string_hash, string_compare);

    char *key = "config_mode";
    char *val1 = "debug";
    char *val2 = "release";

    assert(hash_map_put(map, key, val1) == true);
    assert(hash_map_size(map) == 1);
    assert(strcmp((char *)hash_map_get(map, key), "debug") == 0);

    /* Overwrite */
    assert(hash_map_put(map, key, val2) == true);
    assert(hash_map_size(map) == 1);
    assert(strcmp((char *)hash_map_get(map, key), "release") == 0);

    hash_map_destroy(map, NULL);
}

static void test_remove(void) {
    HashMap *map = hash_map_create(string_hash, string_compare);

    assert(hash_map_put(map, "k1", "v1") == true);
    assert(hash_map_put(map, "k2", "v2") == true);

    void *removed = hash_map_remove(map, "k1");
    assert(removed != NULL);
    assert(strcmp((char *)removed, "v1") == 0);

    assert(hash_map_size(map) == 1);
    assert(hash_map_contains(map, "k1") == false);
    assert(hash_map_get(map, "k1") == NULL);

    /* Remove non-existent */
    assert(hash_map_remove(map, "non_existent") == NULL);

    hash_map_destroy(map, NULL);
}

static void test_collisions(void) {
    HashMap *map = hash_map_create(string_hash, string_compare);

    /* Insert multiple keys to force bucket collisions in size 16 */
    char keys[50][16];
    char values[50][16];

    for (int i = 0; i < 50; i++) {
        snprintf(keys[i], sizeof(keys[i]), "key_%d", i);
        snprintf(values[i], sizeof(values[i]), "val_%d", i);
        assert(hash_map_put(map, keys[i], values[i]) == true);
    }

    assert(hash_map_size(map) == 50);

    for (int i = 0; i < 50; i++) {
        char *val = (char *)hash_map_get(map, keys[i]);
        assert(val != NULL);
        assert(strcmp(val, values[i]) == 0);
    }

    hash_map_destroy(map, NULL);
}

static void test_dynamic_memory_cleanup(void) {
    HashMap *map = hash_map_create(string_hash, string_compare);

    /* Test automatic memory release via free_fn */
    for (int i = 0; i < 10; i++) {
        char *k = malloc(32);
        char *v = malloc(32);
        assert(k != NULL && v != NULL);

        snprintf(k, 32, "dyn_key_%d", i);
        snprintf(v, 32, "dyn_val_%d", i);

        assert(hash_map_put(map, k, v) == true);
    }

    assert(hash_map_size(map) == 10);

    hash_map_destroy(map, free);
}

int main(void) {
    printf("Running HashMap unit tests...\n");

    test_creation_and_destruction();
    test_put_get_and_contains();
    test_overwrite_value();
    test_remove();
    test_collisions();
    test_dynamic_memory_cleanup();

    printf("All HashMap tests passed successfully!\n");
    return 0;
}
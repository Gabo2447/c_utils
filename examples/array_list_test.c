#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_utils/array_list.h"

/* --- Helpers --- */

static int* create_int(int value) {
    int *ptr = malloc(sizeof(int));
    assert(ptr != NULL);
    *ptr = value;
    return ptr;
}

static int int_compare(const void *a, const void *b) {
    const int *val1 = (const int *)a;
    const int *val2 = (const int *)b;
    return (*val1 - *val2);
}

/* --- Tests --- */

static void test_create_and_empty(void) {
    ArrayList *list = array_list_create();
    assert(list != NULL);
    assert(array_list_size(list) == 0);
    assert(array_list_is_empty(list) == true);
    assert(array_list_get(list, 0) == NULL);

    /* Casos nulos */
    assert(array_list_size(NULL) == 0);
    assert(array_list_is_empty(NULL) == true);
    assert(array_list_get(NULL, 0) == NULL);

    array_list_destroy(list, NULL);
}

static void test_add_and_resize(void) {
    ArrayList *list = array_list_create();
    assert(list != NULL);

    /* Test inserción con list == NULL */
    int *dummy = create_int(1);
    assert(array_list_add(NULL, dummy) == false);
    free(dummy);

    const int total_elements = 50;
    for (int i = 0; i < total_elements; i++) {
        bool added = array_list_add(list, create_int(i * 10));
        assert(added == true);
        assert(array_list_size(list) == (size_t)(i + 1));
    }

    assert(array_list_is_empty(list) == false);

    for (int i = 0; i < total_elements; i++) {
        int *val = (int*)array_list_get(list, (size_t)i);
        assert(val != NULL);
        assert(*val == i * 10);
    }

    array_list_destroy(list, free);
}

static void test_set_and_remove(void) {
    ArrayList *list = array_list_create();

    array_list_add(list, create_int(100)); // Index 0
    array_list_add(list, create_int(200)); // Index 1
    array_list_add(list, create_int(300)); // Index 2

    /* Test set */
    int *replacement = create_int(250);
    int *old_val = (int*)array_list_set(list, 1, replacement);
    assert(old_val != NULL && *old_val == 200);
    free(old_val);

    int *check_set = (int*)array_list_get(list, 1);
    assert(check_set != NULL && *check_set == 250);

    /* Set out of bounds y NULL guard */
    assert(array_list_set(list, 99, replacement) == NULL);
    assert(array_list_set(NULL, 0, replacement) == NULL);

    /* Test remove at index 0 */
    int *removed_head = (int*)array_list_remove(list, 0);
    assert(removed_head != NULL && *removed_head == 100);
    free(removed_head);
    assert(array_list_size(list) == 2);

    int *new_head = (int*)array_list_get(list, 0);
    assert(new_head != NULL && *new_head == 250);

    /* Out of bounds y NULL guard */
    assert(array_list_remove(list, 99) == NULL);
    assert(array_list_remove(NULL, 0) == NULL);

    array_list_destroy(list, free);
}

static void test_contains(void) {
    ArrayList *list = array_list_create();

    int *val1 = create_int(10);
    int *val2 = create_int(20);
    int *target_exist = create_int(20);
    int *target_absent = create_int(99);

    array_list_add(list, val1);
    array_list_add(list, val2);

    /* Búsquedas válidas */
    assert(array_list_contains(list, target_exist, int_compare) == true);
    assert(array_list_contains(list, target_absent, int_compare) == false);

    /* Casos límites y punteros nulos */
    assert(array_list_contains(NULL, target_exist, int_compare) == false);
    assert(array_list_contains(list, target_exist, NULL) == false);

    free(target_exist);
    free(target_absent);
    array_list_destroy(list, free);
}

static void test_clear_and_destroy(void) {
    ArrayList *list = array_list_create();

    for (int i = 0; i < 5; i++) {
        array_list_add(list, create_int(i));
    }

    assert(array_list_size(list) == 5);

    /* Clear using free */
    array_list_clear(list, free);
    assert(array_list_size(list) == 0);
    assert(array_list_is_empty(list) == true);

    array_list_add(list, create_int(999));
    assert(array_list_size(list) == 1);

    int *val = (int*)array_list_get(list, 0);
    assert(val != NULL && *val == 999);

    /* Clear & Destroy with NULL points */
    array_list_clear(NULL, free);
    array_list_destroy(NULL, free);

    array_list_destroy(list, free);
}

int main(void) {
    printf("Running ArrayList unit tests...\n");

    test_create_and_empty();
    test_add_and_resize();
    test_set_and_remove();
    test_contains();
    test_clear_and_destroy();

    printf("All ArrayList tests passed successfully!\n");
    return 0;
}
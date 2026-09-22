#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_utils/array_list.h"

// Helper function to allocate integers on the heap
static int* create_int(int value) {
    int *ptr = malloc(sizeof(int));
    assert(ptr != NULL);
    *ptr = value;
    return ptr;
}

// Callback to verify that array_list_destroy and array_list_clear properly free memory
static void custom_free(void *ptr) {
    free(ptr);
}

// Basic creation and initial state inspection test
static void test_create_and_empty(void) {
    printf("Running test_create_and_empty...\n");

    ArrayList *list = array_list_create();
    assert(list != NULL);
    assert(array_list_size(list) == 0);
    assert(array_list_is_empty(list) == true);
    assert(array_list_get(list, 0) == NULL);

    array_list_destroy(list, NULL);
    printf("PASSED\n");
}

// Insertion (add) and automatic dynamic reallocation (resize) test
static void test_add_and_resize(void) {
    printf("Running test_add_and_resize...\n");

    ArrayList *list = array_list_create();
    assert(list != NULL);

    // Insert more elements than the default initial capacity (10)
    const int total_elements = 50;
    for (int i = 0; i < total_elements; i++) {
        bool added = array_list_add(list, create_int(i * 10));
        assert(added == true);
        assert(array_list_size(list) == (size_t)(i + 1));
    }

    assert(array_list_is_empty(list) == false);

    // Verify data integrity across all elements after multiple reallocations
    for (int i = 0; i < total_elements; i++) {
        int *val = (int*)array_list_get(list, (size_t)i);
        assert(val != NULL);
        assert(*val == i * 10);
    }

    array_list_destroy(list, custom_free);
    printf("PASSED\n");
}

// Modification (set) and removal (remove) with element shifting test
static void test_set_and_remove(void) {
    printf("Running test_set_and_remove...\n");

    ArrayList *list = array_list_create();

    array_list_add(list, create_int(100)); // Index 0
    array_list_add(list, create_int(200)); // Index 1
    array_list_add(list, create_int(300)); // Index 2

    // Test set
    int *replacement = create_int(250);
    int *old_val = (int*)array_list_set(list, 1, replacement);
    assert(old_val != NULL && *old_val == 200);
    free(old_val); // Free the replaced value

    int *check_set = (int*)array_list_get(list, 1);
    assert(check_set != NULL && *check_set == 250);

    // Test remove at head (index 0) -> Shifts remaining elements to the left
    int *removed_head = (int*)array_list_remove(list, 0);
    assert(removed_head != NULL && *removed_head == 100);
    free(removed_head);
    assert(array_list_size(list) == 2);

    // After removal, index 0 must contain 250
    int *new_head = (int*)array_list_get(list, 0);
    assert(new_head != NULL && *new_head == 250);

    // Attempt out-of-bounds removal (must return NULL)
    assert(array_list_remove(list, 99) == NULL);

    array_list_destroy(list, custom_free);
    printf("PASSED\n");
}

// Reset and full destruction test
static void test_clear_and_destroy(void) {
    printf("Running test_clear_and_destroy...\n");

    ArrayList *list = array_list_create();

    for (int i = 0; i < 5; i++) {
        array_list_add(list, create_int(i));
    }

    assert(array_list_size(list) == 5);

    // Clear list using the element destructor callback
    array_list_clear(list, custom_free);
    assert(array_list_size(list) == 0);
    assert(array_list_is_empty(list) == true);

    // Insert again after clearing
    array_list_add(list, create_int(999));
    assert(array_list_size(list) == 1);

    int *val = (int*)array_list_get(list, 0);
    assert(val != NULL && *val == 999);

    array_list_destroy(list, custom_free);
    printf("PASSED\n");
}

int main(void) {
    printf("=== RUNNING ARRAY_LIST TESTS ===\n\n");

    test_create_and_empty();
    test_add_and_resize();
    test_set_and_remove();
    test_clear_and_destroy();

    printf("\n=== ALL TESTS PASSED SUCCESSFULLY ===\n");
    return 0;
}
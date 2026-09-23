#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_utils/linked_list.h"

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
    LinkedList *list = linked_list_create();
    assert(list != NULL);
    assert(linked_list_is_empty(list) == true);
    assert(linked_list_size(list) == 0);
    assert(linked_list_get(list, 0) == NULL);

    /* Cases Involving NULL Pointers */
    assert(linked_list_is_empty(NULL) == true);
    assert(linked_list_size(NULL) == 0);
    assert(linked_list_get(NULL, 0) == NULL);

    linked_list_destroy(list, NULL);
}

static void test_add_and_get(void) {
    LinkedList *list = linked_list_create();
    assert(list != NULL);

    /* Rejecting an add to the NULL list */
    int *dummy = create_int(1);
    assert(linked_list_add(NULL, dummy) == false);
    free(dummy);

    /* Add elements (try optimizing head/tail access) */
    const int total = 10;
    for (int i = 0; i < total; i++) {
        assert(linked_list_add(list, create_int(i * 5)) == true);
        assert(linked_list_size(list) == (size_t)(i + 1));
    }

    assert(linked_list_is_empty(list) == false);

    /* Reading Elements */
    for (int i = 0; i < total; i++) {
        int *val = (int*)linked_list_get(list, (size_t)i);
        assert(val != NULL);
        assert(*val == i * 5);
    }

    /* Out of bounds */
    assert(linked_list_get(list, 99) == NULL);

    linked_list_destroy(list, free);
}

static void test_set_and_remove(void) {
    LinkedList *list = linked_list_create();

    linked_list_add(list, create_int(100)); // Index 0 (head)
    linked_list_add(list, create_int(200)); // Index 1
    linked_list_add(list, create_int(300)); // Index 2 (tail)

    /* Test set */
    int *replacement = create_int(250);
    int *old_val = (int*)linked_list_set(list, 1, replacement);
    assert(old_val != NULL && *old_val == 200);
    free(old_val);

    int *check_set = (int*)linked_list_get(list, 1);
    assert(check_set != NULL && *check_set == 250);

    /* Replace out-of-range or NULL values */
    assert(linked_list_set(list, 99, replacement) == NULL);
    assert(linked_list_set(NULL, 0, replacement) == NULL);

    /* Test removal from the head */
    int *removed_head = (int*)linked_list_remove(list, 0);
    assert(removed_head != NULL && *removed_head == 100);
    free(removed_head);
    assert(linked_list_size(list) == 2);

    /* Test remove from the tail */
    int *removed_tail = (int*)linked_list_remove(list, 1);
    assert(removed_tail != NULL && *removed_tail == 300);
    free(removed_tail);
    assert(linked_list_size(list) == 1);

    /* Only index 0 remains, with a value of 250 */
    int *remaining = (int*)linked_list_get(list, 0);
    assert(remaining != NULL && *remaining == 250);

    /* Attempting to remove an invalid index */
    assert(linked_list_remove(list, 99) == NULL);
    assert(linked_list_remove(NULL, 0) == NULL);

    linked_list_destroy(list, free);
}

static void test_contains_and_find(void) {
    LinkedList *list = linked_list_create();

    int *v1 = create_int(10);
    int *v2 = create_int(20);
    int *v3 = create_int(30);

    linked_list_add(list, v1);
    linked_list_add(list, v2);
    linked_list_add(list, v3);

    int search_target = 20;
    int absent_target = 99;

    /* Contains */
    assert(linked_list_contains(list, &search_target, int_compare) == true);
    assert(linked_list_contains(list, &absent_target, int_compare) == false);

    /* Find */
    int *found_ptr = (int*)linked_list_find(list, &search_target, int_compare);
    assert(found_ptr != NULL && *found_ptr == 20);

    int *not_found_ptr = (int*)linked_list_find(list, &absent_target, int_compare);
    assert(not_found_ptr == NULL);

    /* Edge Cases Involving NULL */
    assert(linked_list_contains(NULL, &search_target, int_compare) == false);
    assert(linked_list_contains(list, &search_target, NULL) == false);
    assert(linked_list_find(NULL, &search_target, int_compare) == NULL);
    assert(linked_list_find(list, &search_target, NULL) == NULL);

    linked_list_destroy(list, free);
}

static void test_clear_and_destroy(void) {
    LinkedList *list = linked_list_create();

    for (int i = 0; i < 5; i++) {
        linked_list_add(list, create_int(i));
    }

    assert(linked_list_size(list) == 5);

    /* Clear */
    linked_list_clear(list, free);
    assert(linked_list_size(list) == 0);
    assert(linked_list_is_empty(list) == true);

    /* Reuse After clear */
    linked_list_add(list, create_int(777));
    assert(linked_list_size(list) == 1);

    int *val = (int*)linked_list_get(list, 0);
    assert(val != NULL && *val == 777);

    /* Resilience Against NULL Calls */
    linked_list_clear(NULL, free);
    linked_list_destroy(NULL, free);

    linked_list_destroy(list, free);
}

int main(void) {
    printf("Running LinkedList unit tests...\n");

    test_create_and_empty();
    test_add_and_get();
    test_set_and_remove();
    test_contains_and_find();
    test_clear_and_destroy();

    printf("All LinkedList tests passed successfully!\n");
    return 0;
}
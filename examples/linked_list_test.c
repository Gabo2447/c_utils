#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_utils/linked_list.h"

static void test_linked_list(void) {
    LinkedList* list = linked_list_create();
    assert(list != NULL);
    assert(linked_list_is_empty(list) == true);
    assert(linked_list_size(list) == 0);

    // Add elements
    assert(linked_list_add(list, strdup("Ubuntu")) == true);
    assert(linked_list_add(list, strdup("Fedora")) == true);
    assert(linked_list_add(list, strdup("CachyOS")) == true);
    assert(linked_list_add(list, strdup("Debian")) == true);

    // Verify the state
    assert(linked_list_size(list) == 4);
    assert(linked_list_is_empty(list) == false);

    assert(strcmp((char*) linked_list_get(list, 0), "Ubuntu") == 0);
    assert(strcmp((char*) linked_list_get(list, 1), "Fedora") == 0);
    assert(strcmp((char*) linked_list_get(list, 2), "CachyOS") == 0);
    assert(strcmp((char*) linked_list_get(list, 3), "Debian") == 0);

    //  Test replacement (set) and release the old element
    char* old_distro = (char*) linked_list_set(list, 1, strdup("Arch"));
    assert(strcmp(old_distro, "Fedora") == 0);
    free(old_distro);
    assert(strcmp((char*) linked_list_get(list, 1), "Arch") == 0);

    // Test remove method
    char* removed_distro = (char*) linked_list_remove(list, 2);
    assert(strcmp(removed_distro, "CachyOS") == 0);
    free(removed_distro);
    assert(linked_list_size(list) == 3);

    // Total destruction of the list
    linked_list_destroy(list, free);

    printf("[PASS] All linked list tests passed successfully.\n");
}

int main(void) {
    test_linked_list();
    return 0;
}
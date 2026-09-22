#include <string.h>
#include <stdlib.h>

#include "c_utils/array_list.h"

#define INITIAL_CAPACITY 10

struct ArrayList {
    size_t size;
    size_t capacity;
    void **items;
};

static bool resize_array_list(ArrayList *list) {
    const size_t new_capacity = list->capacity * 2;
    void **new_items = realloc(list->items, sizeof(void *) * new_capacity);

    if (!new_items) {
        return false;
    }

    list->items = new_items;
    list->capacity = new_capacity;
    return true;
}

static bool check_array_list_size(const ArrayList *list) {
    return list->size >= list->capacity;
}

ArrayList* array_list_create(void) {
    ArrayList *list = malloc(sizeof(ArrayList));
    if (!list) {
        return NULL;
    }

    list->items = malloc(sizeof(void *) * INITIAL_CAPACITY);
    if (!list->items) {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;

    return list;
}

bool array_list_add(ArrayList *list, void* element) {
    if (!list) {
        return false;
    }

    if (check_array_list_size(list)) {
        if (!resize_array_list(list)) {
            return false;
        }
    }

    list->items[list->size] = element;
    list->size++;

    return true;
}

void* array_list_get(const ArrayList *list, size_t index) {
    if (!list || index >= list->size) {
        return NULL;
    }

    return list->items[index];
}

void* array_list_set(ArrayList *list, size_t index, void* element) {
    if (!list || index >= list->size) {
        return NULL;
    }

    void* old_element = list->items[index];
    list->items[index] = element;
    return old_element;
}

void* array_list_remove(ArrayList *list, size_t index) {
    if (!list || index >= list->size) {
        return NULL;
    }

    void* old_element = list->items[index];
    const size_t elements_to_move = list->size - index - 1;

    if (elements_to_move > 0) {
        memmove(&list->items[index], &list->items[index + 1], elements_to_move * sizeof(void *));
    }

    list->items[list->size-1] = NULL;
    list->size--;

    return old_element;
}

size_t array_list_size(const ArrayList *list) {
    if (!list) {
        return 0;
    }

    return list->size;
}

bool array_list_is_empty(const ArrayList *list) {
    return array_list_size(list) == 0;
}

void array_list_clear(ArrayList *list, void (*free_fn)(void*)) {
    if (!list) {
        return;
    }

    if (free_fn) {
        for (size_t index = 0; index < list->size; index++) {
            if (list->items[index]) {
                free_fn(list->items[index]);
                list->items[index] = NULL;
            }
        }
    }

    list->size = 0;
}

void array_list_destroy(ArrayList *list, void (*free_fn)(void*)) {
    array_list_clear(list, free_fn);
    free(list->items);
    free(list);
}

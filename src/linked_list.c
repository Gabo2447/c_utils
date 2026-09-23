#include "c_utils/linked_list.h"

#include <stdlib.h>

typedef struct Node {
    void* data;
    struct Node* next;
    struct Node* prev;
} Node;

struct LinkedList {
    Node* head;
    Node* tail;
    size_t size;
};

static Node* linked_list_get_at(const LinkedList* list, size_t index) {
    if (!list || index >= list->size) {
        return NULL;
    }

    Node* current;

    if (index >= (list->size / 2)) {
        current = list->tail;
        for (size_t i = list->size - 1; i > index; i--) {
            current = current->prev;
        }
    } else {
        current = list->head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
    }

    return current;
}

LinkedList* linked_list_create() {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

bool linked_list_add(LinkedList* list, void* element) {
    if (!list) {
        return false;
    }

    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return false;
    }

    new_node->data = element;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (!list->head) {
        list->head = new_node;
    } else {
        list->tail->next = new_node;
    }

    list->tail = new_node;
    list->size++;

    return true;
}

void* linked_list_remove(LinkedList* list, size_t index) {
    Node* target = linked_list_get_at(list, index);
    if (!target) {
        return NULL;
    }

    void *data = target->data;

    if (target->prev) {
        target->prev->next = target->next;
    } else {
        list->head = target->next;
    }

    if (target->next) {
        target->next->prev = target->prev;
    } else {
        list->tail = target->prev;
    }

    free(target);
    list->size--;

    return data;
}

void* linked_list_set(LinkedList* list, size_t index, void* element) {
    Node *current = linked_list_get_at(list, index);
    if (!current) {
        return NULL;
    }

    void *old_element = current->data;
    current->data = element;

    return old_element;
}

void* linked_list_get(const LinkedList* list, size_t index) {
    Node *current = linked_list_get_at(list, index);
    if (!current) {
        return NULL;
    }

    return current->data;
}

size_t linked_list_size(const LinkedList* list) {
    if (!list) {
        return 0;
    }

    return list->size;
}

bool linked_list_is_empty(const LinkedList* list) {
    return linked_list_size(list) == 0;
}

bool linked_list_contains(const LinkedList *list, const void *element, CompareFn cmp_fn) {
    if (!list || !cmp_fn) {
        return false;
    }

    Node *current = list->head;
    while (current != NULL) {
        if (cmp_fn(current->data, element) == 0) {
            return true;
        }
        current = current->next;
    }

    return false;
}

void linked_list_clear(LinkedList* list, void (*free_fn)(void*)) {
    if (!list || !list->head) {
        return;
    }

    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;

        if (free_fn && current->data) {
            free_fn(current->data);
        }

        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void linked_list_destroy(LinkedList* list, void (*free_fn)(void*)) {
    if (!list) {
        return;
    }

    linked_list_clear(list, free_fn);
    free(list);
}
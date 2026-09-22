#include "c_utils/queue.h"

#include <stdlib.h>

#include "c_utils/linked_list.h"

struct Queue {
    LinkedList *list;
};

Queue* queue_create(void) {
    Queue *queue = malloc(sizeof(Queue));
    if (!queue) {
        return NULL;
    }

    queue->list = linked_list_create();
    if (!queue->list) {
        free(queue);
        return NULL;
    }

    return queue;
}

bool queue_is_empty(const Queue *queue) {
    if (!queue || !queue->list) {
        return true;
    }
    return linked_list_is_empty(queue->list);
}

size_t queue_size(const Queue *queue) {
    return linked_list_size(queue->list);
}

bool queue_enqueue(Queue *queue, const void *data) {
    if (!queue || !queue->list || !data) {
        return false;
    }

    return linked_list_add(queue->list, (void*)data);
}

void* queue_dequeue(Queue *queue) {
    if (!queue || !queue->list || queue_is_empty(queue)) {
        return NULL;
    }

    return linked_list_remove(queue->list, 0);
}

void* queue_peek(const Queue *queue) {
    if (!queue || !queue->list || queue_is_empty(queue)) {
        return NULL;
    }

    return linked_list_get(queue->list, 0);
}

void queue_clear(Queue *queue, void (*free_fn)(void*)) {
    if (!queue) {
        return;
    }

    linked_list_clear(queue->list, free_fn);
}

void queue_destroy(Queue *queue, void (*free_fn)(void*)) {
    if (!queue) {
        return;
    }

    if (queue->list) {
        linked_list_destroy(queue->list, free_fn);
    }

    free(queue);
}
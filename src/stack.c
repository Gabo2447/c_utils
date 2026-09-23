#include "c_utils/stack.h"
#include "c_utils/array_list.h"

#include <stdlib.h>

struct Stack {
    ArrayList *list;
};

Stack *stack_create(void) {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) {
        return NULL;
    }

    stack->list = array_list_create();
    if (!stack->list) {
        free(stack);
        return NULL;
    }

    return stack;
}

bool stack_is_empty(const Stack *stack) {
    if (!stack || !stack->list) {
        return true;
    }
    return array_list_is_empty(stack->list);
}

size_t stack_size(const Stack *stack) {
    if (!stack || !stack->list) {
        return 0;
    }
    return array_list_size(stack->list);
}

bool stack_push(Stack *stack, const void *data) {
    if (!stack || !stack->list || !data) {
        return false;
    }

    return array_list_add(stack->list, (void *)data);
}

void* stack_pop(Stack *stack) {
    if (!stack || !stack->list || stack_is_empty(stack)) {
        return NULL;
    }

    size_t top_index = array_list_size(stack->list) - 1;
    return array_list_remove(stack->list, top_index);
}

void* stack_peek(const Stack *stack) {
    if (!stack || !stack->list || stack_is_empty(stack)) {
        return NULL;
    }

    size_t top_index = array_list_size(stack->list) - 1;
    return array_list_get(stack->list, top_index);
}

void stack_clear(Stack *stack, void (*free_fn)(void*)) {
    if (!stack || !stack->list) {
        return;
    }

    array_list_clear(stack->list, free_fn);
}

void stack_destroy(Stack *stack, void (*free_fn)(void*)) {
    if (!stack) {
        return;
    }

    if (stack->list) {
        array_list_destroy(stack->list, free_fn);
    }

    free(stack);
}
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_utils/stack.h"

/* --- Helpers --- */

static int* create_int(int value) {
    int *ptr = malloc(sizeof(int));
    assert(ptr != NULL);
    *ptr = value;
    return ptr;
}

/* --- Tests --- */

static void test_stack_create_and_empty(void) {
    Stack *stack = stack_create();
    assert(stack != NULL);
    assert(stack_is_empty(stack) == true);
    assert(stack_size(stack) == 0);
    assert(stack_peek(stack) == NULL);
    assert(stack_pop(stack) == NULL);

    /* Edge Cases Involving NULL Pointers */
    assert(stack_is_empty(NULL) == true);
    assert(stack_size(NULL) == 0);
    assert(stack_peek(NULL) == NULL);
    assert(stack_pop(NULL) == NULL);

    stack_destroy(stack, NULL);
}

static void test_stack_lifo_operations(void) {
    Stack *stack = stack_create();
    assert(stack != NULL);

    int *v1 = create_int(100);
    int *v2 = create_int(200);
    int *v3 = create_int(300);

    /* Push Elements */
    assert(stack_push(stack, v1) == true);
    assert(stack_push(stack, v2) == true);
    assert(stack_push(stack, v3) == true);

    /* Reject NULL data or operations on NULL stack */
    assert(stack_push(stack, NULL) == false);
    assert(stack_push(NULL, v1) == false);

    assert(stack_size(stack) == 3);
    assert(stack_is_empty(stack) == false);

    /* Peek (Top element should be v3) */
    int *top = (int*)stack_peek(stack);
    assert(top != NULL && *top == 300);
    assert(stack_size(stack) == 3);

    /* Pop respecting LIFO order */
    int *popped1 = (int*)stack_pop(stack);
    assert(popped1 != NULL && *popped1 == 300);
    assert(stack_size(stack) == 2);
    free(popped1);

    int *popped2 = (int*)stack_pop(stack);
    assert(popped2 != NULL && *popped2 == 200);
    assert(stack_size(stack) == 1);
    free(popped2);

    int *popped3 = (int*)stack_pop(stack);
    assert(popped3 != NULL && *popped3 == 100);
    assert(stack_size(stack) == 0);
    assert(stack_is_empty(stack) == true);
    free(popped3);

    /* Attempting to pop from an empty stack */
    assert(stack_pop(stack) == NULL);

    stack_destroy(stack, free);
}

static void test_stack_clear_and_destroy(void) {
    Stack *stack = stack_create();
    assert(stack != NULL);

    for (int i = 0; i < 5; i++) {
        assert(stack_push(stack, create_int(i * 10)) == true);
    }

    assert(stack_size(stack) == 5);

    /* Clear memory using callback */
    stack_clear(stack, free);
    assert(stack_size(stack) == 0);
    assert(stack_is_empty(stack) == true);
    assert(stack_peek(stack) == NULL);

    /* Reuse stack after clear */
    assert(stack_push(stack, create_int(999)) == true);
    assert(stack_size(stack) == 1);

    int *val = (int*)stack_peek(stack);
    assert(val != NULL && *val == 999);

    /* Resilience against NULL calls */
    stack_clear(NULL, free);
    stack_destroy(NULL, free);

    stack_destroy(stack, free);
}

int main(void) {
    printf("Running Stack unit tests...\n");

    test_stack_create_and_empty();
    test_stack_lifo_operations();
    test_stack_clear_and_destroy();

    printf("All Stack tests passed successfully!\n");
    return 0;
}
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_utils/queue.h"

/* --- Helpers --- */

static int* create_int(int value) {
    int *ptr = malloc(sizeof(int));
    assert(ptr != NULL);
    *ptr = value;
    return ptr;
}

/* --- Tests --- */

static void test_queue_create_and_empty(void) {
    Queue *queue = queue_create();
    assert(queue != NULL);
    assert(queue_is_empty(queue) == true);
    assert(queue_size(queue) == 0);
    assert(queue_peek(queue) == NULL);
    assert(queue_dequeue(queue) == NULL);

    /* Guardas para punteros NULL */
    assert(queue_is_empty(NULL) == true);
    assert(queue_size(NULL) == 0);
    assert(queue_peek(NULL) == NULL);
    assert(queue_dequeue(NULL) == NULL);

    queue_destroy(queue, NULL);
}

static void test_queue_fifo_operations(void) {
    Queue *queue = queue_create();
    assert(queue != NULL);

    int *val1 = create_int(10);
    int *val2 = create_int(20);
    int *val3 = create_int(30);

    /* Enqueue */
    assert(queue_enqueue(queue, val1) == true);
    assert(queue_enqueue(queue, val2) == true);
    assert(queue_enqueue(queue, val3) == true);

    /* Rechar inserción de datos NULL o en colas NULL */
    assert(queue_enqueue(queue, NULL) == false);
    assert(queue_enqueue(NULL, val1) == false);

    assert(queue_size(queue) == 3);
    assert(queue_is_empty(queue) == false);

    /* Peek (no debe eliminar el elemento) */
    int *peeked = (int*)queue_peek(queue);
    assert(peeked != NULL && *peeked == 10);
    assert(queue_size(queue) == 3);

    /* Dequeue respetando FIFO */
    int *dequeued1 = (int*)queue_dequeue(queue);
    assert(dequeued1 != NULL && *dequeued1 == 10);
    assert(queue_size(queue) == 2);
    free(dequeued1);

    int *dequeued2 = (int*)queue_dequeue(queue);
    assert(dequeued2 != NULL && *dequeued2 == 20);
    assert(queue_size(queue) == 1);
    free(dequeued2);

    int *dequeued3 = (int*)queue_dequeue(queue);
    assert(dequeued3 != NULL && *dequeued3 == 30);
    assert(queue_size(queue) == 0);
    assert(queue_is_empty(queue) == true);
    free(dequeued3);

    /* Intentar desencolar cuando está vacía */
    assert(queue_dequeue(queue) == NULL);

    queue_destroy(queue, free);
}

static void test_queue_clear_and_destroy(void) {
    Queue *queue = queue_create();
    assert(queue != NULL);

    for (int i = 0; i < 5; i++) {
        assert(queue_enqueue(queue, create_int(i * 100)) == true);
    }

    assert(queue_size(queue) == 5);

    /* Limpieza de elementos manteniendo la estructura */
    queue_clear(queue, free);
    assert(queue_size(queue) == 0);
    assert(queue_is_empty(queue) == true);
    assert(queue_peek(queue) == NULL);

    /* Reutilización tras clear */
    assert(queue_enqueue(queue, create_int(999)) == true);
    assert(queue_size(queue) == 1);

    int *val = (int*)queue_peek(queue);
    assert(val != NULL && *val == 999);

    /* Resiliencia ante llamadas NULL */
    queue_clear(NULL, free);
    queue_destroy(NULL, free);

    queue_destroy(queue, free);
}

int main(void) {
    printf("Running Queue unit tests...\n");

    test_queue_create_and_empty();
    test_queue_fifo_operations();
    test_queue_clear_and_destroy();

    printf("All Queue tests passed successfully!\n");
    return 0;
}
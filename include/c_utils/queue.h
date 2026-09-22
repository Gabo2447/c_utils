#ifndef C_UTILS_QUEUE_H
#define C_UTILS_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @file queue.h
 * @brief Generic First-In-First-Out (FIFO) Queue implementation.
 *
 * This header defines the public API for a thread-unsafe, generic Queue structure.
 * It stores element references as void pointers (`const void*` and `void*`).
 */

/**
 * @brief Opaque structure representing the Queue.
 */
typedef struct Queue Queue;

/**
 * @brief Allocates and initializes a new Queue instance.
 *
 * @return Pointer to the newly created Queue, or `NULL` if allocation fails.
 */
Queue* queue_create(void);

/**
 * @brief Checks whether the queue contains no elements.
 *
 * @param queue Pointer to the Queue structure.
 * @return `true` if the queue is empty or if `queue` is NULL; `false` otherwise.
 */
bool queue_is_empty(const Queue *queue);

/**
 * @brief Gets the number of elements currently stored in the queue.
 *
 * @param queue Pointer to the Queue structure.
 * @return The number of elements, or 0 if `queue` is NULL.
 */
size_t queue_size(const Queue *queue);

/**
 * @brief Inserts an element at the rear of the queue.
 *
 * @param queue Pointer to the Queue structure.
 * @param data  Pointer to the user data to store.
 * @return `true` if the element was successfully enqueued; `false` if `queue` or `data` is NULL,
 *         or if memory allocation fails.
 */
bool queue_enqueue(Queue *queue, const void *data);

/**
 * @brief Removes and returns the element at the front of the queue.
 *
 * @param queue Pointer to the Queue structure.
 * @return Pointer to the dequeued element, or `NULL` if the queue is NULL or empty.
 * @note Dequeuing does not free the underlying user data memory.
 */
void* queue_dequeue(Queue *queue);

/**
 * @brief Inspects the element at the front of the queue without removing it.
 *
 * @param queue Pointer to the Queue structure.
 * @return Pointer to the front element, or `NULL` if the queue is NULL or empty.
 */
void* queue_peek(const Queue *queue);

/**
 * @brief Removes all elements from the queue without destroying the Queue container.
 *
 * @param queue   Pointer to the Queue structure.
 * @param free_fn Optional function pointer to release memory of each stored element.
 *                If NULL, elements are removed without freeing user payloads.
 */
void queue_clear(Queue *queue, void (*free_fn)(void*));

/**
 * @brief Clears all elements and deallocates the Queue container itself.
 *
 * @param queue   Pointer to the Queue structure to destroy.
 * @param free_fn Optional function pointer to release memory of each stored element.
 *                Can be NULL if elements do not require dynamic cleanup.
 *
 * @see queue_clear
 */
void queue_destroy(Queue *queue, void (*free_fn)(void*));

#endif //C_UTILS_QUEUE_H

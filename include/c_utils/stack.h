#ifndef C_UTILS_STACK_H
#define C_UTILS_STACK_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @file stack.h
 * @brief Generic Last-In-First-Out (LIFO) Stack implementation.
 */

typedef struct Stack Stack;

/**
 * @brief Allocates and initializes a new Stack instance.
 * @return Pointer to the newly created Stack, or NULL if allocation fails.
 */
Stack* stack_create(void);

/**
 * @brief Checks whether the stack contains no elements.
 * @param stack Pointer to the Stack structure.
 * @return true if the stack is empty or if stack is NULL; false otherwise.
 */
bool stack_is_empty(const Stack *stack);

/**
 * @brief Gets the number of elements currently stored in the stack.
 * @param stack Pointer to the Stack structure.
 * @return The number of elements, or 0 if stack is NULL.
 */
size_t stack_size(const Stack *stack);

/**
 * @brief Pushes an element onto the top of the stack.
 * @param stack Pointer to the Stack structure.
 * @param data  Pointer to the user data to store.
 * @return true if the element was successfully pushed; false if stack or data is NULL.
 */
bool stack_push(Stack *stack, const void *data);

/**
 * @brief Removes and returns the element at the top of the stack.
 * @param stack Pointer to the Stack structure.
 * @return Pointer to the popped element, or NULL if the stack is NULL or empty.
 */
void* stack_pop(Stack *stack);

/**
 * @brief Inspects the element at the top of the stack without removing it.
 * @param stack Pointer to the Stack structure.
 * @return Pointer to the top element, or NULL if the stack is NULL or empty.
 */
void* stack_peek(const Stack *stack);

/**
 * @brief Removes all elements from the stack without destroying the Stack container.
 * @param stack   Pointer to the Stack structure.
 * @param free_fn Optional callback function to release memory of stored elements.
 */
void stack_clear(Stack *stack, void (*free_fn)(void*));

/**
 * @brief Clears all elements and deallocates the Stack container itself.
 * @param stack   Pointer to the Stack structure to destroy.
 * @param free_fn Optional callback function to release memory of stored elements.
 */
void stack_destroy(Stack *stack, void (*free_fn)(void*));

#endif // C_UTILS_STACK_H
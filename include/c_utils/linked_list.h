#ifndef C_UTILS_LINKED_LIST_H
#define C_UTILS_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Opaque handle representing a generic singly linked list.
 */
typedef struct LinkedList LinkedList;

/**
 * @brief Allocates and initializes a new LinkedList instance.
 *
 * @return Pointer to the new LinkedList, or NULL on allocation failure.
 */
LinkedList* linked_list_create(void);

/**
 * @brief Appends an element to the tail of the list.
 *
 * @param list Target list instance.
 * @param element Pointer to user payload.
 * @return true on success, false if allocation fails or list is NULL.
 */
bool linked_list_add(LinkedList* list, void* element);

/**
 * @brief Removes an element by index, unlinking its node.
 *
 * @note Ownership of the payload pointer is transferred back to the caller.
 *       The internal node is freed, but the user data (`void*`) is NOT freed.
 *
 * @param list Target list instance.
 * @param index Zero-based node position.
 * @return Pointer to the stored payload, or NULL if index is out of bounds or list is NULL.
 */
void* linked_list_remove(LinkedList* list, size_t index);

/**
 * @brief Replaces the element payload at a given index.
 *
 * @warning The overwritten element is NOT freed automatically. If dynamic memory
 *          was previously assigned at this index, caller must retrieve/free it first.
 *
 * @param list Target list instance.
 * @param index Zero-based node position.
 * @param element Pointer to the new payload.
* @return void* Pointer to the replaced element payload, or NULL if index is out of bounds.
 */
void* linked_list_set(LinkedList* list, size_t index, void* element);

/**
 * @brief Fetches an element payload by index without modifying the list.
 *
 * @param list Target list instance (read-only).
 * @param index Zero-based node position.
 * @return Pointer to the payload, or NULL if index is out of bounds or list is NULL.
 */
void* linked_list_get(const LinkedList* list, size_t index);

/**
 * @brief Retrieves the current node count.
 *
 * @param list Target list instance (read-only).
 * @return Element count, or 0 if list is NULL.
 */
size_t linked_list_size(const LinkedList* list);

/**
 * @brief Checks if the list contains zero elements.
 *
 * @param list Target list instance (read-only).
 * @return true if empty or list is NULL, false otherwise.
 */
bool linked_list_is_empty(const LinkedList* list);

/**
 * @brief Frees all internal nodes, resetting size to 0. Keeps the list instance alive.
 *
 * @param list Target list instance.
 * @param free_fn Optional callback to free stored payloads (`free` or custom destructor).
 *                Pass NULL if elements are stack-allocated, static, or freed externally.
 */
void linked_list_clear(LinkedList* list, void (*free_fn)(void*));

/**
 * @brief Clears all internal elements and frees the LinkedList instance itself.
 *
 * @param list Target list instance. Handle becomes invalid after invocation.
 * @param free_fn Optional callback to free stored payloads. Pass NULL to retain payload memory.
 */
void linked_list_destroy(LinkedList* list, void (*free_fn)(void*));

#endif // C_UTILS_LINKED_LIST_H
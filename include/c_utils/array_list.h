#ifndef C_UTILS_ARRAY_LIST_H
#define C_UTILS_ARRAY_LIST_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Opaque structure representing the dynamic array.
 */
typedef struct ArrayList ArrayList;

/**
 * @brief Creates a new, empty ArrayList with a default initial capacity.
 *
 * @return Pointer to the newly allocated ArrayList, or NULL if memory allocation fails.
 */
ArrayList* array_list_create(void);

/**
 * @brief Appends an element to the end of the ArrayList.
 *
 * If the internal buffer is full, it automatically resizes.
 *
 * @param list Pointer to the ArrayList instance.
 * @param element Generic pointer (void*) to the data to store.
 * @return true if the element was successfully added, false if list is NULL or allocation failed.
 *
 * @note Amortized time complexity: O(1). Worst-case (when reallocation occurs): O(N).
 */
bool array_list_add(ArrayList *list, void* element);

/**
 * @brief Retrieves the element stored at the specified index without removing it.
 *
 * @param list Pointer to the constant ArrayList instance.
 * @param index Zero-based position of the element to retrieve.
 * @return Generic pointer to the stored element, or NULL if list is NULL or index is out of bounds.
 *
 * @note Time complexity: O(1).
 */
void* array_list_get(const ArrayList *list, size_t index);

/**
 * @brief Replaces the element at the specified index with a new element.
 *
 * @param list Pointer to the ArrayList instance.
 * @param index Zero-based position of the element to replace.
 * @param element Generic pointer to the new element.
 * @return Generic pointer to the previously stored element (so caller can free or reuse it),
 *         or NULL if list is NULL or index is out of bounds.
 *
 * @note Ownership of the replaced element is returned to the caller. Time complexity: O(1).
 */
void* array_list_set(ArrayList *list, size_t index, void* element);

/**
 * @brief Removes and returns the element at the specified index, shifting subsequent elements to the left.
 *
 * @param list Pointer to the ArrayList instance.
 * @param index Zero-based position of the element to remove.
 * @return Generic pointer to the removed element, or NULL if list is NULL or index is out of bounds.
 *
 * @note Time complexity: O(N) due to memory shifting (memmove).
 */
void* array_list_remove(ArrayList *list, size_t index);

/**
 * @brief Gets the current number of elements stored in the ArrayList.
 *
 * @param list Pointer to the constant ArrayList instance.
 * @return Number of elements, or 0 if list is NULL.
 *
 * @note Time complexity: O(1).
 */
size_t array_list_size(const ArrayList *list);

/**
 * @brief Checks whether the ArrayList contains no elements.
 *
 * @param list Pointer to the constant ArrayList instance.
 * @return true if the list is empty or NULL, false otherwise.
 *
 * @note Time complexity: O(1).
 */
bool array_list_is_empty(const ArrayList *list);

/**
 * @brief Removes all elements from the ArrayList and frees internal memory, leaving it ready for reuse.
 *
 * @param list Pointer to the ArrayList instance.
 * @param free_fn Optional callback function used to free each stored element's data.
 *                Pass NULL if elements do not require custom deallocation (e.g., stack data or primitives).
 *
 * @note Time complexity: O(N) if free_fn is provided, O(1) otherwise.
 */
void array_list_clear(ArrayList *list, void (*free_fn)(void*));

/**
 * @brief Deallocates all elements in the ArrayList and frees the list structure itself.
 *
 * @param list Pointer to the ArrayList instance.
 * @param free_fn Optional callback function used to free stored elements before destroying the list.
 *                Pass NULL if stored elements do not require custom deallocation.
 */
void array_list_destroy(ArrayList *list, void (*free_fn)(void*));

#endif // C_UTILS_ARRAY_LIST_H

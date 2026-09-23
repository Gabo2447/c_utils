#ifndef C_UTILS_HASH_MAP_H
#define C_UTILS_HASH_MAP_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Opaque structure representing a hash map using separate chaining.
 */
typedef struct HashMap HashMap;

/**
 * @brief Function pointer type for computing a key's hash value.
 * @param key Pointer to the key. Must not be NULL.
 * @return Computed hash code.
 */
typedef size_t (*HashFn)(const void *key);

/**
 * @brief Function pointer type for key comparison.
 * @param key1 Pointer to the first key.
 * @param key2 Pointer to the second key.
 * @return 0 if keys are equal, non-zero otherwise.
 */
typedef int (*CompareFn)(const void *key1, const void *key2);

/**
 * @brief Creates a new hash map instance.
 * @param hash_fn Function to hash keys. Must not be NULL.
 * @param cmp_fn Function to compare keys. Must not be NULL.
 * @return Pointer to the new HashMap, or NULL if allocation fails or parameters are NULL.
 */
HashMap* hash_map_create(HashFn hash_fn, CompareFn cmp_fn);

/**
 * @brief Destroys the hash map and frees all allocated internal nodes and bucket storage.
 * @param map Pointer to the map to destroy. If NULL, no action is taken.
 * @param free_fn Optional callback to free individual key and value pointers.
 *                Called separately for `key` and `value` if non-NULL. Can be NULL.
 */
void hash_map_destroy(HashMap *map, void (*free_fn)(void*));

/**
 * @brief Gets the number of key-value pairs stored in the map.
 * @param map Pointer to the map.
 * @return Element count, or 0 if map is NULL.
 */
size_t hash_map_size(const HashMap *map);

/**
 * @brief Checks if the map contains no key-value pairs.
 * @param map Pointer to the map.
 * @return true if empty or map is NULL, false otherwise.
 */
bool hash_map_is_empty(const HashMap *map);

/**
 * @brief Checks whether a given key exists in the map.
 * @param map Pointer to the map.
 * @param key Key to search for. Must not be NULL.
 * @return true if key is present, false otherwise or if parameters are NULL.
 */
bool hash_map_contains(const HashMap *map, const void *key);

/**
 * @brief Retrieves the value associated with a given key.
 * @param map Pointer to the map.
 * @param key Key to look up. Must not be NULL.
 * @return Pointer to the stored value, or NULL if key is not found or parameters are NULL.
 */
void* hash_map_get(const HashMap *map, const void *key);

/**
 * @brief Inserts a key-value pair into the map or updates the value if the key exists.
 * @note If the key exists, the old value is overwritten. If the old value was dynamically
 *       allocated, caller is responsible for freeing it prior to updating or managing its ownership.
 * @param map Pointer to the map.
 * @param key Pointer to the key. Must not be NULL.
 * @param data Pointer to the value.
 * @return true if insertion/update succeeded, false on allocation failure or NULL arguments.
 */
bool hash_map_put(HashMap *map, const void *key, const void *data);

/**
 * @brief Removes a key-value pair entry by key without invoking any cleanup callbacks.
 * @param map Pointer to the map.
 * @param key Key to remove. Must not be NULL.
 * @return Pointer to the removed value, or NULL if key was not found or parameters are NULL.
 */
void* hash_map_remove(HashMap *map, const void *key);

/**
 * @brief Removes all entries from the map, resetting size to 0 while keeping capacity intact.
 * @param map Pointer to the map. If NULL, no action is taken.
 * @param free_fn Optional callback to free individual key and value pointers.
 *                Called separately for `key` and `value` if non-NULL. Can be NULL.
 */
void hash_map_clear(HashMap *map, void (*free_fn)(void*));

#endif // C_UTILS_HASH_MAP_H

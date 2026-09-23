#include "c_utils/hash_map.h"

#include <stdlib.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct HashNode {
    void *key;
    void *value;
    struct HashNode *next;
} HashNode;

struct HashMap {
    HashNode **buckets;
    size_t capacity;
    size_t size;
    HashFn hash_fn;
    CompareFn cmp_fn;
};

static size_t get_hash(const HashMap *map, const void *key) {
    return map->hash_fn(key) % map->capacity;
}

static bool hash_map_resize(HashMap *map) {
    size_t new_capacity = map->capacity * 2;
    HashNode **new_buckets = calloc(new_capacity, sizeof(HashNode*));
    if (!new_buckets) {
        return false;
    }

    for (size_t i = 0; i < map->capacity; i++) {
        HashNode *current = map->buckets[i];
        while (current != NULL) {
            HashNode *next = current->next;

            size_t new_index = map->hash_fn(current->key) % new_capacity;

            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;

            current = next;
        }
    }

    free(map->buckets);
    map->buckets = new_buckets;
    map->capacity = new_capacity;

    return true;
}

HashMap* hash_map_create(HashFn hash_fn, CompareFn cmp_fn) {
    if (!hash_fn || !cmp_fn) {
        return NULL;
    }

    HashMap* map = malloc(sizeof(HashMap));
    if (!map) {
        return NULL;
    }

    map->buckets = calloc(INITIAL_CAPACITY, sizeof(HashNode*));
    if (!map->buckets) {
        free(map);
        return NULL;
    }

    map->capacity = INITIAL_CAPACITY;
    map->size = 0;
    map->hash_fn = hash_fn;
    map->cmp_fn = cmp_fn;

    return map;
}

void hash_map_clear(HashMap *map, void (*free_fn)(void*)) {
    if (!map) {
        return;
    }

    for (size_t i = 0; i < map->capacity; i++) {
        HashNode *current = map->buckets[i];
        while (current != NULL) {
            HashNode *next = current->next;
            if (free_fn) {
                if (current->key) {
                    free_fn(current->key);
                }
                if (current->value) {
                    free_fn(current->value);
                }
            }
            free(current);
            current = next;
        }
        map->buckets[i] = NULL;
    }
    map->size = 0;
}

void hash_map_destroy(HashMap *map, void (*free_fn)(void*)) {
    if (!map) {
        return;
    }

    hash_map_clear(map, free_fn);
    free(map->buckets);
    free(map);
}

size_t hash_map_size(const HashMap *map) {
    return map->size;
}

bool hash_map_is_empty(const HashMap *map) {
    return hash_map_size(map) == 0;
}

bool hash_map_contains(const HashMap *map, const void *key) {
    return hash_map_get(map, key) != NULL;
}

void* hash_map_get(const HashMap *map, const void *key) {
    if (!map || !key) {
        return NULL;
    }

    size_t index = get_hash(map, key);
    HashNode *current = map->buckets[index];

    while (current != NULL) {
        if (map->cmp_fn(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

bool hash_map_put(HashMap *map, const void *key, const void *data) {
    if (!map || !key) {
        return false;
    }

    size_t index = get_hash(map, key);
    HashNode *current = map->buckets[index];

    while (current != NULL) {
        if (map->cmp_fn(current->key, key) == 0) {
            current->value = (void*) data;
            return true;
        }
        current = current->next;
    }

    double current_load_factor = (double)(map->size + 1) / (double)map->capacity;
    if (current_load_factor > LOAD_FACTOR_THRESHOLD) {
        if (hash_map_resize(map)) {
            index = get_hash(map, key);
        }
    }

    HashNode *new_node = malloc(sizeof(HashNode));
    if (!new_node) {
        return false;
    }

    new_node->key = (void*) key;
    new_node->value = (void*) data;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
    map->size++;

    return true;
}

void* hash_map_remove(HashMap *map, const void *key) {
    if (!map || !key) {
        return NULL;
    }

    size_t index = get_hash(map, key);
    HashNode *current = map->buckets[index];
    HashNode *previous = NULL;

    while (current != NULL) {
        if (map->cmp_fn(current->key, key) == 0) {
            void *removed_value = current->value;

            if (previous == NULL) {
                map->buckets[index] = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            map->size--;
            return removed_value;
        }

        previous = current;
        current = current->next;
    }

    return NULL;
}
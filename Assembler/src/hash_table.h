/* Implementation of hash table data structure  */
#include "stdio.h"
#ifndef HASHTABLE__HASH_TABLE_H_
#define HASHTABLE__HASH_TABLE_H_

/******* Data structure declarations *******/

typedef ssize_t ht_value_t;

typedef struct {
  char* key;
  ht_value_t value;
} ht_item_t;

typedef struct {
  size_t base_capacity;
  size_t capacity;
  size_t size;
  ht_item_t** items;
} ht_hash_table_t;

/******* Operations on hash table *******/

/*
  Creates new hash table with capacity == HT_INITIAL_BASE_CAPACITY.
  Return NULL if could not allocate space.
*/
ht_hash_table_t* ht_create(void);

/*
  Creates new hash table with capacity == base_capacity.
  Return NULL if could not allocate space.
*/
ht_hash_table_t* ht_create_sized(size_t base_capacity);

/*
  Destroys hash table.
  Free all storage used by hash table.
*/
void ht_destroy(ht_hash_table_t* ht);

/* Inserts key-value pair to hash table */
void ht_insert(ht_hash_table_t* ht, const char* key, ht_value_t value);

/*
  Search value in hash table by key.
  Return -1 if no such key.
*/
ht_value_t ht_search(const ht_hash_table_t* ht, const char* key);

/* Deletes item in hash table by key */
void ht_delete(ht_hash_table_t* ht, const char* key);

#endif  // HASHTABLE__HASH_TABLE_H_

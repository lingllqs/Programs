#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>

// 错误处理宏
#define ERRP(condition, err_msg, handler) \
    do {                                  \
        if (condition) {                  \
            fprintf(stderr, err_msg);     \
            handler;                      \
        }                                 \
    } while (0);

#define HT_PRIME_1 150
#define HT_PRIME_2 250

typedef struct HashTableItem {
    char *key;
    char *value;
} HashTableItem;

typedef struct HashTable {
    int size;
    int count;
    HashTableItem **items;
} HashTable;

HashTableItem *ht_item_new(const char *key, const char *value);
HashTable *ht_new();
void ht_item_del(HashTableItem *item);
void ht_del(HashTable *ht);
int ht_hash(const char *s, const int a, const int m);
int ht_hash_get(const char *s, const int num_buckets, const int attempt);

void ht_insert(HashTable *ht, const char *key, const char *value);
char *ht_search(HashTable *ht, const char *key);
void ht_delete(HashTable *ht, const char *key);

#endif  // !HASH_TABLE_H

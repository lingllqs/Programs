#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>

// 错误处理宏
#define ERRP(condition, err_msg, handler)                                                                                                                                                                                                      \
    do                                                                                                                                                                                                                                         \
    {                                                                                                                                                                                                                                          \
        if (condition)                                                                                                                                                                                                                         \
        {                                                                                                                                                                                                                                      \
            fprintf(stderr, err_msg);                                                                                                                                                                                                          \
            handler;                                                                                                                                                                                                                           \
        }                                                                                                                                                                                                                                      \
    } while (0);

#define HT_PRIME_1 150
#define HT_PRIME_2 250


typedef struct HashTableItem
{
    char *key;
    char *value;
} HTItem;

typedef struct HT
{
    int size;
    int count;
    HTItem **items;
} HT;

HTItem *ht_item_new(const char *key, const char *value);
HT *ht_new();
void ht_item_del(HTItem *item);
void ht_del(HT *ht);
int ht_hash(const char *s, const int a, const int m);
int ht_hash_get(const char *s, const int num_buckets, const int attempt);


void ht_insert(HT* ht, const char* key, const char* value);
char* ht_search(HT* ht, const char* key);
void ht_delete(HT* ht, const char* key);

#endif // !HASH_TABLE_H

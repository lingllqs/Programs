#include "hash_table.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static HashTableItem HT_DELETED_ITEM = {NULL, NULL};

HashTableItem *ht_item_new(const char *key, const char *value)
{
    HashTableItem *item = malloc(sizeof(HashTableItem));
    ERRP(item == NULL, "malloc item error", goto ERR1);

    item->key = strdup(key);
    item->value = strdup(value);

    return item;

ERR1:
    return NULL;
}

HashTable *ht_new()
{
    HashTable *ht_table = malloc(sizeof(HashTable));
    ERRP(ht_table == NULL, "malloc ht_table", goto ERR1);

    ht_table->size = 53;
    ht_table->count = 0;
    ht_table->items = calloc(sizeof(HashTableItem *), ht_table->size);
    ERRP(ht_table->items == NULL, "malloc ht_table->items error", goto ERR2);

    return ht_table;

ERR2:
    free(ht_table);

ERR1:
    return NULL;
}

void ht_item_del(HashTableItem *item)
{
    if (item)
    {
        free(item->key);
        free(item->value);
        free(item);
    }
}

void ht_del(HashTable *ht)
{
    for (int i = 0; i < ht->size; ++i)
    {
        HashTableItem *ptr = ht->items[i];
        if (ptr)
        {
            ht_item_del(ptr);
        }
    }
    free(ht->items);
    free(ht);
}

int ht_hash(const char *s, const int a, const int m)
{
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++)
    {
        hash += (long)pow(a, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }

    return (int)hash;
}

int ht_hash_get(const char *s, const int num_buckets, const int attempt)
{
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(HashTable *ht, const char *key, const char *value)
{
    HashTableItem *item = ht_item_new(key, value);
    int index = ht_hash_get(item->key, ht->size, 0);
    HashTableItem *cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL)
    {
        if (cur_item != &HT_DELETED_ITEM)
        {
            if (strcmp(cur_item->key, key) == 0)
            {
                ht_item_del(cur_item);
                ht->items[index] = item;
                return;
            }
        }
        index = ht_hash_get(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

char *ht_search(HashTable *ht, const char *key)
{
    int index = ht_hash_get(key, ht->size, 0);
    HashTableItem *item = ht->items[index];
    int i = 1;
    while (item != NULL)
    {
        if (item != &HT_DELETED_ITEM)
        {
            if (strcmp(item->key, key) == 0)
            {
                return item->value;
            }
        }
        index = ht_hash_get(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

void ht_delete(HashTable *ht, const char *key)
{
    int index = ht_hash_get(key, ht->size, 0);
    HashTableItem *item = ht->items[index];
    int i = 1;
    while (item != NULL)
    {
        if (item != &HT_DELETED_ITEM)
        {
            if (strcmp(item->key, key) == 0)
            {
                ht_item_del(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_hash_get(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}

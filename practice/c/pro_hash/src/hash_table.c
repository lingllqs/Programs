#include "hash_table.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static HTItem HT_DELETED_ITEM = {NULL, NULL};

HTItem *ht_item_new(const char *key, const char *value)
{
    HTItem *item = malloc(sizeof(HTItem));
    ERRP(item == NULL, "malloc item error", goto ERR1);

    item->key = strdup(key);
    item->value = strdup(value);

    return item;

ERR1:
    return NULL;
}

HT *ht_new()
{
    HT *ht_table = malloc(sizeof(HT));
    ERRP(ht_table == NULL, "malloc ht_table", goto ERR1);

    ht_table->size = 53;
    ht_table->count = 0;
    ht_table->items = calloc(sizeof(HTItem *), ht_table->size);
    ERRP(ht_table->items == NULL, "malloc ht_table->items error", goto ERR2);

    return ht_table;

ERR2:
    free(ht_table);

ERR1:
    return NULL;
}

void ht_item_del(HTItem *item)
{
    if (item)
    {
        free(item->key);
        free(item->value);
        free(item);
    }
}

void ht_del(HT *ht)
{
    for (int i = 0; i < ht->size; ++i)
    {
        HTItem *ptr = ht->items[i];
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

void ht_insert(HT *ht, const char *key, const char *value)
{
    HTItem *item = ht_item_new(key, value);
    int index = ht_hash_get(item->key, ht->size, 0);
    HTItem *cur_item = ht->items[index];
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

char *ht_search(HT *ht, const char *key)
{
    int index = ht_hash_get(key, ht->size, 0);
    HTItem *item = ht->items[index];
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

void ht_delete(HT *ht, const char *key)
{
    int index = ht_hash_get(key, ht->size, 0);
    HTItem *item = ht->items[index];
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

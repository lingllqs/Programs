#include "../src/hash_table.h"

int main()
{
    HT *hash_table = ht_new();
    ht_del(hash_table);

    return 0;
}

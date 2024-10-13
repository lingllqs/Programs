#include "../src/hash_table.h"
#include <stdio.h>


int main()
{
    int hash_num = ht_hash("Rust", 150, 53);
    printf("%d\n", hash_num);
}

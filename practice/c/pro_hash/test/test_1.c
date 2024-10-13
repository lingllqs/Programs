#include "../src/hash_table.h"

int main()
{
    ERRP(3 > 5, "error test", goto ERR1);
    printf("success\n");

    return 0;
ERR1:
    return 1;
}

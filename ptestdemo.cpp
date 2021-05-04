#include "ptest.h"

int main()
{
    int tmp;
    while (scanf("%x", &tmp) != EOF)
    {

        B_int test = tmp;
        printf("%d\n", PrimalityTest(test, 3));
    }
    return 0;
}
#include "mathLibrary.h"

void sortMinMax(int * value1, int * value2)
{
    int tmp;
    if (*value1 > *value2)
    {
        tmp = *value1;
        *value1 = *value2;
        *value2 = tmp;
    }
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

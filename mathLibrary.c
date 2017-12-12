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

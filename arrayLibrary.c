#include "arrayLibrary.h"

int maxInArray(int * array, int size)
{
    int i, max = array[0];
    for (i = 1 ; i < size ; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

int cellsWithValueInArray(int * array, int size, int value)
{
    int i, count = 0;
    for (i = 0 ; i < size ; i++)
        if (array[i] == value)
            count++;
    return count;
}

int valueExistsInArray(int * array, int size, int value)
{
    int i = 0;
    while (i < size)
    {
        if (array[i] == value)
            return 1;
        i++;
    }
    return 0;
}

int countUniqueValuesInArray(int * array, int size)
{
    int i, counter = 0, max = maxInArray(array, size);
    for (i = 0 ; i <= max ; i++)
        counter += valueExistsInArray(array, size, i);
    return counter;
}

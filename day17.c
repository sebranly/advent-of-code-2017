#include "day17.h"

SolutionIntegers getSolutionDay17(const char * inputFilePath)
{
    SolutionIntegers solution;
    int input = readUniqueNumber(inputFilePath), i, size, currentIndex = 1, numberAfterZero = 1;
    int array[LIMIT_VALUE_DAY_17_PART_1 + 1] = {0};
    array[0] = 0;
    array[1] = 1;
    for (size = 2 ; size <= LIMIT_VALUE_DAY_17_PART_1 ; size++)
    {
        currentIndex = (currentIndex + input) % size + 1;
        for (i = size + 1 ; i >= currentIndex + 1 ; i--)
            array[i] = array[i - 1];
        array[currentIndex] = size;
    }

    for (i = 0 ; i <= LIMIT_VALUE_DAY_17_PART_1 ; i++)
    {
        if (array[i] == LIMIT_VALUE_DAY_17_PART_1)
        {
            if (i != LIMIT_VALUE_DAY_17_PART_1)
                solution.solutionPart1 = array[i + 1];
            else
                solution.solutionPart1 = -1;
            break;
        }
    }

    array[0] = 0;
    array[1] = 1;
    currentIndex = 1;
    for (size = 2 ; size <= LIMIT_VALUE_DAY_17_PART_2 ; size++)
    {
        currentIndex = (currentIndex + input) % size + 1;
        if (currentIndex == 1)
            numberAfterZero = size;
    }
    solution.solutionPart2 = numberAfterZero;

    return solution;
}

#include "../header/day06.h"

SolutionIntegers getSolutionDay06(const char * inputFilePath)
{
    SolutionIntegers solution;
    int records[ARBITRARY_NUMBER_OF_RECORDS][ARBITRARY_NUMBER_OF_ELEMENTS_PER_RECORD];
    int currentNumber = 0, currentIndex = 0, size, numberOfSteps, i, number;
    int input[ARBITRARY_ARRAY_LIMIT] = {0};
    char currentChar;
    int keepReading = 1, solutionIsFound = 0;

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isADigit(currentChar))
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else {
                if (currentChar == EOF || currentChar == '\n')
                    keepReading = 0;
                else if (currentChar != '\t')
                {
                    printf("An unexpected error occurred while reading the input file with name %s\n", inputFilePath);
                    exit(EXIT_FAILURE);
                }
                input[currentIndex] = currentNumber;
                currentNumber = 0;
                currentIndex++;
            }
        }
        size = currentIndex;
        numberOfSteps = 0;
        copyFirstCells(input, records[0], size);
        solutionIsFound = 0;
        while (!solutionIsFound)
        {
            currentIndex = minIndexOfMaxValue(input, size);
            currentNumber = input[currentIndex];
            if (currentNumber == 0)
            {
                printf("The input max value is 0 so there is nothing to distribute");
                exit(EXIT_FAILURE);
            }
            input[currentIndex] = 0;
            while (currentNumber > 0)
            {
                currentIndex = (currentIndex + 1) % size;
                input[currentIndex] += 1;
                currentNumber--;
            }
            numberOfSteps++;
            for (i = 0 ; i < numberOfSteps && !solutionIsFound ; i++)
            {
                if (!differentArrays(input, records[i], size))
                {
                    number = i;
                    solutionIsFound = 1;
                }
            }
            copyFirstCells(input, records[numberOfSteps], size);
        }

        solution.solutionPart1 = numberOfSteps;
        solution.solutionPart2 = numberOfSteps - number;
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

int minIndexOfMaxValue(int array[], int size)
{
    int associatedMinIndex = size - 1;
    int i, maxValue = array[associatedMinIndex];
    for (i = associatedMinIndex - 1 ; i >= 0 ; i--)
    {
        if (array[i] >= maxValue)
        {
            maxValue = array[i];
            associatedMinIndex = i;
        }
    }
    return associatedMinIndex;
}

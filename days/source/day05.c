#include "../header/day05.h"

SolutionIntegers getSolutionDay05(const char * inputFilePath)
{
    SolutionIntegers solution;

    int sign = 1, size = 0, currentNumber = 0, part, currentIndex, numberOfSteps;
    int keepReading = 1;
    int input[ARBITRARY_ARRAY_LIMIT] = {0};
    int input2[ARBITRARY_ARRAY_LIMIT] = {0};
    char currentChar;

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        fillAllCells(input, ARBITRARY_ARRAY_LIMIT, 0);
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isADigit(currentChar))
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else if (currentChar == '-')
                sign = -1;
            else if (currentChar == '\n' || currentChar == EOF)
            {
                input[size] = sign * currentNumber;
                size++;
                if (size >= ARBITRARY_ARRAY_LIMIT)
                {
                    printf("An error occurred while reading the input file with name %s because of memory limitation in the program\n", inputFilePath);
                    exit(EXIT_FAILURE);
                }
                sign = 1;
                currentNumber = 0;
                if (currentChar == EOF)
                    keepReading = 0;
            }
            else
            {
                printf("An unexpected error occurred while reading the input file with name %s because of an unexpected character\n", inputFilePath);
                exit(EXIT_FAILURE);
            }
        }
        copyFirstCells(input, input2, size);

        for (part = 1 ; part <= 2 ; part++)
        {
            if (part == 2)
                copyFirstCells(input2, input, size);
            currentIndex = 0;
            numberOfSteps = 0;
            while (currentIndex >= 0 && currentIndex < size)
            {
                currentNumber = input[currentIndex];
                if (part == 2 && currentNumber >= 3)
                    input[currentIndex]--;
                else
                    input[currentIndex]++;
                currentIndex += currentNumber;
                numberOfSteps++;
            }
            if (part == 1)
                solution.solutionPart1 = numberOfSteps;
            else
                solution.solutionPart2 = numberOfSteps;
        }
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

void copyFirstCells(int sourceArray[], int destinationArray[], int numberOfCellsToBeCopied)
{
    int i = 0;
    for (i = 0 ; i < numberOfCellsToBeCopied ; i++)
        destinationArray[i] = sourceArray[i];
}

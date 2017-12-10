#include <stdio.h>
#include <stdlib.h>
#include "solutionTypes.h"
#include "day01.h"

SolutionIntegers getSolutionDay01(const char * inputFilePath)
{
    SolutionIntegers solution;
    int keepReading = 1;
    char currentChar;
    int i = 0, halfInputLength = 0, inputLength = 0, comparisonIndex = 0, sum = 0;
    int firstDigit = UNSET, currentDigit = UNSET, previousDigit = UNSET;
    int input[ARBITRARY_ARRAY_LIMIT] = {0};
    FILE* file = NULL;

    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isADigit(currentChar))
            {
                currentDigit = toInteger(currentChar);

                input[inputLength] = currentDigit;
                inputLength++;

                if (firstDigit == UNSET)
                    firstDigit = currentDigit;
                else if (currentDigit == previousDigit)
                    sum += previousDigit;

                previousDigit = currentDigit;
            }
            else
                keepReading = 0;
        }

        if (previousDigit == firstDigit)
            sum += previousDigit;

        solution.solutionPart1 = sum;

        sum = 0;
        halfInputLength = inputLength / 2;
        for (i = 0 ; i < inputLength ; i++)
        {
            if (i < halfInputLength)
                comparisonIndex = i + halfInputLength;
            else
                comparisonIndex = i - halfInputLength;

            if (input[comparisonIndex] == input[i])
                sum += input[i];
        }
        solution.solutionPart2 = sum;

        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

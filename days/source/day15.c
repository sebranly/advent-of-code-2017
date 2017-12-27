#include "../header/day15.h"

SolutionIntegers getSolutionDay15(const char * inputFilePath)
{
    SolutionIntegers solution;
    int keepReading = 1;
    char currentChar;
    int n1 = -1, n2, iteration = 0, sum = 0, currentNumber = 0;
    unsigned long long number1 = 65, number2 = 8921;
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
            else if (currentChar == '\n' && n1 == -1)
            {
                n1 = currentNumber;
                currentNumber = 0;
            }
            else if (currentChar == '\n' || currentChar == EOF)
            {
                n2 = currentNumber;
                keepReading = 0;
            }
        }

        printf("Please wait a bit... (some seconds)\n");

        number1 = n1;
        number2 = n2;
        for (iteration = 0 ; iteration < NUMBER_OF_ITERATIONS_PART_1 ; iteration++)
        {
            number1 = getNextGeneratorValue(number1, 1, 1);
            number2 = getNextGeneratorValue(number2, 2, 1);
            sum += (number1 & 0xFFFF) == (number2 & 0xFFFF);
        }
        solution.solutionPart1 = sum;

        sum = 0;
        number1 = n1;
        number2 = n2;
        for (iteration = 0 ; iteration < NUMBER_OF_ITERATIONS_PART_2 ; iteration++)
        {
            number1 = getNextGeneratorValue(number1, 1, 2);
            number2 = getNextGeneratorValue(number2, 2, 2);
            sum += (number1 & 0xFFFF) == (number2 & 0xFFFF);
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

unsigned long long getNextGeneratorValue(unsigned long long number, int generatorNumber, int partNumber)
{
    do {
        if (generatorNumber == 1)
            number = (number * 16807) % 2147483647;
        else
            number = (number * 48271) % 2147483647;
    } while (partNumber == 2 && ((generatorNumber == 1 && number % 4 != 0) || (generatorNumber == 2 && number % 8 != 0)));

    return number;
}

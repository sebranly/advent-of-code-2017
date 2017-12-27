#include "../header/day10.h"

SolutionIntegerString getSolutionDay10(const char * inputFilePath)
{
    SolutionIntegerString solution;
    int keepReading = 1;
    int currentNumber = 0, currentCharIndex = 0;
    char currentChar;
    char input[LONG_STRING_LENGTH];
    KnotHashElements knotHashElements;
    FILE* file = NULL;

    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        initializeKnotHashElements(&knotHashElements);
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (currentChar == '\n' || currentChar == EOF)
                input[currentCharIndex] = '\0';
            else
            {
                input[currentCharIndex] = currentChar;
                currentCharIndex++;
            }

            if (isADigit(currentChar))
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else if (currentChar == ',' || currentChar == '\n' || currentChar == EOF)
            {
                operateArrayChangesBasedOnNumber(currentNumber, &knotHashElements);

                currentNumber = 0;
                if (currentChar == '\n' || currentChar == EOF)
                    keepReading = 0;
            }
        }
        solution.solutionPart1 = knotHashElements.array[0] * knotHashElements.array[1];

        determineFinalKnotHashString(input, &knotHashElements);
        strcpy(solution.solutionPart2, knotHashElements.finalKnotHash);

        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

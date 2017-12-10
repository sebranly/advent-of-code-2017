#include "day09.h"

SolutionIntegers getSolutionDay09(const char * inputFilePath)
{
    SolutionIntegers solution;
    solution.solutionPart1 = 0;
    solution.solutionPart2 = 0;
    int keepReading = 1, nestedLevel = 1, inGarbage = 0, cancelNextCharacter = 0;
    char currentChar;
    FILE* file = NULL;

    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (cancelNextCharacter)
                cancelNextCharacter = 0;
            else if (currentChar == '!')
                cancelNextCharacter = 1;
            else if (currentChar == '{' && !inGarbage)
                solution.solutionPart1 += nestedLevel++;
            else if (currentChar == '}' && !inGarbage)
                nestedLevel--;
            else if (currentChar == '<' && !inGarbage)
                inGarbage = 1;
            else if (currentChar == '>' && inGarbage)
                inGarbage = 0;
            else if (currentChar == '\n' || currentChar == EOF)
                keepReading = 0;
            else if (inGarbage)
                (solution.solutionPart2)++;
        }

        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

#include "../header/day11.h"

SolutionIntegers getSolutionDay11(const char * inputFilePath)
{
    SolutionIntegers solution;
    int keepReading = 1;
    int currentCharIndex = 0, maxStepsFromCenter = 0, numberOfStepsFromCenter;
    char currentChar;
    char direction[STRING_LIMITED_LENGTH];
    int steps[NUMBER_OF_HEX_AXES] = {0};
    FILE* file = NULL;

    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isALowerCaseLetter(currentChar))
            {
                direction[currentCharIndex] = currentChar;
                currentCharIndex++;
            }
            else if (currentChar == ',' || currentChar == '\n' || currentChar == EOF)
            {
                direction[currentCharIndex] = '\0';
                currentCharIndex = 0;

                addSteps(direction, steps);
                minimizeSteps(steps);

                numberOfStepsFromCenter = abs(steps[HEX_NORTH] + steps[HEX_NORTH_EAST] + steps[HEX_SOUTH_EAST]);
                if (numberOfStepsFromCenter > maxStepsFromCenter)
                    maxStepsFromCenter = numberOfStepsFromCenter;

                if (currentChar == '\n' || currentChar == EOF)
                    keepReading = 0;
            }
        }

        solution.solutionPart1 = numberOfStepsFromCenter;
        solution.solutionPart2 = maxStepsFromCenter;

        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

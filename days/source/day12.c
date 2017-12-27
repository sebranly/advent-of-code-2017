#include "../header/day12.h"

SolutionIntegers getSolutionDay12(const char * inputFilePath)
{
    SolutionIntegers solution;
    int keepReading = 1, stillOnLeftPart = 1;
    char currentChar;
    int i, currentNumber = 0, fileLine = 0, currentGroupId, otherGroupId;
    int* groups = NULL;

    int numberOfCorrectLines = numberOfNonEmptyLines(inputFilePath);
    if (numberOfCorrectLines < 1)
    {
        printf("The file with name %s does not even have one correct line (non empty)", inputFilePath);
        exit(EXIT_FAILURE);
    }
    groups = malloc(numberOfCorrectLines * sizeof(int));
    if (groups == NULL)
    {
        printf("An error occurred because of limited memory\n");
        exit(EXIT_FAILURE);
    }

    // groups array contains ID of groups, 0 means no group was found for the number i yet
    for (i = 0 ; i < numberOfCorrectLines ; i++)
        groups[i] = 0;

    FILE* file = NULL;

    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isADigit(currentChar) && !stillOnLeftPart)
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else if (currentChar == '>')
                stillOnLeftPart = 0;
            else if (currentChar == ',' || currentChar == '\n' || currentChar == EOF)
            {
                if (groups[fileLine] == 0)
                {
                    currentGroupId = maxInArray(groups, numberOfCorrectLines) + 1;
                    groups[fileLine] = currentGroupId;
                }
                else
                    currentGroupId = groups[fileLine];

                if (groups[currentNumber] == 0)
                    groups[currentNumber] = currentGroupId;
                else if (groups[currentNumber] != groups[fileLine])
                {
                    otherGroupId = groups[currentNumber];
                    sortMinMax(&currentGroupId, &otherGroupId);
                    for (i = 0 ; i < numberOfCorrectLines ; i++)
                        if (groups[i] == otherGroupId)
                            groups[i] = currentGroupId;
                }

                currentNumber = 0;
                if (currentChar == '\n')
                {
                    fileLine++;
                    stillOnLeftPart = 1;
                }
                if (currentChar == EOF)
                    keepReading = 0;
            }
        }

        solution.solutionPart1 = cellsWithValueInArray(groups, numberOfCorrectLines, 1);
        solution.solutionPart2 = countUniqueValuesInArray(groups, numberOfCorrectLines);

        free(groups);
        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

#include "../header/day02.h"

SolutionIntegers getSolutionDay02(const char * inputFilePath)
{
    SolutionIntegers solution;

    int x = 0, y = 0, currentNumber = 0, i, i2, j, min, max, sum;
    int keepReading = 1, skipLine = 0;
    char currentChar;

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    int inputIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT];

    if (file != NULL)
    {
        fillAllCellsIn2D(inputIn2D, UNSET);
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isADigit(currentChar))
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else {
                inputIn2D[x][y] = currentNumber;
                currentNumber = 0;
                if (currentChar == '\t')
                    x++;
                else if (currentChar == '\n')
                {
                    x = 0;
                    y++;
                }
                else if (currentChar == EOF)
                    keepReading = 0;
                else
                {
                    printf("An unexpected error occurred while reading the input file with name %s because of an unexpected character\n", inputFilePath);
                    exit(EXIT_FAILURE);
                }
            }
        }

        sum = 0;
        i = 0;
        j = 0;
        while (inputIn2D[i][j] != UNSET)
        {
            while (inputIn2D[i][j] != UNSET)
            {
                if (min == UNSET || inputIn2D[i][j] < min)
                    min = inputIn2D[i][j];
                if (max == UNSET || inputIn2D[i][j] > max)
                    max = inputIn2D[i][j];
                i++;
            }
            sum += max - min;
            min = UNSET;
            max = UNSET;
            i = 0;
            j++;
        }
        solution.solutionPart1 = sum;

        sum = 0;
        i = 0;
        i2 = 0;
        j = 0;
        skipLine = 0;
        while (inputIn2D[i][j] != UNSET)
        {
            while (inputIn2D[i][j] != UNSET && !skipLine)
            {
                i2 = 0;
                while (inputIn2D[i2][j] != UNSET && !skipLine)
                {
                   if (i != i2 && inputIn2D[i][j] >= inputIn2D[i2][j] && inputIn2D[i][j] % inputIn2D[i2][j] == 0)
                   {
                       sum += inputIn2D[i][j] / inputIn2D[i2][j];
                       skipLine = 1;
                   }
                   i2++;
                }
                i++;
            }
            skipLine = 0;
            i = 0;
            j++;
        }
        solution.solutionPart2 = sum;
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

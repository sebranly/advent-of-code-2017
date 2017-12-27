#include "../header/day03.h"

SolutionIntegers getSolutionDay03(const char * inputFilePath)
{
    SolutionIntegers solution;

    int i, x, y, uniqueInputNumber = 0, numberOfSteps = UNSET, min, max, pivotNumber = 0, number = 0, numberOfRing = 0, heightPerRing = UNSET;
    int currentDirection = UNSET, beforeResetForDirection = UNSET;
    int corners[NUMBER_OF_CARDINAL_DIRECTIONS];
    for (i = 0 ; i < NUMBER_OF_CARDINAL_DIRECTIONS ; i++)
        corners[i] = UNSET;
    int keepReading = 1, outOfArrayRange = 0;
    char currentChar;
    int inputIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT];

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isADigit(currentChar))
            {
                uniqueInputNumber *= 10;
                uniqueInputNumber += toInteger(currentChar);
            }
            else if (currentChar == EOF || currentChar == '\n')
                keepReading = 0;
            else
            {
                printf("An unexpected error occurred while reading the input file with name %s because of an unexpected character\n", inputFilePath);
                exit(EXIT_FAILURE);
            }
        }
        if (uniqueInputNumber <= 0)
        {
            printf("The number for the memory has to be strictly greater than 0, the one found in the input file is %d so it is impossible to proceed", uniqueInputNumber);
            exit(EXIT_FAILURE);
        }

        numberOfSteps = UNSET;
        if (uniqueInputNumber == 1)
        {
            numberOfSteps = 0;
        }
        else
        {
            do
            {
                /* Every time we go from a ring to an upper ring, the height has two more cells in height
                Ring #1 is the one right after the ring #0 (that only has cell 1) */
                min = (numberOfRing == 0) ? 2 : min + numberOfRing * 8;
                heightPerRing = (numberOfRing == 0) ? 3 : heightPerRing + 2;
                numberOfRing++;
                // Formula to know the max cell of the current ring being analyzed
                max = min + (heightPerRing - 1) * 4 - 1;
            } while (uniqueInputNumber < min || uniqueInputNumber > max);

            corners[SOUTH_EAST] = max;
            corners[SOUTH_WEST] = max - (heightPerRing - 1);
            corners[NORTH_WEST] = max - 2 * (heightPerRing - 1);
            corners[NORTH_EAST] = max - 3 * (heightPerRing - 1);

            for (i = 0 ; i < NUMBER_OF_CARDINAL_DIRECTIONS ; i++)
                if (uniqueInputNumber == corners[i])
                    numberOfSteps = (heightPerRing / 2) * 2;

            if (numberOfSteps == UNSET)
            {
                if (corners[SOUTH_EAST] > uniqueInputNumber && uniqueInputNumber > corners[SOUTH_WEST])
                {
                    min = corners[SOUTH_WEST];
                }
                else if (corners[SOUTH_WEST] > uniqueInputNumber && uniqueInputNumber > corners[NORTH_WEST])
                {
                    min = corners[NORTH_WEST];
                }
                else if (corners[NORTH_WEST] > uniqueInputNumber && uniqueInputNumber > corners[NORTH_EAST])
                {
                    min = corners[NORTH_EAST];
                }
                else
                {
                    // Compared to the ring min, we decrease the value and suppose it appears on the bottom right hand corner for our algorithm instead of the ring max value
                    min -= 1;
                }
                pivotNumber = (2 * min + heightPerRing - 1) / 2;
                numberOfSteps = (heightPerRing / 2) * 2;
                number = min;

                do
                {
                    number++;
                    numberOfSteps = (number <= pivotNumber) ? numberOfSteps - 1 : numberOfSteps + 1;
                } while (number != uniqueInputNumber);
            }
        }

        solution.solutionPart1 = numberOfSteps;

        // Zero is a good choice (rather than UNSET) because we explicitly use the neutral number in the operation addition
        fillAllCellsIn2D(inputIn2D, 0);
        x = ARBITRARY_2D_ARRAY_LIMIT / 2;
        y = ARBITRARY_2D_ARRAY_LIMIT / 2;
        number = 1;
        inputIn2D[x][y] = number;
        x++;
        inputIn2D[x][y] = 1;
        max = 1;
        currentDirection = NORTH;
        heightPerRing = 3;
        beforeResetForDirection = 1;
        outOfArrayRange = 0;

        do
        {
            beforeResetForDirection--;
            moveOneStep(&x, &y, currentDirection);
            if (!valueIsBetween(x, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) || !valueIsBetween(y, 0, ARBITRARY_2D_ARRAY_LIMIT - 1))
                outOfArrayRange = 1;
            else
            {
                number = sumOfAdjacentCells(inputIn2D, x, y);
                if (number > max)
                    max = number;
                inputIn2D[x][y] = number;
                if (beforeResetForDirection == 0)
                {
                    if (currentDirection == SOUTH || currentDirection == EAST)
                        beforeResetForDirection = heightPerRing;
                    else
                        beforeResetForDirection = heightPerRing - 1;
                    currentDirection = nextSpiralDirection(currentDirection);
                    if (currentDirection == NORTH)
                        heightPerRing += 2;
                }
            }
        } while (max < uniqueInputNumber && !outOfArrayRange);

        if (outOfArrayRange)
        {
            printf("We could not find any solution with your input because of memory limitation in the program\n");
            exit(EXIT_FAILURE);
        }
        solution.solutionPart2 = max;
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

int nextSpiralDirection(int currentDirection)
{
    switch (currentDirection)
    {
        case NORTH:
            return WEST;
            break;
        case WEST:
            return SOUTH;
            break;
        case SOUTH:
            return EAST;
            break;
        case EAST:
        default:
            return NORTH;
            break;
    }
}

void moveOneStep(int * x, int * y, int currentDirection)
{
    switch (currentDirection)
    {
        case NORTH:
            (*y)--;
            break;
        case WEST:
            (*x)--;
            break;
        case SOUTH:
            (*y)++;
            break;
        case EAST:
        default:
            (*x)++;
            break;
    }
}

int sumOfAdjacentCells(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int x, int y)
{
    int sum = 0, i = 0, j = 0;
    for (i = x - 1 ; i <= x + 1 ; i++)
        for (j = y - 1 ; j <= y + 1 ; j++)
            if (i != x || j != y)
                if (valueIsBetween(i, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) && valueIsBetween(j, 0, ARBITRARY_2D_ARRAY_LIMIT - 1))
                    sum += arrayIn2D[i][j];
    return sum;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57

#define LATEST_AVAILABLE_CHALLENGE 3
#define MAX_CHALLENGE 25

#define UNSET -1
#define EXIT_VALUE -1

#define ARBITRARY_ARRAY_LIMIT 3000
// The following value is a limit per dimension
#define ARBITRARY_2D_ARRAY_LIMIT 100
#define MAX_FILE_NAME_LENGTH 50

#define NUMBER_OF_CARDINAL_DIRECTIONS 4

enum { NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST };
enum { NORTH, SOUTH, WEST, EAST };

int isADigit(char c);
int toInteger(char digit);
int nextSpiralDirection(int currentDirection);
int valueIsBetween(int value, int min, int max);
void moveOneStep(int * x, int * y, int currentDirection);
void fillAllCells(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int value);
int sumOfAdjacentCells(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int x, int y);
void printCellsArrayIn2D(const int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int minX, int maxX, int minY, int maxY);

int main()
{
    FILE* file = NULL;
    char currentChar = 0, c;
    char fileName[MAX_FILE_NAME_LENGTH];
    int previousDigit = UNSET;
    int currentDigit = UNSET;
    int firstDigit = UNSET;
    int i = 0, i2 = 0, j = 0, x = 0, y = 0, uniqueInputNumber = 0, number = 0, pivotNumber = 0, min = UNSET, max = UNSET, sum = 0, numberOfRing = 0, heightPerRing = UNSET, numberOfSteps = UNSET, currentNumber = 0, comparisonIndex = 0, inputLength = 0, halfInputLength = 0, dayOfChallenge = 0, result = 0;
    int beforeResetForDirection = UNSET, currentDirection = UNSET;
    // The following variables are used as booleans only
    int keepReading = 1, outOfArrayRange = 0, incorrectDayOfChallenge = 1, skipLine = 0;
    int input[ARBITRARY_ARRAY_LIMIT] = {0};
    int corners[NUMBER_OF_CARDINAL_DIRECTIONS];
    for (i = 0 ; i < NUMBER_OF_CARDINAL_DIRECTIONS ; i++)
        corners[i] = UNSET;
    int inputIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT];
    fillAllCells(inputIn2D, UNSET);

    do
    {
        printf("Which daily challenge do you want to access? (from 1 to %d)\nType %d to exit.\nYour choice: ", LATEST_AVAILABLE_CHALLENGE, EXIT_VALUE);
        scanf("%d", &dayOfChallenge);

        if (dayOfChallenge == EXIT_VALUE)
        {
            printf("Goodbye!\n");
            return EXIT_SUCCESS;
        }
        else if (dayOfChallenge == 0 || dayOfChallenge > MAX_CHALLENGE)
        {
            printf("The input you typed is incorrect\n");
            // We flush the buffer in case something else than two digits was typed (because of \n behaviour)
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        else if (dayOfChallenge > LATEST_AVAILABLE_CHALLENGE && dayOfChallenge <= MAX_CHALLENGE)
        {
            printf("Challenge #%d is not accessible yet\n", dayOfChallenge);
        }
        else {
            incorrectDayOfChallenge = 0;
        }
    } while (incorrectDayOfChallenge);

    printf("\nCHALLENGE OF DAY %02d\n===================\n", dayOfChallenge);

    result = sprintf(fileName, "inputDay%02d.txt", dayOfChallenge);
    if (result < 0)
    {
        printf("An unexpected error occurred before reading the input file");
    }
    file = fopen(fileName, "r");

    if (file != NULL)
    {
        switch (dayOfChallenge)
        {
            case 1:
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (isADigit(currentChar))
                {
                    currentDigit = toInteger(currentChar);

                    input[inputLength] = currentDigit;
                    inputLength++;

                    if (firstDigit == UNSET)
                    {
                        firstDigit = currentDigit;
                    }
                    else if (currentDigit == previousDigit) {
                        sum += previousDigit;
                    }

                    previousDigit = currentDigit;
                }
                else
                {
                    keepReading = 0;
                }
            }

            if (previousDigit == firstDigit)
            {
                sum += previousDigit;
            }

            printf("Part 1 - Sum for the input is: %d\n", sum);

            sum = 0;
            halfInputLength = inputLength / 2;
            for (i = 0 ; i < inputLength ; i++)
            {
                if (i < halfInputLength)
                    comparisonIndex = i + halfInputLength;
                else {
                    comparisonIndex = i - halfInputLength;
                }

                if (input[comparisonIndex] == input[i])
                    sum += input[i];
            }
            printf("Part 2 - Sum for the input is: %d\n", sum);
            break;

            case 2:
            fillAllCells(inputIn2D, UNSET);
            x = 0;
            y = 0;
            currentNumber = 0;
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
                        printf("An unexpected error occurred while reading the input file with name %s\n", fileName);
                        return EXIT_FAILURE;
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
            printf("Part 1 - Checksum for the input is: %d\n", sum);

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
            printf("Part 2 - Checksum for the input is: %d\n", sum);
            break;

            case 3:
            uniqueInputNumber = 0;
            keepReading = 1;
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (isADigit(currentChar))
                {
                    uniqueInputNumber *= 10;
                    uniqueInputNumber += toInteger(currentChar);
                }
                else if (currentChar == EOF)
                {
                    keepReading = 0;
                }
                else
                {
                    printf("An unexpected error occurred while reading the input file with name %s\n", fileName);
                    return EXIT_FAILURE;
                }
            }
            if (uniqueInputNumber <= 0)
            {
                printf("The number for the memory has to be strictly greater than 0, the one found in the input file is %d so it is impossible to proceed", uniqueInputNumber);
                return EXIT_FAILURE;
            }
            printf("Going to access memory in number %d based on Manhattan Distance...\n", uniqueInputNumber);

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
                printf("Your cell has been identified on ring %d of memory cells that is ranging from %d to %d included\n", numberOfRing, min, max);

                corners[SOUTH_EAST] = max;
                corners[SOUTH_WEST] = max - (heightPerRing - 1);
                corners[NORTH_WEST] = max - 2 * (heightPerRing - 1);
                corners[NORTH_EAST] = max - 3 * (heightPerRing - 1);
                printf("Numbers for the corners of this ring are NE: %d ; NW: %d ; SW: %d ; SE: %d\n", corners[NORTH_EAST], corners[NORTH_WEST], corners[SOUTH_WEST], corners[SOUTH_EAST]);

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

            printf("Part 1 - %d step(s) is/are required to go from number %d to number 1 in the memory\n", numberOfSteps, uniqueInputNumber);

            // Zero is a good choice (rather than UNSET) because we explicitly use the neutral number in the operation addition
            fillAllCells(inputIn2D, 0);
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
                printf("We could not find any solution with your input because of memory limitation in the program\n");
            else
            {
                printCellsArrayIn2D(inputIn2D, ARBITRARY_2D_ARRAY_LIMIT/2 - 3, ARBITRARY_2D_ARRAY_LIMIT/2 + 3, ARBITRARY_2D_ARRAY_LIMIT/2 - 3, ARBITRARY_2D_ARRAY_LIMIT/2 + 3);
                printf("Part 2 - the first value written that is larger than your puzzle input is %d\n", max);
            }
            break;

            default:
            break;
        }
        fclose(file);
    }
    else
    {
        printf("No file found with name %s", fileName);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int isADigit(char c)
{
    return (c >= ZERO_ASCII_CODE && c <= NINE_ASCII_CODE);
}

int toInteger(char digit)
{
    return digit - ZERO_ASCII_CODE;
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

void fillAllCells(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int value)
{
    int i, j;
    for (i = 0 ; i < ARBITRARY_2D_ARRAY_LIMIT ; i++)
        for (j = 0 ; j < ARBITRARY_2D_ARRAY_LIMIT ; j++)
            arrayIn2D[i][j] = value;
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

int valueIsBetween(int value, int min, int max)
{
    return (min <= value && value <= max);
}

void printCellsArrayIn2D(const int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int minX, int maxX, int minY, int maxY)
{
    int i, j;
    if (minX > maxX || minY > maxY || !valueIsBetween(minX, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) || !valueIsBetween(maxX, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) || !valueIsBetween(minY, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) || !valueIsBetween(maxY, 0, ARBITRARY_2D_ARRAY_LIMIT - 1))
    {
        printf("We cannot print the portion of the 2D array because the limits are not correct\n");
    }
    else
    {
        printf("Displaying 2D array with X between %d and %d and Y between %d and %d\n", minX, maxX, minY, maxY);
        for (j = minY ; j <= maxY ; j++)
        {
            for (i = minX ; i <= maxX ; i++)
                printf("%d\t", arrayIn2D[i][j]);
            printf("\n");
        }
    }
}

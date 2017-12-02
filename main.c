#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57

#define LATEST_AVAILABLE_CHALLENGE 2
#define MAX_CHALLENGE 25

#define UNSET -1
#define EXIT_VALUE -1

#define ARBITRARY_ARRAY_LIMIT 3000
// The following value is a limit per dimension
#define ARBITRARY_2D_ARRAY_LIMIT 100
#define MAX_FILE_NAME_LENGTH 50

int isADigit(char c);
int toInteger(char digit);

int main()
{
    FILE* file = NULL;
    char currentChar = 0, c;
    char fileName[MAX_FILE_NAME_LENGTH];
    int previousDigit = UNSET;
    int currentDigit = UNSET;
    int firstDigit = UNSET;
    int i = 0, i2 = 0, j = 0, x = 0, y = 0, min = UNSET, max = UNSET, sum = 0, currentNumber = 0, comparisonIndex = 0, inputLength = 0, halfInputLength = 0, dayOfChallenge = 0, result = 0;
    // The following variables are used as booleans only
    int keepReading = 1, incorrectDayOfChallenge = 1, skipLine = 0;
    int input[ARBITRARY_ARRAY_LIMIT] = {0};
    int inputIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT];
    for (i = 0 ; i < ARBITRARY_2D_ARRAY_LIMIT ; i++)
        for (j = 0 ; j < ARBITRARY_2D_ARRAY_LIMIT ; j++)
            inputIn2D[i][j] = UNSET;

    do {
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

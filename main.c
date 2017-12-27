#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "other/header/solutionTypes.h"
#include "other/header/stringLibrary.h"
#include "other/header/allDays.h"

int main()
{
    SolutionIntegers solutionIntegers;
    SolutionStrings solutionStrings;
    SolutionIntegerString solutionIntegerString;
    SolutionStringInteger solutionStringInteger;

    FILE* file = NULL;
    char currentChar = 0, c;
    char fileName[MAX_FILE_NAME_LENGTH];
    int i = 0, i2 = 0, j = 0, x = 0, y = 0, min = UNSET, max = UNSET, sum = 0, currentNumber = 0, dayOfChallenge = 0, result = 0;
    // The following variables are used as booleans only
    int keepReading = 1, incorrectDayOfChallenge = 1, skipLine = 0;
    int inputIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT];
    fillAllCellsIn2D(inputIn2D, UNSET);

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

    result = sprintf(fileName, "days/input/day%02d.txt", dayOfChallenge);
    if (result < 0)
    {
        printf("An unexpected error occurred before reading the input file");
    }
    // TBD: remove it once every day challenge has its own .c file
    file = fopen(fileName, "r");

    if (file != NULL)
    {
        switch (dayOfChallenge)
        {
            case 1:
            solutionIntegers = getSolutionDay01(fileName);
            printf("Part 1 - Sum for the input with next digit is: %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - Sum for the input with halfway around digit is: %d\n", solutionIntegers.solutionPart2);
            break;

            case 2:
            fillAllCellsIn2D(inputIn2D, UNSET);
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
            solutionIntegers = getSolutionDay03(fileName);
            printf("Part 1 - %d step(s) is/are required\n", solutionIntegers.solutionPart1);
            printf("Part 2 - the first value written that is larger than your puzzle input is %d\n", solutionIntegers.solutionPart2);
            break;

            case 4:
            solutionIntegers = getSolutionDay04(fileName);
            printf("Part 1 - there is/are %d valid passphrase(s) in the input file\n", solutionIntegers.solutionPart1);
            printf("Part 2 - there is/are %d valid passphrase(s) in the input file\n", solutionIntegers.solutionPart2);
            break;

            case 5:
            solutionIntegers = getSolutionDay05(fileName);
            printf("Part 1 - %d step(s) was/were needed to get out of the list\n", solutionIntegers.solutionPart1);
            printf("Part 2 - %d step(s) was/were needed to get out of the list\n", solutionIntegers.solutionPart2);
            break;

            case 6:
            solutionIntegers = getSolutionDay06(fileName);
            printf("Part 1 - An infinite loop has been detected after the block redistribution cycle %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - the size of the loop is %d\n", solutionIntegers.solutionPart2);
            break;

            case 7:
            solutionStringInteger = getSolutionDay07(fileName);
            printf("Part 1 - The bottom program is called %s\n", solutionStringInteger.solutionPart1);
            printf("Part 2 - WIP\n");
            break;

            case 8:
            solutionIntegers = getSolutionDay08(fileName);
            printf("Part 1 - the largest value is any register is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - the highest value held in any register during the process was %d\n", solutionIntegers.solutionPart2);
            break;

            case 9:
            solutionIntegers = getSolutionDay09(fileName);
            printf("Part 1 - the total score for all groups is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - the total number of garbage elements is %d\n", solutionIntegers.solutionPart2);
            break;

            case 10:
            solutionIntegerString = getSolutionDay10(fileName);
            printf("Part 1 - first number times second number equals %d\n", solutionIntegerString.solutionPart1);
            printf("Part 2 - final hash is %s", solutionIntegerString.solutionPart2);
            break;

            case 11:
            solutionIntegers = getSolutionDay11(fileName);
            printf("Part 1 - the fewest number of steps required to reach him is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - the furthest he ever got from his starting position is %d\n", solutionIntegers.solutionPart2);
            break;

            case 12:
            solutionIntegers = getSolutionDay12(fileName);
            printf("Part 1 - number of programs in same group than program with ID 0 is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - number of groups is %d\n", solutionIntegers.solutionPart2);
            break;

            case 13:
            solutionIntegers = getSolutionDay13(fileName);
            printf("Part 1 - the severity of the whole trip is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - the fewest number of picoseconds that I need to delay the packet to pass through the firewall without being caught is %d\n", solutionIntegers.solutionPart2);
            break;

            case 14:
            solutionIntegers = getSolutionDay14(fileName);
            printf("Part 1 - %d squares are used\n", solutionIntegers.solutionPart1);
            printf("Part 2 - %d regions are present\n", solutionIntegers.solutionPart2);
            break;

            case 15:
            solutionIntegers = getSolutionDay15(fileName);
            printf("Part 1 - Judge's final count is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - Judge's final count is %d\n", solutionIntegers.solutionPart2);
            break;

            case 16:
            solutionStrings = getSolutionDay16(fileName);
            printf("Part 1 - The programs are in the following order after one dance:\n%s\n", solutionStrings.solutionPart1);
            printf("Part 2 - The programs are in the following order after way more than one dance:\n%s\n", solutionStrings.solutionPart2);
            break;

            case 17:
            solutionIntegers = getSolutionDay17(fileName);
            printf("Part 1 - The value after %d is %d\n", LIMIT_VALUE_DAY_17_PART_1, solutionIntegers.solutionPart1);
            printf("Part 2 - The moment %d is inserted, the value after 0 is %d\n", LIMIT_VALUE_DAY_17_PART_2, solutionIntegers.solutionPart2);
            break;

            case 18:
            solutionIntegers = getSolutionDay18(fileName);
            printf("Part 1 - The first time a rcv instruction is executed with a non-zero value, the value of the recovered frequency is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - Once both programs have terminated, program 1 sent a value %d times\n", solutionIntegers.solutionPart2);
            break;

            case 19:
            solutionStringInteger = getSolutionDay19(fileName);
            printf("Part 1 - The letters were picked in that order: %s\n", solutionStringInteger.solutionPart1);
            printf("Part 2 - There were %d steps\n", solutionStringInteger.solutionPart2);
            break;

            case 20:
            solutionIntegers = getSolutionDay20(fileName);
            printf("Part 1 - The particle that will stay closest to position <0,0,0> in the long term is #%d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - Number of particles that are left after all collisions are resolved: %d\n", solutionIntegers.solutionPart2);
            break;

            case 21:
            solutionIntegers = getSolutionDay21(fileName);
            printf("Part 1 - %d pixels stay on after %d iterations\n", solutionIntegers.solutionPart1, LIMIT_VALUE_DAY_21_PART_1);
            printf("Part 2 - %d pixels stay on after %d iterations\n", solutionIntegers.solutionPart2, LIMIT_VALUE_DAY_21_PART_2);
            break;

            case 22:
            solutionIntegers = getSolutionDay22(fileName);
            printf("Part 1 - After a total of %d bursts of activity, %d bursts will have caused an infection\n", LIMIT_VALUE_DAY_22_PART_1, solutionIntegers.solutionPart1);
            printf("Part 2 - After a total of %d bursts of activity, %d bursts will have caused an infection\n", LIMIT_VALUE_DAY_22_PART_2, solutionIntegers.solutionPart2);
            break;

            case 23:
            solutionIntegers = getSolutionDay23(fileName);
            printf("Part 1 - The mul instruction is invoked %d times\n", solutionIntegers.solutionPart1);
            printf("Part 2 - The value left in h register would be %d\n", solutionIntegers.solutionPart2);
            break;

            case 24:
            solutionIntegers = getSolutionDay24(fileName);
            printf("Part 1 - The strength of the strongest bridge we can make is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - The strength of the longest bridge we can make is %d\n", solutionIntegers.solutionPart2);
            break;

            case 25:
            printf("The diagnostic checksum it produces is %d\n", getSolutionDay25(fileName));
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

void fillAllCellsIn2D(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int value)
{
    int i, j;
    for (i = 0 ; i < ARBITRARY_2D_ARRAY_LIMIT ; i++)
        for (j = 0 ; j < ARBITRARY_2D_ARRAY_LIMIT ; j++)
            arrayIn2D[i][j] = value;
}

int valueIsBetween(int value, int min, int max)
{
    return (min <= value && value <= max);
}

void swapValues(int * value1, int * value2)
{
    int tmp = *value1;
    *value1 = *value2;
    *value2 = tmp;
}

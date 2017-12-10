#include "day10.h"

SolutionIntegerString getSolutionDay10(const char * inputFilePath)
{
    SolutionIntegerString solution;
    int keepReading = 1, ongoingAdditionalSequence = 1;
    int currentNumber = 0, currentAdditionalNumber = BEGINNING_OF_ADDITIONAL_SEQUENCE, counterOfRounds = 0, i = 0, j = 0, correctIndex = 0, correctOppositeIndex = 0, currentIndex = 0, tmp = 0, skipSize = 0;
    int array[SIZE_DAY10_ARRAY];
    char currentChar;
    char hexadecimalNumber[3];
    FILE* file = NULL;

    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        for (i = 0 ; i < SIZE_DAY10_ARRAY ; i++)
            array[i] = i;
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isADigit(currentChar))
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else if (currentChar == ',' || currentChar == '\n' || currentChar == EOF)
            {
                j = currentIndex + currentNumber - 1;
                for (i = 0 ; i < currentNumber / 2 ; i++)
                {
                    correctIndex = (i + currentIndex) % SIZE_DAY10_ARRAY;
                    correctOppositeIndex = j % SIZE_DAY10_ARRAY;
                    tmp = array[correctIndex];
                    array[correctIndex] = array[correctOppositeIndex];
                    array[correctOppositeIndex] = tmp;
                    j--;
                }
                currentIndex += currentNumber + skipSize;
                currentIndex %= SIZE_DAY10_ARRAY;
                skipSize += 1;
                currentNumber = 0;
                if (currentChar == '\n' || currentChar == EOF)
                    keepReading = 0;
            }
        }
        solution.solutionPart1 = array[0] * array[1];

        skipSize = 0;
        currentIndex = 0;
        for (i = 0 ; i < SIZE_DAY10_ARRAY ; i++)
            array[i] = i;
        for (counterOfRounds = 0 ; counterOfRounds < TYPICAL_NUMBER_OF_ROUNDS ; counterOfRounds++)
        {
            rewind(file);
            keepReading = 1;
            ongoingAdditionalSequence = 1;
            currentAdditionalNumber = BEGINNING_OF_ADDITIONAL_SEQUENCE;
            while (keepReading || ongoingAdditionalSequence)
            {
                if (keepReading)
                    currentChar = fgetc(file);
                if ((keepReading && currentChar != '\n' && currentChar != EOF) ||
                    (!keepReading && currentAdditionalNumber != END_OF_ADDITIONAL_SEQUENCE))
                {
                    currentNumber = keepReading ? currentChar : currentAdditionalNumber;

                    // TBD: remove duplication by creating a modulo-based reverse function for a 1D array
                    j = currentIndex + currentNumber - 1;
                    for (i = 0 ; i < currentNumber / 2 ; i++)
                    {
                        correctIndex = (i + currentIndex) % SIZE_DAY10_ARRAY;
                        correctOppositeIndex = j % SIZE_DAY10_ARRAY;
                        tmp = array[correctIndex];
                        array[correctIndex] = array[correctOppositeIndex];
                        array[correctOppositeIndex] = tmp;
                        j--;
                    }
                    currentIndex += currentNumber + skipSize;
                    currentIndex %= SIZE_DAY10_ARRAY;
                    skipSize += 1;

                    if (!keepReading)
                        currentAdditionalNumber = nextInAdditionalSequence(currentAdditionalNumber);
                }
                else if (keepReading)
                    keepReading = 0;
                else
                    ongoingAdditionalSequence = 0;
            }
        }

        for (i = 0 ; i < SIZE_DENSE_HASH ; i++)
        {
            sprintf(hexadecimalNumber, "%02x", performXorOn16NumberBlock(array, i * 16));
            solution.solutionPart2[i * 2] = hexadecimalNumber[0];
            solution.solutionPart2[i * 2 + 1] = hexadecimalNumber[1];
        }
        solution.solutionPart2[32] = '\0';

        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

int nextInAdditionalSequence(int current)
{
    switch (current)
    {
        case BEGINNING_OF_ADDITIONAL_SEQUENCE:
            return 31;
        case 31:
            return 73;
        case 73:
            return 47;
        case 47:
            return 23;
        case 23:
        default:
            return END_OF_ADDITIONAL_SEQUENCE;
    }
}

int bitXor(int x, int y)
{
    int a = x & y;
    int b = ~x & ~y;
    return ~a & ~b;
}

int performXorOn16NumberBlock(const int * array, int startingIndex)
{
    int i, result = bitXor(array[startingIndex], array[startingIndex + 1]);
    for (i = startingIndex + 2 ; i < startingIndex + 16 ; i++)
        result = bitXor(result, array[i]);
    return result;
}

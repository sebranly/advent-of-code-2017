#include "knotHash.h"

int nextInAdditionalSequence(int current)
{
    switch (current)
    {
        case KNOT_HASH_BEGINNING_OF_ADDITIONAL_SEQUENCE:
            return 31;
        case 31:
            return 73;
        case 73:
            return 47;
        case 47:
            return 23;
        case 23:
        default:
            return KNOT_HASH_END_OF_ADDITIONAL_SEQUENCE;
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

void initializeKnotHashElements(KnotHashElements * elements)
{
    int i;
    elements->currentIndex = 0;
    elements->skipSize = 0;
    elements->finalKnotHash[0] = '\0';
    elements->hexadecimalNumber[0] = '\0';
    for (i = 0 ; i < SIZE_KNOT_HASH_ARRAY ; i++)
        elements->array[i] = i;
}

void operateArrayChangesBasedOnNumber(int currentNumber, KnotHashElements * elements)
{
    int correctIndex, correctOppositeIndex, tmp;
    int i, j = elements->currentIndex + currentNumber - 1;
    for (i = 0 ; i < currentNumber / 2 ; i++)
    {
        correctIndex = (i + elements->currentIndex) % SIZE_KNOT_HASH_ARRAY;
        correctOppositeIndex = j % SIZE_KNOT_HASH_ARRAY;
        tmp = elements->array[correctIndex];
        elements->array[correctIndex] = elements->array[correctOppositeIndex];
        elements->array[correctOppositeIndex] = tmp;
        j--;
    }
    elements->currentIndex += currentNumber + elements->skipSize;
    elements->currentIndex %= SIZE_KNOT_HASH_ARRAY;
    elements->skipSize += 1;
}

void determineFinalKnotHashString(const char * initialString, KnotHashElements * knotHashElements)
{
    char currentChar;
    int i, counterOfRounds, currentCharIndex, currentNumber, currentAdditionalNumber;
    int keepReadingString = 1, ongoingAdditionalSequence = 1;
    initializeKnotHashElements(knotHashElements);
    for (counterOfRounds = 0 ; counterOfRounds < KNOT_HASH_TYPICAL_NUMBER_OF_ROUNDS ; counterOfRounds++)
    {
        currentCharIndex = 0;
        keepReadingString = 1;
        ongoingAdditionalSequence = 1;
        currentAdditionalNumber = KNOT_HASH_BEGINNING_OF_ADDITIONAL_SEQUENCE;
        while (keepReadingString || ongoingAdditionalSequence)
        {
            if (keepReadingString)
            {
                currentChar = initialString[currentCharIndex];
                currentCharIndex++;
            }
            if ((keepReadingString && currentChar != '\0') ||
                (!keepReadingString && currentAdditionalNumber != KNOT_HASH_END_OF_ADDITIONAL_SEQUENCE))
            {
                currentNumber = keepReadingString ? currentChar : currentAdditionalNumber;
                operateArrayChangesBasedOnNumber(currentNumber, knotHashElements);

                if (!keepReadingString)
                    currentAdditionalNumber = nextInAdditionalSequence(currentAdditionalNumber);
            }
            else if (keepReadingString)
                keepReadingString = 0;
            else
                ongoingAdditionalSequence = 0;
        }
    }

    for (i = 0 ; i < SIZE_DENSE_HASH ; i++)
    {
        sprintf(knotHashElements->hexadecimalNumber, "%02x", performXorOn16NumberBlock(knotHashElements->array, i * 16));
        knotHashElements->finalKnotHash[i * (HEXADECIMAL_NUMBER_STRING_LENGTH - 1)] = knotHashElements->hexadecimalNumber[0];
        knotHashElements->finalKnotHash[i * (HEXADECIMAL_NUMBER_STRING_LENGTH - 1) + 1] = knotHashElements->hexadecimalNumber[1];
    }
    knotHashElements->finalKnotHash[FINAL_KNOT_HASH_STRING_LENGTH - 1] = '\0';
}

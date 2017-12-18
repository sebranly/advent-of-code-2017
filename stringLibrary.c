#include "stringLibrary.h"

int isALowerCaseLetter(char c)
{
    return (c >= A_LOWER_CASE_ASCII_CODE && c <= Z_LOWER_CASE_ASCII_CODE);
}

void countLetters(const char * string, int array[NUMBER_OF_LOWER_CASE_LETTERS])
{
    int i = 0;
    fillAllCells(array, NUMBER_OF_LOWER_CASE_LETTERS, 0);
    while (string[i] != '\0')
    {
        array[string[i] - A_LOWER_CASE_ASCII_CODE]++;
        i++;
    }
}

int sameStrings(const char * string1, const char * string2)
{
    return (strcmp(string1, string2) == SAME_STRINGS);
}

void initializeAlphabeticalSequence(char * string, int numberOfLetters)
{
    int i;
    if (numberOfLetters <= NUMBER_OF_LOWER_CASE_LETTERS)
    {
        for (i = 0 ; i < numberOfLetters ; i++)
            string[i] = i + A_LOWER_CASE_ASCII_CODE;
        string[i] = '\0';
    }
}

void swapValuesInString(char * string, int position1, int position2)
{
    int tmp = string[position1];
    string[position1] = string[position2];
    string[position2] = tmp;
}

int findFirstOccurrence(const char * string, char character)
{
    int i = 0;
    while (string[i] != character)
    {
        if (string[i] == '\0')
            return CHARACTER_NOT_FOUND;
        i++;
    }
    return i;
}

int findSecondOccurrence(const char * string, char character)
{
    int counter = 0, i = 0;
    while (string[i] != '\0')
    {
        if (string[i] == character)
            if (counter == 0)
                counter++;
            else
                return i;
        i++;
    }
    return CHARACTER_NOT_FOUND;
}

void spinString(char * string, int length, int spinSize)
{
    int startingPoint = length - 1 - spinSize;
    int currentIndex = startingPoint;
    char * string2;
    string2 = malloc(length * sizeof(char));
    if (string2 == NULL)
    {
        printf("An error occurred because of limited memory\n");
        exit(EXIT_FAILURE);
    }
    while (string[currentIndex] != '\0')
    {
        string2[currentIndex - startingPoint] = string[currentIndex];
        currentIndex++;
    }
    string2[currentIndex - startingPoint] = '\0';
    currentIndex = length - 2;
    while (currentIndex >= 0 + spinSize)
    {
        string[currentIndex] = string[currentIndex - spinSize];
        currentIndex--;
    }
    currentIndex = 0;
    while (string2[currentIndex] != '\0')
    {
        string[currentIndex] = string2[currentIndex];
        currentIndex++;
    }
    free(string2);
}

// Returns 1 if it could convert the portion of the string to an integer, otherwise 0
int stringToLongLong(const char * string, int startingIndex, int endingIndex, long long * number)
{
    int index = startingIndex;
    long long currentNumber = 0;
    int sign = 1, atLeastOneDigit =0;
    while ((endingIndex == NO_ENDING_INDEX && string[index] != '\0') || (endingIndex != NO_ENDING_INDEX && index <= endingIndex))
    {
        if (string[index] == '-')
            sign = -1;
        else if (isADigit(string[index]))
        {
            atLeastOneDigit = 1;
            currentNumber *= 10;
            currentNumber += toInteger(string[index]);
        }
        index++;
    }
    if (atLeastOneDigit)
    {
        *number = sign * currentNumber;
        return 1;
    }
    return 0;
}

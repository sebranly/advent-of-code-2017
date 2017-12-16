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

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

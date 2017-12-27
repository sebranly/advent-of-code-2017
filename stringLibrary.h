#ifndef STRINGLIBRARY_H_INCLUDED
#define STRINGLIBRARY_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "main.h"
// TBD: create arrayLibrary.h and .c files and include them here for filling cells functions

#define NUMBER_OF_LOWER_CASE_LETTERS 26
#define SAME_STRINGS 0
#define SHORT_STRING_LENGTH 20
#define LONG_STRING_LENGTH 100
#define CHARACTER_NOT_FOUND -1
#define NO_ENDING_INDEX -1

int isALowerCaseLetter(char c);
int isAnUpperCaseLetter(char c);
void countLetters(const char * string, int array[NUMBER_OF_LOWER_CASE_LETTERS]);
int sameStrings(const char * string1, const char * string2);
void initializeAlphabeticalSequence(char * string, int numberOfLetters);
void swapValuesInString(char * string, int position1, int position2);
int findFirstOccurrence(const char * string, char character);
int findSecondOccurrence(const char * string, char character);
void spinString(char * string, int length, int spinSize);
int stringToLongLong(const char * string, int startingIndex, int endingIndex, long long * integer);

#endif // STRINGLIBRARY_H_INCLUDED

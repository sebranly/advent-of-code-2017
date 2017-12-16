#ifndef STRINGLIBRARY_H_INCLUDED
#define STRINGLIBRARY_H_INCLUDED

#include <stdlib.h>
#include <string.h>
// TBD: create arrayLibrary.h and .c files and include them here for filling cells functions

#define NUMBER_OF_LOWER_CASE_LETTERS 26
#define SAME_STRINGS 0
#define SHORT_STRING_LENGTH 20
#define LONG_STRING_LENGTH 100
#define CHARACTER_NOT_FOUND -1

enum { A_LOWER_CASE_ASCII_CODE = 97, Z_LOWER_CASE_ASCII_CODE = 122 };

int isALowerCaseLetter(char c);
void countLetters(const char * string, int array[NUMBER_OF_LOWER_CASE_LETTERS]);
int sameStrings(const char * string1, const char * string2);
void initializeAlphabeticalSequence(char * string, int numberOfLetters);
void swapValuesInString(char * string, int position1, int position2);
int findFirstOccurrence(const char * string, char character);
void spinString(char * string, int length, int spinSize);

#endif // STRINGLIBRARY_H_INCLUDED

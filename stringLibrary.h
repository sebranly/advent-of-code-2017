#ifndef STRINGLIBRARY_H_INCLUDED
#define STRINGLIBRARY_H_INCLUDED

#include <string.h>
// TBD: create arrayLibrary.h and .c files and include them here for filling cells functions

#define NUMBER_OF_LOWER_CASE_LETTERS 26
#define SAME_STRINGS 0

enum { A_LOWER_CASE_ASCII_CODE = 97, Z_LOWER_CASE_ASCII_CODE = 122 };

int isALowerCaseLetter(char c);
void countLetters(const char * string, int array[NUMBER_OF_LOWER_CASE_LETTERS]);
int sameStrings(const char * string1, const char * string2);

#endif // STRINGLIBRARY_H_INCLUDED

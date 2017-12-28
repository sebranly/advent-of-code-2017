#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

enum { ZERO_ASCII_CODE = 48, NINE_ASCII_CODE = 57 };

#define LATEST_AVAILABLE_CHALLENGE 25
#define MAX_CHALLENGE 25

#define UNSET -1
#define EXIT_VALUE -1
#define TEST_SUITE_VALUE -2
#define NOT_FOUND -1

#define ARBITRARY_ARRAY_LIMIT 3000
// The following value is a limit per dimension
#define ARBITRARY_2D_ARRAY_LIMIT 100
#define MAX_FILE_NAME_LENGTH 50
#define STRING_MAX_LENGTH 30
#define STRING_LIMITED_LENGTH 5
#define MAX_ELEMENTS_PER_LINE 30

enum { NORTH, SOUTH, WEST, EAST };

int isADigit(char c);
int toInteger(char digit);
int valueIsBetween(int value, int min, int max);
void fillAllCellsIn2D(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int value);
void swapValues(int * value1, int * value2);

#endif // MAIN_H_INCLUDED

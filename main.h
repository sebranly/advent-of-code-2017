#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

enum { ZERO_ASCII_CODE = 48, NINE_ASCII_CODE = 57 };
enum { NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST };
enum { NORTH, SOUTH, WEST, EAST };

#define MAX_TREE_ELEMENTS 1200
#define MAX_REGISTERS 1200
#define TREE_ELEMENT_NAME_MAX_LENGTH 20
#define REGISTER_NAME_MAX_LENGTH 10

#define LATEST_AVAILABLE_CHALLENGE 18
#define MAX_CHALLENGE 25

#define UNSET -1
#define EXIT_VALUE -1
#define NOT_FOUND -1

#define ARBITRARY_ARRAY_LIMIT 3000
// TBD - Note: day challenge 6 part 1 deserves an optimization because this is only a workaround so far (problem is memory limitation)
#define ARBITRARY_NUMBER_OF_RECORDS 15000
#define ARBITRARY_NUMBER_OF_ELEMENTS_PER_RECORD 30
// The following value is a limit per dimension
#define ARBITRARY_2D_ARRAY_LIMIT 100
#define MAX_FILE_NAME_LENGTH 50
#define STRING_MAX_LENGTH 30
#define STRING_LIMITED_LENGTH 5
#define MAX_ELEMENTS_PER_LINE 30
#define MAX_DEPTH_TO_DISPLAY 2

#define NUMBER_OF_CARDINAL_DIRECTIONS 4

typedef struct TreeElement TreeElement;
struct TreeElement
{
    char uniqueAncestorName[TREE_ELEMENT_NAME_MAX_LENGTH];
    char name[TREE_ELEMENT_NAME_MAX_LENGTH];
    int valueOfAncestor;
    int valueOfAncestorAndChildren;
};

typedef struct Register Register;
struct Register
{
    char name[REGISTER_NAME_MAX_LENGTH];
    int value;
};

int isADigit(char c);
int toInteger(char digit);
int nextSpiralDirection(int currentDirection);
int valueIsBetween(int value, int min, int max);
void moveOneStep(int * x, int * y, int currentDirection);
void fillAllCells(int array[], int sizeArray, int value);
int minIndexOfMaxValue(int array[], int size);
int differentArrays(int array1[], int array2[], int size);
void copyFirstCells(int sourceArray[], int destinationArray[], int numberOfCellsToBeCopied);
void fillAllCellsIn2D(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int value);
int sumOfAdjacentCells(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int x, int y);
void emptyInlineTextInput(char inlineInputAsText[MAX_ELEMENTS_PER_LINE][STRING_MAX_LENGTH]);
void printCellsArrayIn2D(const int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int minX, int maxX, int minY, int maxY);
int addAncestor(TreeElement elements[], int size, const char elementName[], const char ancestorName[]);
void removeTreeAncestors(TreeElement elements[], int size);
TreeElement firstElementWithoutAncestor(TreeElement elements[], int size);
void displayChildren(TreeElement elements[], int size, const TreeElement ancestor, int depth);
int setValueOfAncestorAndChildren(TreeElement elements[], int size, TreeElement * ancestor);
int createNewRegister(Register * registers, int size, const char * name);
int findRegister(const Register * registers, int size, const char * name);
void swapValues(int * value1, int * value2);

#endif // MAIN_H_INCLUDED

#ifndef DAY04_H_INCLUDED
#define DAY04_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../../other/header/stringLibrary.h"
#include "../../other/header/solutionTypes.h"
#include "../../main.h"

SolutionIntegers getSolutionDay04(const char * inputFilePath);
void emptyInlineTextInput(char inlineInputAsText[MAX_ELEMENTS_PER_LINE][STRING_MAX_LENGTH]);
void fillAllCells(int array[], int sizeArray, int value);
int differentArrays(int array1[], int array2[], int size);

#endif // DAY04_H_INCLUDED

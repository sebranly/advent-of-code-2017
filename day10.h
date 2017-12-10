#ifndef DAY10_H_INCLUDED
#define DAY10_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "solutionTypes.h"
// TBD: delete it once main.h is way shorter by exporting definitions for example
#include "main.h"

#define SIZE_DAY10_ARRAY 256
#define SIZE_DENSE_HASH (SIZE_DAY10_ARRAY / 16)
#define BEGINNING_OF_ADDITIONAL_SEQUENCE 17
#define END_OF_ADDITIONAL_SEQUENCE -1
#define TYPICAL_NUMBER_OF_ROUNDS 64

SolutionIntegerString getSolutionDay10(const char * inputFilePath);
int nextInAdditionalSequence(int current);
int bitXor(int x, int y);
int performXorOn16NumberBlock(const int * array, int startingIndex);

#endif // DAY10_H_INCLUDED

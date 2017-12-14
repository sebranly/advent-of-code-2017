#ifndef DAY14_H_INCLUDED
#define DAY14_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solutionTypes.h"
#include "knotHash.h"
#include "stringLibrary.h"
#include "fileLibrary.h"

#define BITS_STRING_LENGTH ((FINAL_KNOT_HASH_STRING_LENGTH - 1) * 4 + 1) // Corresponds to 129 in our example because the knot hash has 32 hexadecimal digit
#define GRID_SIZE (BITS_STRING_LENGTH - 1)

SolutionIntegers getSolutionDay14(const char * inputFilePath);
void hexadecimalStringToBitsString(const char * hexadecimalString, char * bitsString);
int determineGroups(int grid[GRID_SIZE][GRID_SIZE]);
int sprayOneGroup(int grid[128][128], int x, int y, int maxGroupId, int fromCoreFunction);

#endif // DAY14_H_INCLUDED

#ifndef DAY03_H_INCLUDED
#define DAY03_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../../other/header/solutionTypes.h"
#include "../../main.h"

#define NUMBER_OF_CARDINAL_DIRECTIONS 4

enum { NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST };

SolutionIntegers getSolutionDay03(const char * inputFilePath);
int nextSpiralDirection(int currentDirection);
void moveOneStep(int * x, int * y, int currentDirection);
int sumOfAdjacentCells(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int x, int y);

#endif // DAY03_H_INCLUDED

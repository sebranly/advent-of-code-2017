#ifndef DAY22_H_INCLUDED
#define DAY22_H_INCLUDED

#include "coordinates.h"
#include "solutionTypes.h"
#include "fileLibrary.h"
// Because of the cardinal directions enumeration
#include "main.h"

#define LIMIT_VALUE_DAY_22_PART_1 10000
#define CLEAN_NODE '.'
#define INFECTED_NODE '#'

enum { TURN_LEFT, TURN_RIGHT };

typedef struct Node Node;
struct Node
{
    PositiveCoordinates2D coordinates;
    int infected;
};

SolutionIntegers getSolutionDay22(const char * inputFilePath);
void changeDirection(int * currentDirection, int turningDirection);
void moveOneNode(PositiveCoordinates2D * currentPosition, int currentDirection);

#endif // DAY22_H_INCLUDED

#ifndef DAY22_H_INCLUDED
#define DAY22_H_INCLUDED

#include "coordinates.h"
#include "solutionTypes.h"
#include "fileLibrary.h"
#include "mathLibrary.h"
// Because of the cardinal directions enumeration
#include "main.h"

#define LIMIT_VALUE_DAY_22_PART_1 10000
#define LIMIT_VALUE_DAY_22_PART_2 10000000
#define CLEAN_NODE '.'
#define INFECTED_NODE '#'
#define NOT_REFERENCED_NODE -1

enum { TURN_LEFT, TURN_RIGHT, TURN_BACK };
enum { CLEAN_STATE = 0, INFECTED_STATE = 1, FLAGGED_STATE = 2, WEAKENED_STATE = 3 };

typedef struct Node Node;
struct Node
{
    PositiveCoordinates2D coordinates;
    int state;
};

SolutionIntegers getSolutionDay22(const char * inputFilePath);
void changeDirection(int * currentDirection, int turningDirection);
void moveOneNode(PositiveCoordinates2D * currentPosition, int currentDirection);

#endif // DAY22_H_INCLUDED

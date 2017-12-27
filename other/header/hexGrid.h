#ifndef HEXGRID_H_INCLUDED
#define HEXGRID_H_INCLUDED

#include "stringLibrary.h"

#define NUMBER_OF_HEX_AXES 3

enum { HEX_NORTH, HEX_NORTH_EAST, HEX_SOUTH_EAST, HEX_SOUTH, HEX_SOUTH_WEST, HEX_NORTH_WEST };

void minimizeSteps(int steps[NUMBER_OF_HEX_AXES]);
void addSteps(char * direction, int steps[NUMBER_OF_HEX_AXES]);

#endif // HEXGRID_H_INCLUDED

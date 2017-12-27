#ifndef DAY16_H_INCLUDED
#define DAY16_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../other/header/stringLibrary.h"
#include "../../other/header/solutionTypes.h"
// TBD: delete it once main.h is way shorter by exporting definitions for example
#include "../../main.h"

#define NUMBER_OF_LETTERS_DAY_16 16
#define DANCE_COMMAND_LENGTH 10
#define DANCE_MAX_PERIOD 19600 // Based on a reddit post stating it's 140^2
#define NUMBER_OF_DANCES_PART_2 1000000000

SolutionStrings getSolutionDay16(const char * inputFilePath);
void determineSwappedPositions(const char * xCommand, int * position1, int * position2);
void determineSwappedPrograms(const char * pCommand, char * program1, char * program2);
void determineSwappedPositionsBasedOnSwapPrograms(const char * programs, int * position1, int * position2, char program1, char program2);
int determineSpinSize(const char * sCommand);

#endif // DAY16_H_INCLUDED

#ifndef DAY15_H_INCLUDED
#define DAY15_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../../other/header/solutionTypes.h"
// TBD: delete it once main.h is way shorter by exporting definitions for example
#include "../../main.h"

#define NUMBER_OF_ITERATIONS_PART_1 40000000
#define NUMBER_OF_ITERATIONS_PART_2 5000000

SolutionIntegers getSolutionDay15(const char * inputFilePath);
unsigned long long getNextGeneratorValue(unsigned long long number, int generatorNumber, int partNumber);

#endif // DAY15_H_INCLUDED

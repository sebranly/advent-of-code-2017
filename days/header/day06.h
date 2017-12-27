#ifndef DAY06_H_INCLUDED
#define DAY06_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../../other/header/solutionTypes.h"
#include "../../main.h"

// TBD - Note: day challenge 6 part 1 deserves an optimization because this is only a workaround so far (problem is memory limitation)
#define ARBITRARY_NUMBER_OF_RECORDS 15000
#define ARBITRARY_NUMBER_OF_ELEMENTS_PER_RECORD 30

SolutionIntegers getSolutionDay06(const char * inputFilePath);
int minIndexOfMaxValue(int array[], int size);

#endif // DAY06_H_INCLUDED

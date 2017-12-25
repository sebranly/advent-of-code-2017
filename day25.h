#ifndef DAY25_H_INCLUDED
#define DAY25_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "fileLibrary.h"
#include "stringLibrary.h"

#define DAY_25_HEADER_INPUT_NUMBER_OF_LINES 2
#define DAY_25_STATE_INPUT_NUMBER_OF_LINES 9

typedef struct StateRule StateRule;
struct StateRule
{
    int nextValueIf[2];
    int nextOffsetIf[2];
    int nextStateIf[2];
};

int getSolutionDay25(const char * inputFilePath);

#endif // DAY25_H_INCLUDED

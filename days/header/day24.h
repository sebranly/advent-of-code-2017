#ifndef DAY24_H_INCLUDED
#define DAY24_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../../other/header/solutionTypes.h"
#include "../../other/header/fileLibrary.h"
#include "../../other/header/stackLibrary.h"
// TBD: delete it once main.h is way shorter by exporting definitions for example
#include "../../main.h"

#define NO_TOP_ID -1

typedef struct BridgeBrick BridgeBrick;
struct BridgeBrick
{
    unsigned int port1;
    unsigned int port2;
    int port1isAvailable;
    int port2isAvailable;
};

SolutionIntegers getSolutionDay24(const char * inputFilePath);
void createBridge(Stack *stack, BridgeBrick *bricks, int numberOfBricks, int * maxStrength, int * lengthLongestBridge, int * maxStrengthLongestBridge);
int calculateBridgeStrength(Stack * stack, BridgeBrick *bricks);

#endif // DAY24_H_INCLUDED

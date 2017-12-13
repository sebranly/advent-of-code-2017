#ifndef DAY13_H_INCLUDED
#define DAY13_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "solutionTypes.h"

#define INCORRECT_SOLUTION -1

enum { UP, DOWN };

typedef struct SecurityLayer SecurityLayer;
struct SecurityLayer
{
    int range;
    int indexScanner;
    int detectedPlayer;
    int direction;
};

SolutionIntegers getSolutionDay13(const char * inputFilePath);
void displayCurrentSecurityState(const SecurityLayer * layers, int numberOfLayers);
void initializeSecurityScanners(SecurityLayer * layers, int numberOfLayers);
void moveAllSecurityScanners(SecurityLayer * layers, int numberOfLayers, int currentPlayer);
int indexScannerDependingOnRangeAndTime(int range, int time);

#endif // DAY13_H_INCLUDED

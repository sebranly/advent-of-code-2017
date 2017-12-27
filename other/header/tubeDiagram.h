#ifndef TUBEDIAGRAM_H_INCLUDED
#define TUBEDIAGRAM_H_INCLUDED

#define INCORRECT_NUMBER_OF_STEPS -1

#include <stdlib.h>
#include <stdio.h>
#include "coordinates.h"
// TBD: delete it once main.h is way shorter by exporting definitions for example
#include "../../main.h"

typedef struct TubeDiagram TubeDiagram;
struct TubeDiagram
{
    Coordinates2D vectorNextMove;
    Coordinates2D currentPosition;
    char **diagram;
    char *path;
    int currentPathIndex;
    int numberOfLetters;
    int counterOfPickedLetters;
    int numberOfSteps;
    int widthDiagram;
    int heightDiagram;
};

void initializeTubeDiagram(TubeDiagram * tubeDiagram);
void fillTubeDiagram(TubeDiagram * tubeDiagram, const char * inputFilePath);
void displayTubeDiagramDiagram(const TubeDiagram tubeDiagram);
void findTubeDiagramStartingPosition(TubeDiagram * tubeDiagram);
void moveOneStepInTubeDiagram(TubeDiagram * tubeDiagram);

#endif // TUBEDIAGRAM_H_INCLUDED

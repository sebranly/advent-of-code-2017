#ifndef TUBEDIAGRAM_H_INCLUDED
#define TUBEDIAGRAM_H_INCLUDED

#define INCORRECT_NUMBER_OF_STEPS -1

#include <stdlib.h>
#include <stdio.h>
#include "main.h"

typedef struct Coordinates Coordinates;
struct Coordinates
{
    int x;
    int y;
};

typedef struct TubeDiagram TubeDiagram;
struct TubeDiagram
{
    Coordinates vectorNextMove;
    Coordinates currentPosition;
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

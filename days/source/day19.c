#include "../header/day19.h"

SolutionStringInteger getSolutionDay19(const char * inputFilePath)
{
    SolutionStringInteger solution;
    int i;

    strcpy(solution.solutionPart1, "");
    solution.solutionPart2 = INCORRECT_NUMBER_OF_STEPS;

    TubeDiagram tubeDiagram;
    tubeDiagram.heightDiagram = numberOfNonEmptyLines(inputFilePath);
    tubeDiagram.widthDiagram = lengthFirstLine(inputFilePath);
    tubeDiagram.diagram = malloc(sizeof(*(tubeDiagram.diagram)) * tubeDiagram.heightDiagram);
    for (i = 0 ; i < tubeDiagram.heightDiagram ; i++)
        tubeDiagram.diagram[i] = malloc(sizeof(**(tubeDiagram.diagram)) * tubeDiagram.widthDiagram);

    initializeTubeDiagram(&tubeDiagram);
    fillTubeDiagram(&tubeDiagram, inputFilePath);
    // displayTubeDiagramDiagram(tubeDiagram);
    findTubeDiagramStartingPosition(&tubeDiagram);

    while (tubeDiagram.counterOfPickedLetters < tubeDiagram.numberOfLetters)
        moveOneStepInTubeDiagram(&tubeDiagram);

    strcpy(solution.solutionPart1, tubeDiagram.path);
    solution.solutionPart2 = tubeDiagram.numberOfSteps;

    for (i = 0 ; i < tubeDiagram.heightDiagram ; i++)
        free(tubeDiagram.diagram[i]);
    free(tubeDiagram.diagram);
    free(tubeDiagram.path);

    return solution;
}

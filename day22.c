#include "day22.h"

SolutionIntegers getSolutionDay22(const char * inputFilePath)
{
    SolutionIntegers solution;
    int sizeInput = lengthFirstLine(inputFilePath);
    int maxLimit = max(LIMIT_VALUE_DAY_22_PART_1, LIMIT_VALUE_DAY_22_PART_2);
    // The input grid is a square that corresponds to the center of the "infinite" grid
    // To represent the latter for a simulation, a grid of (number of iterations + 1 (central element)) elements is enough
    // We calculate the offset of the input grid by taking this simulation grid as the reference
    int offsetInput = maxLimit / 2 + 1 - sizeInput / 2;
    PositiveCoordinates2D currentPosition;
    int x, y, i, iteration, numberOfIterationsCausingInfection, partNumber;
    // One iteration contaminates one node max so the following number is way sufficient to store all the infected nodes
    // whatever the number of infected nodes in the input is
    int maxNumberOfInfectedNodesPossible = sizeInput * sizeInput + maxLimit;
    int numberOfReferencedNodes, numberOfIterations;
    int keepReading;
    int currentDirection;
    // This variable will reference all the nodes that are or have been infected by the past
    // It will never reference a node that has never been infected
    Node * nodes;
    // This will contain the index of the current node if this node has once been added to the referenced nodes
    int currentPositionIndexInNode;
    char currentChar;

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        nodes = malloc(sizeof(Node) * maxNumberOfInfectedNodesPossible);
        if (nodes == NULL)
        {
            printf("An error occurred because of memory limitation\n");
            exit(EXIT_FAILURE);
        }
        for (partNumber = 1 ; partNumber <= 2 ; partNumber++)
        {
            printf("Calculating part %d, please wait...\n", partNumber);
            // We start at the middle of the grid
            currentPosition.x = maxLimit / 2 + 1;
            currentPosition.y = maxLimit / 2 + 1;
            x = offsetInput;
            y = offsetInput;
            numberOfIterationsCausingInfection = 0;
            numberOfReferencedNodes = 0;
            keepReading = 1;
            currentDirection = NORTH;
            if (partNumber == 2)
                rewind(file);

            while (keepReading)
            {
                currentChar = fgetc(file);
                if (currentChar == INFECTED_NODE)
                {
                    nodes[numberOfReferencedNodes].state = INFECTED_STATE;
                    nodes[numberOfReferencedNodes].coordinates.x = x;
                    nodes[numberOfReferencedNodes].coordinates.y = y;
                    numberOfReferencedNodes++;

                    x++;
                }
                else if (currentChar == CLEAN_NODE)
                    x++;
                else if (currentChar == '\n')
                {
                    y++;
                    x = offsetInput;
                }
                else if (currentChar == EOF)
                    keepReading = 0;
            }

            numberOfIterations = partNumber == 1 ? LIMIT_VALUE_DAY_22_PART_1 : LIMIT_VALUE_DAY_22_PART_2;
            for (iteration = 0 ; iteration < numberOfIterations ; iteration++)
            {
                if (iteration % (numberOfIterations / 100) == 0)
                    printf("%d per cent completed\n", iteration / (numberOfIterations / 100));
                // We try and find the element
                currentPositionIndexInNode = NOT_REFERENCED_NODE;
                for (i = 0 ; i < numberOfReferencedNodes && currentPositionIndexInNode == NOT_REFERENCED_NODE ; i++)
                    if (identicalPositiveCoordinates2D(nodes[i].coordinates, currentPosition))
                        currentPositionIndexInNode = i;

                if (currentPositionIndexInNode != NOT_REFERENCED_NODE && nodes[currentPositionIndexInNode].state != CLEAN_STATE)
                {
                    if (nodes[currentPositionIndexInNode].state == INFECTED_STATE)
                    {
                        changeDirection(&currentDirection, TURN_RIGHT);
                        nodes[currentPositionIndexInNode].state = (partNumber == 1) ? CLEAN_STATE : FLAGGED_STATE;
                    }
                    else if (nodes[currentPositionIndexInNode].state == WEAKENED_STATE)
                    {
                        nodes[currentPositionIndexInNode].state = INFECTED_STATE;
                        numberOfIterationsCausingInfection++;
                    }
                    else if (nodes[currentPositionIndexInNode].state == FLAGGED_STATE)
                    {
                        changeDirection(&currentDirection, TURN_BACK);
                        nodes[currentPositionIndexInNode].state = CLEAN_STATE;
                    }
                }
                else
                {
                    changeDirection(&currentDirection, TURN_LEFT);

                    // In that case we have to create this element
                    if (currentPositionIndexInNode == NOT_REFERENCED_NODE)
                    {
                        if (partNumber == 1)
                        {
                            nodes[numberOfReferencedNodes].state = INFECTED_STATE;
                            numberOfIterationsCausingInfection++;
                        }
                        else
                            nodes[numberOfReferencedNodes].state = WEAKENED_STATE;

                        nodes[numberOfReferencedNodes].coordinates.x = currentPosition.x;
                        nodes[numberOfReferencedNodes].coordinates.y = currentPosition.y;
                        numberOfReferencedNodes++;
                    }
                    // In that case we just have to update the element
                    else
                    {
                        if (partNumber == 1)
                        {
                            nodes[currentPositionIndexInNode].state = INFECTED_STATE;
                            numberOfIterationsCausingInfection++;
                        }
                        else
                            nodes[currentPositionIndexInNode].state = WEAKENED_STATE;
                    }
                }
                moveOneNode(&currentPosition, currentDirection);
            }
            if (partNumber == 1)
                solution.solutionPart1 = numberOfIterationsCausingInfection;
            else
                solution.solutionPart2 = numberOfIterationsCausingInfection;
        }

        free(nodes);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

void changeDirection(int * currentDirection, int turningDirection)
{
    switch (*currentDirection)
    {
        case NORTH:
            if (turningDirection == TURN_LEFT)
                *currentDirection = WEST;
            else if (turningDirection == TURN_RIGHT)
                *currentDirection = EAST;
            else if (turningDirection == TURN_BACK)
                *currentDirection = SOUTH;
            break;
        case SOUTH:
            if (turningDirection == TURN_LEFT)
                *currentDirection = EAST;
            else if (turningDirection == TURN_RIGHT)
                *currentDirection = WEST;
            else if (turningDirection == TURN_BACK)
                *currentDirection = NORTH;
            break;
        case WEST:
            if (turningDirection == TURN_LEFT)
                *currentDirection = SOUTH;
            else if (turningDirection == TURN_RIGHT)
                *currentDirection = NORTH;
            else if (turningDirection == TURN_BACK)
                *currentDirection = EAST;
            break;
        case EAST:
        default:
            if (turningDirection == TURN_LEFT)
                *currentDirection = NORTH;
            else if (turningDirection == TURN_RIGHT)
                *currentDirection = SOUTH;
            else if (turningDirection == TURN_BACK)
                *currentDirection = WEST;
            break;

    }
}

void moveOneNode(PositiveCoordinates2D * currentPosition, int currentDirection)
{
    int x, y;
    switch (currentDirection)
    {
        case NORTH:
            x = 0;
            y = -1;
            break;
        case SOUTH:
            x = 0;
            y = 1;
            break;
        case WEST:
            x = -1;
            y = 0;
            break;
        case EAST:
        default:
            x = 1;
            y = 0;
            break;
    }
    currentPosition->x += x;
    currentPosition->y += y;
}

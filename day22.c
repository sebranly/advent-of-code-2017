#include "day22.h"

SolutionIntegers getSolutionDay22(const char * inputFilePath)
{
    SolutionIntegers solution;
    int sizeInput = lengthFirstLine(inputFilePath);
    // The input grid is a square that corresponds to the center of the "infinite" grid
    // To represent the latter for a simulation, a grid of (number of iterations + 1 (central element)) elements is enough
    // We calculate the offset of the input grid by taking this simulation grid as the reference
    int offsetInput = LIMIT_VALUE_DAY_22_PART_1 / 2 + 1 - sizeInput / 2;
    PositiveCoordinates2D currentPosition;
    // We start at the middle of the grid
    currentPosition.x = LIMIT_VALUE_DAY_22_PART_1 / 2 + 1;
    currentPosition.y = LIMIT_VALUE_DAY_22_PART_1 / 2 + 1;
    int x = offsetInput, y = offsetInput, i, iteration, numberOfIterationsCausingInfection = 0;
    // One iteration contaminates one node max so the following number is way sufficient to store all the infected nodes
    // whatever the number of infected nodes in the input is
    int maxNumberOfInfectedNodesPossible = sizeInput * sizeInput + LIMIT_VALUE_DAY_22_PART_1;
    int numberOfReferencedNodes = 0;
    int keepReading = 1, currentPositionIsInfected = 0;
    int currentDirection = NORTH;
    // This variable will reference all the nodes that are or have been infected by the past
    // It will never reference a node that has never been infected
    Node * nodes;
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

        while (keepReading)
        {
            currentChar = fgetc(file);
            if (currentChar == INFECTED_NODE)
            {
                nodes[numberOfReferencedNodes].infected = 1;
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

        for (iteration = 0 ; iteration < LIMIT_VALUE_DAY_22_PART_1 ; iteration++)
        {
            currentPositionIsInfected = 0;
            for (i = 0 ; i < numberOfReferencedNodes && !currentPositionIsInfected ; i++)
            {
                if (nodes[i].infected && identicalPositiveCoordinates2D(nodes[i].coordinates, currentPosition))
                {
                    changeDirection(&currentDirection, TURN_RIGHT);
                    currentPositionIsInfected = 1;

                    // Due to step 2 of the algorithm
                    nodes[i].infected = 0;
                }
            }
            if (!currentPositionIsInfected)
            {
                changeDirection(&currentDirection, TURN_LEFT);
                // Due to step 2 of the algorithm
                numberOfIterationsCausingInfection++;
                nodes[numberOfReferencedNodes].infected = 1;
                nodes[numberOfReferencedNodes].coordinates.x = currentPosition.x;
                nodes[numberOfReferencedNodes].coordinates.y = currentPosition.y;
                numberOfReferencedNodes++;
            }
            moveOneNode(&currentPosition, currentDirection);
        }
        solution.solutionPart1 = numberOfIterationsCausingInfection;
        solution.solutionPart2 = 0;

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
            break;
        case SOUTH:
            if (turningDirection == TURN_LEFT)
                *currentDirection = EAST;
            else if (turningDirection == TURN_RIGHT)
                *currentDirection = WEST;
            break;
        case WEST:
            if (turningDirection == TURN_LEFT)
                *currentDirection = SOUTH;
            else if (turningDirection == TURN_RIGHT)
                *currentDirection = NORTH;
            break;
        case EAST:
        default:
            if (turningDirection == TURN_LEFT)
                *currentDirection = NORTH;
            else if (turningDirection == TURN_RIGHT)
                *currentDirection = SOUTH;
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

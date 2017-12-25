#include "day24.h"

SolutionIntegers getSolutionDay24(const char * inputFilePath)
{
    SolutionIntegers solution;
    solution.solutionPart1 = -1;
    solution.solutionPart2 = -1;

    int numberOfBricks = numberOfNonEmptyLines(inputFilePath), currentNumber = 0, currentLine = 0, i, maxStrength = 0;
    int keepReading = 1, readingFlag = 0;
    char currentChar;
    BridgeBrick * bricks;
    Stack *stack = initializeStack();

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        bricks = malloc(sizeof(BridgeBrick) * numberOfBricks);
        if (bricks == NULL)
        {
            printf("An error occurred because of limited memory\n");
            exit(EXIT_FAILURE);
        }

        while (keepReading)
        {
            currentChar = fgetc(file);
            if (currentChar == '/')
            {
                bricks[currentLine].port1 = currentNumber;
                currentNumber = 0;
                readingFlag = 1;
            }
            else if (isADigit(currentChar))
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else if (currentChar == '\n' || currentChar == EOF)
            {
                bricks[currentLine].port2 = currentNumber;
                bricks[currentLine].idBrick = currentLine;
                bricks[currentLine].port1isAvailable = 1;
                bricks[currentLine].port2isAvailable = 1;
                currentNumber = 0;
                currentLine++;
                readingFlag = 0;
                if (currentChar == EOF)
                    keepReading = 0;
            }
        }

        createBridge(stack, bricks, numberOfBricks, &maxStrength);
        solution.solutionPart1 = maxStrength;

        free(bricks);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

void createBridge(Stack *stack, BridgeBrick *bricks, int numberOfBricks, int * maxStrength)
{
    int currentPortNumber, currentTopId = NO_TOP_ID, i, removedId, previousPortNumber, currentStrength;
    if (getStackLength(stack) == 0)
        currentPortNumber = 0;
    else
    {
        currentTopId = pop(stack);
        if (bricks[currentTopId].port1isAvailable)
            currentPortNumber = bricks[currentTopId].port1;
        else if (bricks[currentTopId].port2isAvailable)
            currentPortNumber = bricks[currentTopId].port2;
        push(stack, currentTopId);
    }

    for (i = 0 ; i < numberOfBricks ; i++)
    {
        if (i != currentTopId)
        {
            if ((bricks[i].port1isAvailable && bricks[i].port2isAvailable)
                && (bricks[i].port1 == currentPortNumber || bricks[i].port2 == currentPortNumber))
            {
                if (currentTopId != NO_TOP_ID)
                {
                    bricks[currentTopId].port1isAvailable = 0;
                    bricks[currentTopId].port2isAvailable = 0;
                }
                push(stack, i);
                if (bricks[i].port1 == currentPortNumber)
                    bricks[i].port1isAvailable = 0;
                else
                    bricks[i].port2isAvailable = 0;
                createBridge(stack, bricks, numberOfBricks, maxStrength);
            }
        }
    }
    currentStrength = calculateBridgeStrength(stack, bricks);
    if (currentStrength > *maxStrength)
        *maxStrength = currentStrength;
    // displayStack(stack);
    // printf("Strength: %d\n", currentStrength);
    if (getStackLength(stack) > 0)
    {
        removedId = pop(stack);
        if (bricks[removedId].port1isAvailable == 1)
        {
            previousPortNumber = bricks[removedId].port2;
            bricks[removedId].port2isAvailable = 1;
        }
        else if (bricks[removedId].port2isAvailable == 1)
        {
            previousPortNumber = bricks[removedId].port1;
            bricks[removedId].port1isAvailable = 1;
        }
        if (getStackLength(stack) > 0)
        {
            currentTopId = pop(stack);
            if (bricks[currentTopId].port1 == previousPortNumber && bricks[currentTopId].port1isAvailable == 0)
                bricks[currentTopId].port1isAvailable = 1;
            else if (bricks[currentTopId].port2 == previousPortNumber && bricks[currentTopId].port2isAvailable == 0)
                bricks[currentTopId].port2isAvailable = 1;
            push(stack, currentTopId);
        }
    }
}

int calculateBridgeStrength(Stack * stack, BridgeBrick *bricks)
{
    StackElement *currentElement;
    int strength;

    if (getStackLength(stack) == 0)
        return 0;
    currentElement = stack->first;
    strength = bricks[currentElement->number].port1 + bricks[currentElement->number].port2;
    while (currentElement->next != NULL)
    {
        currentElement = currentElement->next;
        strength += bricks[currentElement->number].port1 + bricks[currentElement->number].port2;
    }
    return strength;
}

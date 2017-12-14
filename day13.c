#include "day13.h"

SolutionIntegers getSolutionDay13(const char * inputFilePath)
{
    SolutionIntegers solution;
    int keepReading = 1, stillOnLeftPart, notDetected = 1;
    char currentChar;
    int i, currentNumber = 0, maxNumber = 0, currentDepth = -1, currentPlayerLayer, tripSeverity = 0, delay, currentLayer;
    SecurityLayer* layers = NULL;
    FILE* file = NULL;

    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        stillOnLeftPart = 1;
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isADigit(currentChar) && stillOnLeftPart)
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else if (currentChar == ':')
            {
                stillOnLeftPart = 0;
            }
            else if (currentChar == '\n' || currentChar == EOF)
            {
                if(currentNumber > maxNumber)
                    maxNumber = currentNumber;
                currentNumber = 0;
                stillOnLeftPart = 1;
                if (currentChar == EOF)
                    keepReading = 0;
            }
        }
        printf("max is %d\n", maxNumber);
        layers = malloc((maxNumber + 1) * sizeof(SecurityLayer));
        if (layers == NULL)
        {
            printf("An error occurred because of limited memory\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0 ; i < maxNumber + 1 ; i++)
        {
            layers[i].range = 0;
        }
        rewind(file);
        stillOnLeftPart = 1;
        keepReading = 1;
        currentNumber = 0;
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isADigit(currentChar))
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else if (currentChar == ':')
            {
                currentDepth = currentNumber;
                currentNumber = 0;
                stillOnLeftPart = 0;
            }
            else if (currentChar == '\n' || currentChar == EOF)
            {
                layers[currentDepth].range = currentNumber;
                currentNumber = 0;
                stillOnLeftPart = 1;
                if (currentChar == EOF)
                    keepReading = 0;
            }
        }

        initializeSecurityScanners(layers, maxNumber + 1);
        // displayCurrentSecurityState(layers, maxNumber + 1);
        tripSeverity = 0;
        currentPlayerLayer = 0;
        while (currentPlayerLayer < maxNumber + 1)
        {
            if (layers[currentPlayerLayer].range > 0 && layers[currentPlayerLayer].indexScanner == 0)
            {
                layers[currentPlayerLayer].detectedPlayer = 1;
                tripSeverity += currentPlayerLayer * layers[currentPlayerLayer].range;
            }
            moveAllSecurityScanners(layers, maxNumber + 1, currentPlayerLayer);
            currentPlayerLayer++;
            // displayCurrentSecurityState(layers, maxNumber + 1);
        }
        solution.solutionPart1 = tripSeverity;

        // tripSeverity would be 0 even if detectedPlayer was true at layer 0 because of the formula so we have to check both
        if (tripSeverity == 0 && layers[0].detectedPlayer == 0)
            solution.solutionPart2 = 0;
        else
        {
            solution.solutionPart2 = INCORRECT_SOLUTION;
            delay = 1;
            while (solution.solutionPart2 == INCORRECT_SOLUTION)
            {
                if (delay % 1000 == 0)
                    printf("%d\n", delay);
                notDetected = 1;
                currentLayer = 0;
                while (currentLayer < maxNumber + 1 && notDetected)
                {
                    if (layers[currentLayer].range > 0 && indexScannerDependingOnRangeAndTime(layers[currentLayer].range, delay + currentLayer) == 0)
                        notDetected = 0;
                    currentLayer++;
                }
                if (notDetected)
                    solution.solutionPart2 = delay;
                else
                    delay++;
            }
        }

        free(layers);
        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

void displayCurrentSecurityState(const SecurityLayer * layers, int numberOfLayers)
{
    int i, j;
    for (i = 0 ; i < numberOfLayers ; i++)
    {
        printf("%d: ", i);
        for (j = 0 ; j < layers[i].range ; j++)
            if (j == layers[i].indexScanner)
                printf("[S]");
            else
                printf("[ ]");
        printf("\n");
    }
}

void initializeSecurityScanners(SecurityLayer * layers, int numberOfLayers)
{
    int i;
    for (i = 0 ; i < numberOfLayers ; i++)
    {
        layers[i].detectedPlayer = 0;
        layers[i].direction = DOWN;
        layers[i].indexScanner = 0;
    }
}

// There is no need to move scanners before the player position
void moveAllSecurityScanners(SecurityLayer * layers, int numberOfLayers, int currentPlayer)
{
    int i;
    for (i = currentPlayer ; i < numberOfLayers ; i++)
    {
        if (layers[i].range == 2)
            layers[i].indexScanner = 1 - layers[i].indexScanner;
        else if (layers[i].range > 2)
        {
            if (layers[i].direction == DOWN)
            {
                (layers[i].indexScanner)++;
                if (layers[i].indexScanner >= layers[i].range)
                {
                    layers[i].indexScanner -= 2;
                    layers[i].direction = UP;
                }
            }
            else if (layers[i].direction == UP)
            {
                (layers[i].indexScanner)--;
                if (layers[i].indexScanner < 0)
                {
                    layers[i].indexScanner += 2;
                    layers[i].direction = DOWN;
                }
            }
        }
    }
}

int indexScannerDependingOnRangeAndTime(int range, int time)
{
    int periodOfRange;
    int firstPeriodTimeIndex, associatedIndexScanner;
    int equivalentTimeInFirstPeriod;
    if (range == 1)
        return 0;
    if (range == 2)
        return time % 2;
    else
    {
        periodOfRange = 2 * (range - 1);
        equivalentTimeInFirstPeriod = time % periodOfRange;
        // We know it's the same value at time as the one at equivalentTimeInFirstPeriod
        // We found that at periodOfRange / 2 there is always the max value i.e. range - 1
        firstPeriodTimeIndex = periodOfRange / 2;
        associatedIndexScanner = range - 1;
        while (firstPeriodTimeIndex != equivalentTimeInFirstPeriod)
        {
            if (firstPeriodTimeIndex < equivalentTimeInFirstPeriod)
                firstPeriodTimeIndex++;
            else
                firstPeriodTimeIndex--;
            // We get further away from the center of the period in both cases (max value of scanner) so the value of the index scanner decreases
            associatedIndexScanner--;
        }
        return associatedIndexScanner;
    }
}

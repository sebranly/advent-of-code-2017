#include "day16.h"

SolutionStrings getSolutionDay16(const char * inputFilePath)
{
    SolutionStrings solution;
    int keepReading = 1;
    char currentChar, program1, program2;
    int position1, position2, iteration = 0, spinSize, iterationLimit;
    char programs[NUMBER_OF_LETTERS_DAY_16 + 1], command[DANCE_COMMAND_LENGTH], initialPrograms[NUMBER_OF_LETTERS_DAY_16 + 1];
    int currentIndex = 0;
    FILE* file = NULL;

    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        initializeAlphabeticalSequence(programs, NUMBER_OF_LETTERS_DAY_16);
        initializeAlphabeticalSequence(initialPrograms, NUMBER_OF_LETTERS_DAY_16);
        iterationLimit = DANCE_MAX_PERIOD;
        while (iteration < iterationLimit)
        {
            keepReading = 1;
            currentIndex = 0;
            rewind(file);
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (currentChar == ',' || currentChar == '\n' || currentChar == EOF)
                {
                    command[currentIndex] = '\0';
                    switch (command[0])
                    {
                        case 'x':
                            determineSwappedPositions(command, &position1, &position2);
                            swapValuesInString(programs, position1, position2);
                            break;
                        case 'p':
                            determineSwappedPrograms(command, &program1, &program2);
                            determineSwappedPositionsBasedOnSwapPrograms(programs, &position1, &position2, program1, program2);
                            swapValuesInString(programs, position1, position2);
                            break;
                        case 's':
                            spinSize = determineSpinSize(command);
                            spinString(programs, NUMBER_OF_LETTERS_DAY_16 + 1, spinSize);
                            break;
                        default:
                            break;
                    }
                    if (currentChar == '\n' || currentChar == EOF)
                        keepReading = 0;
                    else
                        currentIndex = 0;
                }
                else
                {
                    command[currentIndex] = currentChar;
                    currentIndex++;
                }
            }
            if (iteration == 0)
                strcpy(solution.solutionPart1, programs);
            if (sameStrings(programs, initialPrograms))
            {
                // We found the cycle so we just re-launch it with the appropriate number of iterations
                initializeAlphabeticalSequence(programs, NUMBER_OF_LETTERS_DAY_16);
                iterationLimit = NUMBER_OF_DANCES_PART_2 % (iteration + 1);
                iteration = 0;
            }
            else
                iteration++;
        }

        strcpy(solution.solutionPart2, programs);

        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

void determineSwappedPositions(const char * xCommand, int * position1, int * position2)
{
    int currentIndex = 1, currentNumber = 0;
    while (xCommand[currentIndex] != '\0')
    {
        if (isADigit(xCommand[currentIndex]))
        {
            currentNumber *= 10;
            currentNumber += toInteger(xCommand[currentIndex]);
        }
        else
        {
            *position1 = currentNumber;
            currentNumber = 0;
        }
        currentIndex++;
    }
    *position2 = currentNumber;
}

void determineSwappedPrograms(const char * pCommand, char * program1, char * program2)
{
    *program1 = pCommand[1];
    *program2 = pCommand[3];
}

void determineSwappedPositionsBasedOnSwapPrograms(const char * programs, int * position1, int * position2, char program1, char program2)
{
    *position1 = findFirstOccurrence(programs, program1);
    *position2 = findFirstOccurrence(programs, program2);
}

int determineSpinSize(const char * sCommand)
{
    int size = 0;
    int currentIndex = 1;
    while (sCommand[currentIndex] != '\0')
    {
        size *= 10;
        size += toInteger(sCommand[currentIndex]);
        currentIndex++;
    }
    return size;
}

#include "day21.h"

SolutionIntegers getSolutionDay21(const char * inputFilePath)
{
    SolutionIntegers solution;
    int keepReading = 1, beforeOutput = 1;
    int currentLine = 0;
    int x, y, i, j, combinationIndex, numberOfPatternRelations = numberOfNonEmptyLines(inputFilePath);
    int size = 3, iteration, numberOfCells;
    char currentChar;
    int occurrencesOfCombinations[NUMBER_OF_2_PER_2_INPUT_COMBINATIONS] = {0};
    PatternRelation * patternRelations;

    char **pattern;
    char **patternCopy;
    int maxPatternSize = 0;

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        // We determine the max size of the pattern array we need for the whole day challenge
        // Note: this is a workaround for part 2 as the part 2 needs a lot of iterations hence too many resources for the grid
        size = 2;
        iteration = 0;
        while (iteration < (LIMIT_VALUE_DAY_21_PART_2 - LIMIT_VALUE_DAY_21_PART_1))
        {
            if (size % 2 == 0)
                size = 3 * (size / 2);
            else if (size % 3 == 0)
                size = 4 * (size / 3);
            iteration++;
        }
        maxPatternSize = size;
        pattern = malloc(sizeof(*pattern) * maxPatternSize);
        for (i = 0 ; i < maxPatternSize ; i++)
            pattern[i] = malloc(sizeof(**pattern) * maxPatternSize);
        patternCopy = malloc(sizeof(*patternCopy) * maxPatternSize);
        for (i = 0 ; i < maxPatternSize ; i++)
            patternCopy[i] = malloc(sizeof(**patternCopy) * maxPatternSize);

        patternRelations = malloc(sizeof(*patternRelations) * numberOfPatternRelations);
        if (patternRelations == NULL)
        {
            printf("An error occurred because of memory limitation\n");
            exit(EXIT_FAILURE);
        }

        x = 0;
        y = 0;
        while (keepReading)
        {
            currentChar = fgetc(file);

            if (currentChar == NO_CELL || currentChar == CELL)
            {
                if (beforeOutput)
                    patternRelations[currentLine].inputPattern[x][y] = currentChar;
                else
                    patternRelations[currentLine].outputPattern[x][y] = currentChar;
                x++;
            }
            else if (currentChar == '>')
            {
                beforeOutput = 0;
                x = 0;
                y = 0;
            }
            else if (currentChar == '/')
            {
                y++;
                if (beforeOutput)
                    patternRelations[currentLine].sizeInput = x;
                else
                    patternRelations[currentLine].sizeOutput = x;
                x = 0;
            }
            else if (currentChar == '\n' || currentChar == EOF)
            {
                currentLine++;
                x = 0;
                y = 0;
                beforeOutput = 1;
                if (currentChar == EOF)
                    keepReading = 0;
            }
        }

        size = initializePattern(pattern);
        size = evolvePatternOverGenerations(pattern, patternCopy, size, patternRelations, numberOfPatternRelations, LIMIT_VALUE_DAY_21_PART_1);

        solution.solutionPart1 = 0;
        for (i = 0 ; i < size ; i++)
            for (j = 0 ; j < size ; j++)
                if (pattern[i][j] == CELL)
                    (solution.solutionPart1)++;

        // We take a look at the shape of the final grid by dividing it into a lot of elementary 2x2 grids
        for (i = 0 ; i < size ; i += 2)
            for (j = 0 ; j < size ; j += 2)
                occurrencesOfCombinations[get2Per2Combination(pattern, i, j)]++;

        solution.solutionPart2 = 0;
        // We make each type of 2x2 grid evolve from part 1's iteration to part 2's iteration
        for (combinationIndex = 0 ; combinationIndex < NUMBER_OF_2_PER_2_INPUT_COMBINATIONS ; combinationIndex++)
        {
            if (occurrencesOfCombinations[combinationIndex] > 0)
            {
                size = initialize2Per2Pattern(pattern, combinationIndex);
                size = evolvePatternOverGenerations(pattern, patternCopy, size, patternRelations, numberOfPatternRelations, LIMIT_VALUE_DAY_21_PART_2 - LIMIT_VALUE_DAY_21_PART_1);
                numberOfCells = 0;
                for (i = 0 ; i < size ; i++)
                    for (j = 0 ; j < size ; j++)
                        if (pattern[i][j] == CELL)
                            numberOfCells++;
                solution.solutionPart2 += occurrencesOfCombinations[combinationIndex] * numberOfCells;
            }
        }

        for (i = 0 ; i < maxPatternSize ; i++)
            free(pattern[i]);
        free(pattern);

        for (i = 0 ; i < maxPatternSize ; i++)
            free(patternCopy[i]);
        free(patternCopy);

        free(patternRelations);

        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

int initializePattern(char **pattern)
{
    pattern[0][0] = NO_CELL;
    pattern[1][0] = CELL;
    pattern[2][0] = NO_CELL;

    pattern[0][1] = NO_CELL;
    pattern[1][1] = NO_CELL;
    pattern[2][1] = CELL;

    pattern[0][2] = CELL;
    pattern[1][2] = CELL;
    pattern[2][2] = CELL;

    return 3;
}

int initialize2Per2Pattern(char ** pattern, int combinationOf2Per2)
{
    int i, j;
    switch (combinationOf2Per2)
    {
        case ZERO_CELLS:
            for (i = 0 ; i < 2 ; i++)
                for (j = 0 ; j < 2 ; j++)
                    pattern[i][j] = NO_CELL;
            break;

        case ONE_CELL:
            for (i = 0 ; i < 2 ; i++)
                for (j = 0 ; j < 2 ; j++)
                    pattern[i][j] = NO_CELL;
            pattern[0][0] = CELL;
            break;

        case TWO_DIAGONAL_CELLS:
            pattern[0][0] = NO_CELL;
            pattern[0][1] = CELL;
            pattern[1][0] = CELL;
            pattern[1][1] = NO_CELL;
            break;

        case TWO_ADJACENT_CELLS:
            pattern[0][0] = CELL;
            pattern[0][1] = CELL;
            pattern[1][0] = NO_CELL;
            pattern[1][1] = NO_CELL;
            break;

        case THREE_CELLS:
            for (i = 0 ; i < 2 ; i++)
                for (j = 0 ; j < 2 ; j++)
                    pattern[i][j] = CELL;
            pattern[0][0] = NO_CELL;
            break;

        case FOUR_CELLS:
            for (i = 0 ; i < 2 ; i++)
                for (j = 0 ; j < 2 ; j++)
                    pattern[i][j] = CELL;
            break;
    }
    return 2;
}

// Only focuses on a 2x2 portion of the pattern grid
int get2Per2Combination(char **pattern, int startingX, int startingY)
{
    int i, j, numberOfCells = 0;
    for (i = 0 ; i < 2 ; i++)
        for (j = 0 ; j < 2 ; j++)
            if (pattern[startingX + i][startingY + j] == CELL)
                numberOfCells++;

    switch (numberOfCells)
    {
        case 0:
            return ZERO_CELLS;
            break;
        case 1:
            return ONE_CELL;
            break;
        case 2:
            if ((pattern[startingX][startingY] == CELL && pattern[startingX + 1][startingY + 1] == CELL)
                || (pattern[startingX + 1][startingY] == CELL && pattern[startingX][startingY + 1] == CELL))
                return TWO_DIAGONAL_CELLS;
            return TWO_ADJACENT_CELLS;
            break;
        case 3:
            return THREE_CELLS;
            break;
        case 4:
        default:
            return FOUR_CELLS;
            break;
    }
}

int evolvePatternOverGenerations(char **pattern, char **patternCopy, int sizePatternInput, PatternRelation * patternRelations, int numberOfPatternRelations, int numberOfGenerations)
{
    int iterationDone;
    int numberOfBlocks = 0, numberOfBlocksX = 0, numberOfBlocksY = 0, iteration = 0, sizePatternOutput, divisor = 0, i, j;
    char patternInput[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE];
    char patternOutput[MAX_OUTPUT_PATTERN_SIZE][MAX_OUTPUT_PATTERN_SIZE];

    while (iteration < numberOfGenerations)
    {
        iterationDone = 0;
        for (divisor = 2 ; divisor <= 3 && !iterationDone ; divisor++)
        {
            if (sizePatternInput % divisor == 0)
            {
                sizePatternOutput = (divisor + 1) * (sizePatternInput / divisor);
                numberOfBlocks = (sizePatternInput / divisor);
                for (numberOfBlocksX = numberOfBlocks - 1 ; numberOfBlocksX >= 0 ; numberOfBlocksX--)
                {
                    for (numberOfBlocksY = numberOfBlocks - 1 ; numberOfBlocksY >= 0 ; numberOfBlocksY--)
                    {
                        for (i = 0 ; i < divisor ; i++)
                            for (j = 0 ; j < divisor ; j++)
                                 patternInput[i][j] = pattern[numberOfBlocksX * divisor + i][numberOfBlocksY * divisor + j];

                        determineOutputPatternBasedOnInputPattern(patternInput, patternOutput, patternRelations, numberOfPatternRelations, divisor);

                        for (i = 0 ; i < divisor + 1 ; i++)
                            for (j = 0 ; j < divisor + 1 ; j++)
                                patternCopy[numberOfBlocksX * (divisor + 1) + i][numberOfBlocksY * (divisor + 1) + j] = patternOutput[i][j];
                    }
                }

                for (i = 0 ; i < sizePatternOutput ; i++)
                    for(j = 0 ; j < sizePatternOutput ; j++)
                        pattern[i][j] = patternCopy[i][j];

                sizePatternInput = sizePatternOutput;
                iterationDone = 1;
            }
        }

        iteration++;
    }
    return sizePatternInput;
}

void determineOutputPatternBasedOnInputPattern(char inputPattern[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], char outputPattern[MAX_OUTPUT_PATTERN_SIZE][MAX_OUTPUT_PATTERN_SIZE], PatternRelation * patternRelations, int numberOfPatternRelations, int inputPatternSize)
{
    int i = 0;
    while (i < numberOfPatternRelations)
    {
        // We skip this pattern relation if it's 3x3 but the element in the center is not the same for both matrices
        // Indeed the transformations do not affect the central element so it's a good indicator of if we should go further
        if ((patternRelations[i].sizeInput == inputPatternSize) && (inputPatternSize == 2 || (inputPatternSize == 3 && patternRelations[i].inputPattern[1][1] == inputPattern[1][1])))
        {
            // TBD: reduce the number of transformations by keeping a complete verification of pattern-matching though
            if (identicalArray2D(patternRelations[i].inputPattern, inputPattern, inputPatternSize))
                break;
            flipArray2D(patternRelations[i].inputPattern, inputPatternSize);
            if (identicalArray2D(patternRelations[i].inputPattern, inputPattern, inputPatternSize))
                break;
            flipArray2D(patternRelations[i].inputPattern, inputPatternSize);
            rotate90DegreesArray2D(patternRelations[i].inputPattern, inputPatternSize);
            if (identicalArray2D(patternRelations[i].inputPattern, inputPattern, inputPatternSize))
                break;
            flipArray2D(patternRelations[i].inputPattern, inputPatternSize);
            if (identicalArray2D(patternRelations[i].inputPattern, inputPattern, inputPatternSize))
                break;
            flipArray2D(patternRelations[i].inputPattern, inputPatternSize);
            rotate90DegreesArray2D(patternRelations[i].inputPattern, inputPatternSize);
            if (identicalArray2D(patternRelations[i].inputPattern, inputPattern, inputPatternSize))
                break;
            flipArray2D(patternRelations[i].inputPattern, inputPatternSize);
            if (identicalArray2D(patternRelations[i].inputPattern, inputPattern, inputPatternSize))
                break;
            flipArray2D(patternRelations[i].inputPattern, inputPatternSize);
            rotate90DegreesArray2D(patternRelations[i].inputPattern, inputPatternSize);
            if (identicalArray2D(patternRelations[i].inputPattern, inputPattern, inputPatternSize))
                break;
            flipArray2D(patternRelations[i].inputPattern, inputPatternSize);
            if (identicalArray2D(patternRelations[i].inputPattern, inputPattern, inputPatternSize))
                break;
            flipArray2D(patternRelations[i].inputPattern, inputPatternSize);
        }
        i++;
    }
    copyOutputArray2D(outputPattern, patternRelations[i].outputPattern,  patternRelations[i].sizeOutput);
}

int identicalArray2D(char a[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], char b[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], int size)
{
    int i, j;
    for (i = 0 ; i < size ; i++)
        for (j = 0 ; j < size ; j++)
            if (a[i][j] != b[i][j])
                return 0;
    return 1;
}

void flipArray2D(char a[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], int size)
{
    int i, j;
    char b[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE];
    for (i = 0 ; i < size ; i++)
        for (j = 0 ; j < size ; j++)
            b[i][j] = a[size - 1 - i][j];
    copyInputArray2D(a, b, size);
}

void rotate90DegreesArray2D(char a[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], int size)
{
    int i, j;
    char b[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE];
    for (i = 0 ; i < size ; i++)
        for (j = 0 ; j < size ; j++)
            b[i][j] = a[size - j - 1][i];
    copyInputArray2D(a, b, size);
}

void copyInputArray2D(char destination[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], char source[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], int size)
{
    int i, j;
    for (i = 0 ; i < size ; i++)
        for (j = 0 ; j < size ; j++)
            destination[i][j] = source[i][j];
}

void copyOutputArray2D(char destination[MAX_OUTPUT_PATTERN_SIZE][MAX_OUTPUT_PATTERN_SIZE], char source[MAX_OUTPUT_PATTERN_SIZE][MAX_OUTPUT_PATTERN_SIZE], int size)
{
    int i, j;
    for (i = 0 ; i < size ; i++)
        for (j = 0 ; j < size ; j++)
            destination[i][j] = source[i][j];
}

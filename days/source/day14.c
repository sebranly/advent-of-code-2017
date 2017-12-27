#include "../header/day14.h"

SolutionIntegers getSolutionDay14(const char * inputFilePath)
{
    SolutionIntegers solution;
    char input[SHORT_STRING_LENGTH], inputWithNumber[SHORT_STRING_LENGTH], bits[BITS_STRING_LENGTH];
    int i, rowNumber, usedSquares = 0;
    int grid[GRID_SIZE][GRID_SIZE];
    KnotHashElements knotHashElements;

    readUniqueLine(inputFilePath, input, SHORT_STRING_LENGTH);
    for (rowNumber = 0 ; rowNumber < GRID_SIZE ; rowNumber++)
    {
        sprintf(inputWithNumber, "%s-%d", input, rowNumber);
        determineFinalKnotHashString(inputWithNumber, &knotHashElements);
        hexadecimalStringToBitsString(knotHashElements.finalKnotHash, bits);
        for (i = 0 ; i < GRID_SIZE ; i++)
            if (bits[i] == '1')
            {
                // In order to avoid confusion later, we turn all 1 into -1 for part 2
                grid[rowNumber][i] = -1;
                usedSquares++;
            }
            else
                grid[rowNumber][i] = 0;
    }

    solution.solutionPart1 = usedSquares;
    solution.solutionPart2 = determineGroups(grid);

    return solution;
}

int determineGroups(int grid[GRID_SIZE][GRID_SIZE])
{
    int i, j, maxGroupId = 0, newGroupId;
    for (i = 0 ; i < GRID_SIZE ; i++)
        for (j = 0 ; j < GRID_SIZE ; j++)
            if (grid[i][j] == -1)
            {
                newGroupId = sprayOneGroup(grid, i, j, maxGroupId, 1);
                if (newGroupId > maxGroupId)
                    maxGroupId = newGroupId;
            }
    return maxGroupId;
}

int sprayOneGroup(int grid[GRID_SIZE][GRID_SIZE], int x, int y, int maxGroupId, int fromCoreFunction)
{
    if (grid[x][y] == -1)
    {
        if (fromCoreFunction)
            maxGroupId++;
        grid[x][y] = maxGroupId;
        if (x - 1 >= 0)
            sprayOneGroup(grid, x - 1, y, maxGroupId, 0);
        if (y - 1 >= 0)
            sprayOneGroup(grid, x, y - 1, maxGroupId, 0);
        if (x + 1 < GRID_SIZE)
            sprayOneGroup(grid, x + 1, y, maxGroupId, 0);
        if (y + 1 < GRID_SIZE)
            sprayOneGroup(grid, x, y + 1, maxGroupId, 0);
        return maxGroupId;
    }
    else
        return 0;
}

void hexadecimalStringToBitsString(const char * hexadecimalString, char * bitsString)
{
    int i, j;
    // Not a general case, this is hardcoded for this specific example regarding lengths and sizes
    char bits[4];
    for (i = 0 ; i < 32 ; i++)
    {
        switch (hexadecimalString[i])
        {
            case '0':
            strcpy(bits, "0000");
                break;
            case '1':
            strcpy(bits, "0001");
                break;
            case '2':
            strcpy(bits, "0010");
                break;
            case '3':
            strcpy(bits, "0011");
                break;
            case '4':
            strcpy(bits, "0100");
                break;
            case '5':
            strcpy(bits, "0101");
                break;
            case '6':
            strcpy(bits, "0110");
                break;
            case '7':
            strcpy(bits, "0111");
                break;
            case '8':
            strcpy(bits, "1000");
                break;
            case '9':
            strcpy(bits, "1001");
                break;
            case 'a':
            strcpy(bits, "1010");
                break;
            case 'b':
            strcpy(bits, "1011");
                break;
            case 'c':
            strcpy(bits, "1100");
                break;
            case 'd':
            strcpy(bits, "1101");
                break;
            case 'e':
            strcpy(bits, "1110");
                break;
            case 'f':
            default:
            strcpy(bits, "1111");
                break;
        }
        for (j = 0 ; j < 4 ; j++)
            bitsString[i * 4 + j] = bits[j];
    }
    bitsString[128] = '\0';
}

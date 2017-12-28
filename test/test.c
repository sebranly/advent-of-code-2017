#include "test.h"

// Returns 1 only if the whole test suite is successful, 0 otherwise
int runTestSuite(void)
{
    int allResultsAreCorrect = 1;
    int currentDay, currentDayTest;
    char fileName[50];

    SolutionIntegers solutionIntegers, expectedSolutionIntegers;
    SolutionIntegerString solutionIntegerString, expectedSolutionIntegerString;
    SolutionStringInteger solutionStringInteger, expectedSolutionStringInteger;
    SolutionStrings solutionStrings, expectedSolutionStrings;

    currentDayTest = 1;

    for (currentDay = 1 ; currentDay <= 25 ; currentDay++)
    {
        // TBD - once solution for day 22 is fast enough, remove this exception
        if (getSolutionType(currentDay) == INTEGERS && currentDay != 22)
        {
            printf("Checking the code for day %02d...\n", currentDay);

            sprintf(fileName, "test/days/%02d/part1-%03d.txt", currentDay, currentDayTest);
            expectedSolutionIntegers.solutionPart1 = readUniqueNumber(fileName);
            sprintf(fileName, "test/days/%02d/part2-%03d.txt", currentDay, currentDayTest);
            expectedSolutionIntegers.solutionPart2 = readUniqueNumber(fileName);

            sprintf(fileName, "test/days/%02d/input-%03d.txt", currentDay, currentDayTest);
            solutionIntegers = getSolutionIntegersDay(fileName, currentDay);

            allResultsAreCorrect = min(allResultsAreCorrect, compareSolutionIntegers(expectedSolutionIntegers, solutionIntegers, currentDay, currentDayTest));
        }
    }

    return allResultsAreCorrect;
}

int getSolutionType(int currentDay)
{
    if (currentDay == 7 || currentDay == 19)
        return STRING_INTEGER;
    if (currentDay == 10)
        return INTEGER_STRING;
    if (currentDay == 16)
        return STRINGS;
    if (currentDay == 25)
        return INTEGER;
    return INTEGERS;
}

int compareSolutionIntegers(SolutionIntegers expected, SolutionIntegers actual, int currentDay, int currentDayTest)
{
    int bothTestsAreCorrect = 1;
    if (expected.solutionPart1 != actual.solutionPart1)
    {
        printf("Day %02d, test %03d: expected %d but got %d\n", currentDay, currentDayTest, expected.solutionPart1, actual.solutionPart1);
        bothTestsAreCorrect = 0;
    }
    if (expected.solutionPart2 != actual.solutionPart2)
    {
        printf("Day %02d, test %03d: expected %d but got %d\n", currentDay, currentDayTest, expected.solutionPart2, actual.solutionPart2);
        bothTestsAreCorrect = 0;
    }
    return bothTestsAreCorrect;
}

SolutionIntegers getSolutionIntegersDay(const char * inputFilePath, int currentDay)
{
    SolutionIntegers solution;
    solution.solutionPart1 = 0;
    solution.solutionPart2 = 0;

    switch (currentDay)
    {
        case 1:
            return getSolutionDay01(inputFilePath);
        case 2:
            return getSolutionDay02(inputFilePath);
        case 3:
            return getSolutionDay03(inputFilePath);
        case 4:
            return getSolutionDay04(inputFilePath);
        case 5:
            return getSolutionDay05(inputFilePath);
        case 6:
            return getSolutionDay06(inputFilePath);
        case 8:
            return getSolutionDay08(inputFilePath);
        case 9:
            return getSolutionDay09(inputFilePath);
        case 11:
            return getSolutionDay11(inputFilePath);
        case 12:
            return getSolutionDay12(inputFilePath);
        case 13:
            return getSolutionDay13(inputFilePath);
        case 14:
            return getSolutionDay14(inputFilePath);
        case 15:
            return getSolutionDay15(inputFilePath);
        case 17:
            return getSolutionDay17(inputFilePath);
        case 18:
            return getSolutionDay18(inputFilePath);
        case 20:
            return getSolutionDay20(inputFilePath);
        case 21:
            return getSolutionDay21(inputFilePath);
        case 22:
            return getSolutionDay22(inputFilePath);
        case 23:
            return getSolutionDay23(inputFilePath);
        case 24:
            return getSolutionDay24(inputFilePath);
        default:
            return solution;
    }
}

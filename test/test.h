#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "../other/header/allDays.h"
#include "../other/header/solutionTypes.h"
#include "../other/header/fileLibrary.h"
#include "../other/header/mathLibrary.h"

enum { INTEGERS, STRINGS, INTEGER_STRING, STRING_INTEGER, INTEGER };

int runTestSuite(void);
int compareSolutionIntegers(SolutionIntegers expected, SolutionIntegers actual, int currentDay, int currentDayTest);
SolutionIntegers getSolutionIntegersDay(const char * inputFilePath, int currentDay);
int getSolutionType(int currentDay);

#endif // TEST_H_INCLUDED

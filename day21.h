#ifndef DAY21_H_INCLUDED
#define DAY21_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "solutionTypes.h"
#include "fileLibrary.h"

#define LIMIT_VALUE_DAY_21_PART_1 5
#define LIMIT_VALUE_DAY_21_PART_2 18
#define MAX_INPUT_PATTERN_SIZE 3
#define MAX_OUTPUT_PATTERN_SIZE 4

typedef struct PatternRelation PatternRelation;
struct PatternRelation
{
    int sizeInput;
    int sizeOutput;
    char inputPattern[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE];
    char outputPattern[MAX_OUTPUT_PATTERN_SIZE][MAX_OUTPUT_PATTERN_SIZE];
};

SolutionIntegers getSolutionDay21(const char * inputFilePath);
void initializePattern(char **pattern);
int evolvePatternOverGenerations(char **pattern, char **patternCopy, int sizePattern, PatternRelation * patternRelations, int numberOfPatternRelations, int numberOfGenerations);
void determineOutputPatternBasedOnInputPattern(char inputPattern[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], char outputPattern[MAX_OUTPUT_PATTERN_SIZE][MAX_OUTPUT_PATTERN_SIZE], PatternRelation * patternRelations, int numberOfPatternRelations, int inputPatternSize);
int identicalArray2D(char a[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], char b[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], int size);
void flipArray2D(char a[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], int size);
void rotate90DegreesArray2D(char a[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], int size);
void copyInputArray2D(char destination[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], char source[MAX_INPUT_PATTERN_SIZE][MAX_INPUT_PATTERN_SIZE], int size);
void copyOutputArray2D(char destination[MAX_OUTPUT_PATTERN_SIZE][MAX_OUTPUT_PATTERN_SIZE], char source[MAX_OUTPUT_PATTERN_SIZE][MAX_OUTPUT_PATTERN_SIZE], int size);

#endif // DAY21_H_INCLUDED

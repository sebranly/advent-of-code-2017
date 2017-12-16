#ifndef SOLUTIONTYPES_H_INCLUDED
#define SOLUTIONTYPES_H_INCLUDED

#define SOLUTION_STRING_SIZE 100

typedef struct SolutionIntegers SolutionIntegers;
struct SolutionIntegers
{
    int solutionPart1;
    int solutionPart2;
};

typedef struct SolutionStrings SolutionStrings;
struct SolutionStrings
{
    char solutionPart1[SOLUTION_STRING_SIZE];
    char solutionPart2[SOLUTION_STRING_SIZE];
};

typedef struct SolutionIntegerString SolutionIntegerString;
struct SolutionIntegerString
{
    int solutionPart1;
    char solutionPart2[SOLUTION_STRING_SIZE];
};

#endif // SOLUTIONTYPES_H_INCLUDED

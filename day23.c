#include "day23.h"

SolutionIntegers getSolutionDay23(const char * inputFilePath)
{
    SolutionIntegers solution;
    solution.solutionPart1 = -1;
    solution.solutionPart2 = -1;

    DuetAssemblyCode assemblyCode;
    int i;

    assemblyCode.numberOfInstructions = numberOfNonEmptyLines(inputFilePath);
    assemblyCode.instructions = malloc(sizeof(*(assemblyCode.instructions)) * assemblyCode.numberOfInstructions);
    for (i = 0 ; i < assemblyCode.numberOfInstructions ; i++)
        assemblyCode.instructions[i] = malloc(sizeof(**(assemblyCode.instructions)) * INSTRUCTION_STRING_LENGTH);

    initializeDuetAssemblyCode(&assemblyCode, 0);
    fillDuetAssemblyCodeInstructions(assemblyCode, inputFilePath);

    while (valueIsBetween(assemblyCode.currentInstructionIndex, 0, assemblyCode.numberOfInstructions - 1))
        executeDuetAssemblyCodeInstruction(&assemblyCode, NULL, 1);

    solution.solutionPart1 = assemblyCode.counterMul;

    for (i = 0 ; i < assemblyCode.numberOfInstructions ; i++)
        free(assemblyCode.instructions[i]);
    free(assemblyCode.instructions);

    return solution;
}

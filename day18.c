#include "day18.h"

SolutionIntegers getSolutionDay18(const char * inputFilePath)
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

    initializeDuetAssemblyCode(&assemblyCode);
    fillDuetAssemblyCodeInstructions(assemblyCode, inputFilePath);
    displayDuetAssemblyCodeInstructions(assemblyCode);
    printf("There are %d instructions, the first one is <%s> and the last one is <%s>\n", assemblyCode.numberOfInstructions, assemblyCode.instructions[0], assemblyCode.instructions[assemblyCode.numberOfInstructions - 1]);

    while(!assemblyCode.recoverOperationExecuted && valueIsBetween(assemblyCode.currentInstructionIndex, 0, assemblyCode.numberOfInstructions - 1))
    {
        executeDuetAssemblyCodeInstruction(&assemblyCode);
    }

    if (assemblyCode.recoverOperationExecuted)
        solution.solutionPart1 = assemblyCode.frequencyLastSoundPlayed;

    for (i = 0 ; i < assemblyCode.numberOfInstructions ; i++)
        free(assemblyCode.instructions[i]);
    free(assemblyCode.instructions);

    return solution;
}

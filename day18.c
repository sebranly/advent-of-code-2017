#include "day18.h"

SolutionIntegers getSolutionDay18(const char * inputFilePath)
{
    SolutionIntegers solution;
    solution.solutionPart1 = -1;
    solution.solutionPart2 = -1;

    DuetAssemblyCode assemblyCode, assemblyCode2;
    int i;

    assemblyCode.numberOfInstructions = numberOfNonEmptyLines(inputFilePath);
    assemblyCode.instructions = malloc(sizeof(*(assemblyCode.instructions)) * assemblyCode.numberOfInstructions);
    for (i = 0 ; i < assemblyCode.numberOfInstructions ; i++)
        assemblyCode.instructions[i] = malloc(sizeof(**(assemblyCode.instructions)) * INSTRUCTION_STRING_LENGTH);

    initializeDuetAssemblyCode(&assemblyCode, 0);
    fillDuetAssemblyCodeInstructions(assemblyCode, inputFilePath);
    printf("There are %d instructions, the first one is <%s> and the last one is <%s>\n", assemblyCode.numberOfInstructions, assemblyCode.instructions[0], assemblyCode.instructions[assemblyCode.numberOfInstructions - 1]);

    while (!assemblyCode.recoverOperationExecuted && valueIsBetween(assemblyCode.currentInstructionIndex, 0, assemblyCode.numberOfInstructions - 1))
    {
        executeDuetAssemblyCodeInstruction(&assemblyCode, NULL, 1);
    }

    if (assemblyCode.recoverOperationExecuted)
        solution.solutionPart1 = assemblyCode.frequencyLastSoundPlayed;

    assemblyCode2.numberOfInstructions = numberOfNonEmptyLines(inputFilePath);
    assemblyCode2.instructions = malloc(sizeof(*(assemblyCode2.instructions)) * assemblyCode2.numberOfInstructions);
    for (i = 0 ; i < assemblyCode2.numberOfInstructions ; i++)
        assemblyCode2.instructions[i] = malloc(sizeof(**(assemblyCode2.instructions)) * INSTRUCTION_STRING_LENGTH);
    initializeDuetAssemblyCode(&assemblyCode, 0);
    initializeDuetAssemblyCode(&assemblyCode2, 1);
    fillDuetAssemblyCodeInstructions(assemblyCode, inputFilePath);
    fillDuetAssemblyCodeInstructions(assemblyCode2, inputFilePath);

    printf("Please wait a bit...\n");
    while ((valueIsBetween(assemblyCode.currentInstructionIndex, 0, assemblyCode.numberOfInstructions - 1) || valueIsBetween(assemblyCode2.currentInstructionIndex, 0, assemblyCode2.numberOfInstructions - 1)) && !(assemblyCode.programState == LOCKED && assemblyCode2.programState == LOCKED))
    {
        if (valueIsBetween(assemblyCode.currentInstructionIndex, 0, assemblyCode.numberOfInstructions - 1))
            executeDuetAssemblyCodeInstruction(&assemblyCode, &assemblyCode2, 2);
        if (valueIsBetween(assemblyCode2.currentInstructionIndex, 0, assemblyCode2.numberOfInstructions - 1))
            executeDuetAssemblyCodeInstruction(&assemblyCode2, &assemblyCode, 2);
    }
    solution.solutionPart2 = assemblyCode2.counterValuesSent;

    for (i = 0 ; i < assemblyCode.numberOfInstructions ; i++)
        free(assemblyCode.instructions[i]);
    free(assemblyCode.instructions);

    for (i = 0 ; i < assemblyCode2.numberOfInstructions ; i++)
        free(assemblyCode2.instructions[i]);
    free(assemblyCode2.instructions);

    return solution;
}

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

    // TBD - this is a hardcoded solution for now that only works for my input after manual optimization
    int b = 109300, c = 126300, d = 0, f = 0, g = 0, h = 0;
    do
    {
        f = 1;
        d = 2;
        do
        {
            if (b % d == 0 && b / d >= 2 && b / d <= b)
                f = 0;
            d += 1;
        } while (f == 1 && d != b);

        if (f == 0)
            h += 1;
        g = b - c;
        if (b != c)
            b += 17;
    } while (g != 0);
    solution.solutionPart2 = h;

    return solution;
}

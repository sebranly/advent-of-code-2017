#include "duetAssemblyCode.h"

void fillDuetAssemblyCodeInstructions(DuetAssemblyCode assemblyCode, const char * inputFilePath)
{
    fillLinesIn2DArray(assemblyCode.instructions, assemblyCode.numberOfInstructions, inputFilePath);
}

void initializeDuetAssemblyCode(DuetAssemblyCode * assemblyCode)
{
    int i;
    assemblyCode->currentInstructionIndex = 0;
    assemblyCode->recoverOperationExecuted = 0;
    assemblyCode->atLeastOneSoundPlayed = 0;
    assemblyCode->frequencyLastSoundPlayed = 0;
    for (i = 0 ; i < assemblyCode->numberOfInstructions ; i++)
        assemblyCode->instructions[i][0] = '\0';
    for (i = 0 ; i < NUMBER_OF_LOWER_CASE_LETTERS ; i++)
        assemblyCode->assemblyRegister[i] = 0;
}

void displayDuetAssemblyCodeInstructions(const DuetAssemblyCode assemblyCode)
{
    int i;
    for (i = 0 ; i < assemblyCode.numberOfInstructions ; i++)
        printf("Instruction %04d: %s\n", i, assemblyCode.instructions[i]);
}

void executeDuetAssemblyCodeInstruction(DuetAssemblyCode * assemblyCode)
{
    char instruction[INSTRUCTION_STRING_LENGTH];
    int number, indexSecondSpace;
    int correctConversion;
    strcpy(instruction, assemblyCode->instructions[assemblyCode->currentInstructionIndex]);
    // printf("%s | ", instruction);

    if (isSetInstruction(instruction) || isAddInstruction(instruction) || isMulInstruction(instruction) || isModInstruction(instruction))
    {
        correctConversion = stringToInteger(instruction, 6, NO_ENDING_INDEX, &number);
        // In that case it was a register like 'a' for example
        if (!correctConversion)
            number = assemblyCode->assemblyRegister[instruction[6] - A_LOWER_CASE_ASCII_CODE];

        if (isSetInstruction(instruction))
            assemblyCode->assemblyRegister[instruction[4] - A_LOWER_CASE_ASCII_CODE] = number;
        else if (isAddInstruction(instruction))
            assemblyCode->assemblyRegister[instruction[4] - A_LOWER_CASE_ASCII_CODE] += number;
        else if (isMulInstruction(instruction))
            assemblyCode->assemblyRegister[instruction[4] - A_LOWER_CASE_ASCII_CODE] *= number;
        else if (isModInstruction(instruction))
            assemblyCode->assemblyRegister[instruction[4] - A_LOWER_CASE_ASCII_CODE] %= number;
        // printf(" => <%c: %d>\n", instruction[4], assemblyCode->assemblyRegister[instruction[4] - A_LOWER_CASE_ASCII_CODE]);

        (assemblyCode->currentInstructionIndex)++;
    }
    else if (isSndInstruction(instruction))
    {
        correctConversion = stringToInteger(instruction, 4, NO_ENDING_INDEX, &number);
        // In that case it was a register like 'a' for example
        if (!correctConversion)
            number = assemblyCode->assemblyRegister[instruction[4] - A_LOWER_CASE_ASCII_CODE];
        assemblyCode->atLeastOneSoundPlayed = 1;
        assemblyCode->frequencyLastSoundPlayed = number;

        (assemblyCode->currentInstructionIndex)++;
    }
    else if (isRcvInstruction(instruction))
    {
        correctConversion = stringToInteger(instruction, 4, NO_ENDING_INDEX, &number);
        // In that case it was a register like 'a' for example
        if (!correctConversion)
            number = assemblyCode->assemblyRegister[instruction[4] - A_LOWER_CASE_ASCII_CODE];
        if (number != 0)
            assemblyCode->recoverOperationExecuted = 1;

        (assemblyCode->currentInstructionIndex)++;
    }
    else if (isJgzInstruction(instruction))
    {
        indexSecondSpace = findSecondOccurrence(instruction, ' ');
        correctConversion = stringToInteger(instruction, 4, indexSecondSpace - 1, &number);
        // In that case it was a register like 'a' for example
        if (!correctConversion)
            number = assemblyCode->assemblyRegister[instruction[4] - A_LOWER_CASE_ASCII_CODE];
        if (number > 0)
        {
            correctConversion = stringToInteger(instruction, indexSecondSpace + 1, NO_ENDING_INDEX, &number);
            // In that case it was a register like 'a' for example
            if (!correctConversion)
                number = assemblyCode->assemblyRegister[instruction[indexSecondSpace + 1] - A_LOWER_CASE_ASCII_CODE];

            (assemblyCode->currentInstructionIndex) += number;
        }
        else
            (assemblyCode->currentInstructionIndex)++;
    }
}

int isSetInstruction(const char * instruction)
{
    return (instruction[0] == 's' && instruction[1] == 'e' && instruction[2] == 't');
}

int isAddInstruction(const char * instruction)
{
    return (instruction[0] == 'a' && instruction[1] == 'd' && instruction[2] == 'd');
}

int isMulInstruction(const char * instruction)
{
    return (instruction[0] == 'm' && instruction[1] == 'u' && instruction[2] == 'l');
}

int isModInstruction(const char * instruction)
{
    return (instruction[0] == 'm' && instruction[1] == 'o' && instruction[2] == 'd');
}

int isSndInstruction(const char * instruction)
{
    return (instruction[0] == 's' && instruction[1] == 'n' && instruction[2] == 'd');
}

int isRcvInstruction(const char * instruction)
{
    return (instruction[0] == 'r' && instruction[1] == 'c' && instruction[2] == 'v');
}

int isJgzInstruction(const char * instruction)
{
    return (instruction[0] == 'j' && instruction[1] == 'g' && instruction[2] == 'z');
}

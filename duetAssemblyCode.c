#include "duetAssemblyCode.h"

void fillDuetAssemblyCodeInstructions(DuetAssemblyCode assemblyCode, const char * inputFilePath)
{
    fillLinesIn2DArray(assemblyCode.instructions, assemblyCode.numberOfInstructions, inputFilePath);
}

void initializeDuetAssemblyCode(DuetAssemblyCode * assemblyCode, int programId)
{
    int i;
    assemblyCode->currentInstructionIndex = 0;
    assemblyCode->recoverOperationExecuted = 0;
    assemblyCode->atLeastOneSoundPlayed = 0;
    assemblyCode->frequencyLastSoundPlayed = 0;
    assemblyCode->counterValuesSent = 0;
    assemblyCode->programId = programId;
    for (i = 0 ; i < assemblyCode->numberOfInstructions ; i++)
        assemblyCode->instructions[i][0] = '\0';
    for (i = 0 ; i < NUMBER_OF_LOWER_CASE_LETTERS ; i++)
        assemblyCode->assemblyRegister[i] = 0;
    assemblyCode->assemblyRegister['p' - 'a'] = programId;
    assemblyCode->valuesReceived = initializeQueue();
    assemblyCode->programState = NOT_LOCKED;
    assemblyCode->counterMul = 0;
}

void displayDuetAssemblyCodeInstructions(const DuetAssemblyCode assemblyCode)
{
    int i;
    for (i = 0 ; i < assemblyCode.numberOfInstructions ; i++)
        printf("Instruction %04d: %s\n", i, assemblyCode.instructions[i]);
}

void executeDuetAssemblyCodeInstruction(DuetAssemblyCode * assemblyCode, DuetAssemblyCode * otherAssemblyCode, int part)
{
    char instruction[INSTRUCTION_STRING_LENGTH];
    long long number;
    int indexSecondSpace;
    int correctConversion;
    strcpy(instruction, assemblyCode->instructions[assemblyCode->currentInstructionIndex]);

    if (isSetInstruction(instruction) || isAddInstruction(instruction) || isSubInstruction(instruction) || isMulInstruction(instruction) || isModInstruction(instruction))
    {
        correctConversion = stringToLongLong(instruction, INDEX_INSTRUCTION_OPTION_2, NO_ENDING_INDEX, &number);
        // In that case it was a register like 'a' for example
        if (!correctConversion)
            number = assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_2] - 'a'];

        if (isSetInstruction(instruction))
            assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_1] - 'a'] = number;
        else if (isAddInstruction(instruction))
            assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_1] - 'a'] += number;
        else if (isSubInstruction(instruction))
            assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_1] - 'a'] -= number;
        else if (isMulInstruction(instruction))
        {
            assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_1] - 'a'] *= number;
            assemblyCode->counterMul++;
        }
        else if (isModInstruction(instruction))
            assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_1] - 'a'] %= number;

        (assemblyCode->currentInstructionIndex)++;
    }
    else if (isSndInstruction(instruction))
    {
        correctConversion = stringToLongLong(instruction, INDEX_INSTRUCTION_OPTION_1, NO_ENDING_INDEX, &number);
        // In that case it was a register like 'a' for example
        if (!correctConversion)
            number = assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_1] - 'a'];
        assemblyCode->atLeastOneSoundPlayed = 1;
        assemblyCode->frequencyLastSoundPlayed = number;

        if (part == 2)
        {
            (assemblyCode->counterValuesSent)++;
            addToQueue(otherAssemblyCode->valuesReceived, number);
        }

        (assemblyCode->currentInstructionIndex)++;
    }
    else if (isRcvInstruction(instruction))
    {
        if (part == 1)
        {
            if (assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_1] - 'a'] != 0)
                assemblyCode->recoverOperationExecuted = 1;
            (assemblyCode->currentInstructionIndex)++;
        }
        else if (part == 2)
        {
            if (getQueueLength(assemblyCode->valuesReceived) == 0)
                assemblyCode->programState = LOCKED;
            else
            {
                assemblyCode->programState = NOT_LOCKED;
                assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_1] - 'a'] = getFromQueue(assemblyCode->valuesReceived);
                (assemblyCode->currentInstructionIndex)++;
            }
        }
    }
    else if (isJgzInstruction(instruction) || isJnzInstruction(instruction))
    {
        indexSecondSpace = findSecondOccurrence(instruction, ' ');
        correctConversion = stringToLongLong(instruction, INDEX_INSTRUCTION_OPTION_1, indexSecondSpace - 1, &number);
        // In that case it was a register like 'a' for example
        if (!correctConversion)
            number = assemblyCode->assemblyRegister[instruction[INDEX_INSTRUCTION_OPTION_1] - 'a'];
        if ((isJgzInstruction(instruction) && number > 0) || (isJnzInstruction(instruction) && number != 0))
        {
            correctConversion = stringToLongLong(instruction, indexSecondSpace + 1, NO_ENDING_INDEX, &number);
            // In that case it was a register like 'a' for example
            if (!correctConversion)
                number = assemblyCode->assemblyRegister[instruction[indexSecondSpace + 1] - 'a'];

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

int isSubInstruction(const char * instruction)
{
    return (instruction[0] == 's' && instruction[1] == 'u' && instruction[2] == 'b');
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

int isJnzInstruction(const char * instruction)
{
    return (instruction[0] == 'j' && instruction[1] == 'n' && instruction[2] == 'z');
}

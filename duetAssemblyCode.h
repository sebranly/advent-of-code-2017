#ifndef DUETASSEMBLYCODE_H_INCLUDED
#define DUETASSEMBLYCODE_H_INCLUDED
#define INSTRUCTION_STRING_LENGTH 20

#include <string.h>
#include "stringLibrary.h"
#include "fileLibrary.h"

typedef struct DuetAssemblyCode DuetAssemblyCode;
struct DuetAssemblyCode
{
    int numberOfInstructions;
    char **instructions;
    int currentInstructionIndex;
    int assemblyRegister[NUMBER_OF_LOWER_CASE_LETTERS];
    int recoverOperationExecuted;
    int frequencyLastSoundPlayed;
    int atLeastOneSoundPlayed;
};

void fillDuetAssemblyCodeInstructions(DuetAssemblyCode assemblyCode, const char * inputFilePath);
void initializeDuetAssemblyCode(DuetAssemblyCode * assemblyCode);
void displayDuetAssemblyCodeInstructions(const DuetAssemblyCode assemblyCode);
void executeDuetAssemblyCodeInstruction(DuetAssemblyCode * assemblyCode);
int isSetInstruction(const char * instruction);
int isAddInstruction(const char * instruction);
int isMulInstruction(const char * instruction);
int isModInstruction(const char * instruction);
int isSndInstruction(const char * instruction);
int isRcvInstruction(const char * instruction);
int isJgzInstruction(const char * instruction);

#endif // DUETASSEMBLYCODE_H_INCLUDED

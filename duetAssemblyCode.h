#ifndef DUETASSEMBLYCODE_H_INCLUDED
#define DUETASSEMBLYCODE_H_INCLUDED
#define INSTRUCTION_STRING_LENGTH 20

#include <string.h>
#include "stringLibrary.h"
#include "fileLibrary.h"
#include "queueLibrary.h"

enum { LOCKED, NOT_LOCKED };

typedef struct DuetAssemblyCode DuetAssemblyCode;
struct DuetAssemblyCode
{
    int numberOfInstructions;
    char **instructions;
    int currentInstructionIndex;
    long long assemblyRegister[NUMBER_OF_LOWER_CASE_LETTERS];
    int recoverOperationExecuted;
    int frequencyLastSoundPlayed;
    int atLeastOneSoundPlayed;
    int counterValuesSent;
    int programId;
    Queue *valuesReceived;
    int programState;
};

void fillDuetAssemblyCodeInstructions(DuetAssemblyCode assemblyCode, const char * inputFilePath);
void initializeDuetAssemblyCode(DuetAssemblyCode * assemblyCode, int programId);
void displayDuetAssemblyCodeInstructions(const DuetAssemblyCode assemblyCode);
void executeDuetAssemblyCodeInstruction(DuetAssemblyCode * assemblyCode, DuetAssemblyCode * otherAssemblyCode, int part);
int isSetInstruction(const char * instruction);
int isAddInstruction(const char * instruction);
int isMulInstruction(const char * instruction);
int isModInstruction(const char * instruction);
int isSndInstruction(const char * instruction);
int isRcvInstruction(const char * instruction);
int isJgzInstruction(const char * instruction);

#endif // DUETASSEMBLYCODE_H_INCLUDED

#ifndef DAY08_H_INCLUDED
#define DAY08_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../../other/header/stringLibrary.h"
#include "../../other/header/solutionTypes.h"
// TBD: delete it once main.h is way shorter by exporting definitions for example
#include "../../main.h"

#define MAX_REGISTERS 1200
#define REGISTER_NAME_MAX_LENGTH 10

typedef struct Register Register;
struct Register
{
    char name[REGISTER_NAME_MAX_LENGTH];
    int value;
};

SolutionIntegers getSolutionDay08(const char * inputFilePath);
int createNewRegister(Register * registers, int size, const char * name);
int findRegister(const Register * registers, int size, const char * name);

#endif // DAY08_H_INCLUDED

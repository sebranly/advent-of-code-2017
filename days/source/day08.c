#include "../header/day08.h"

SolutionIntegers getSolutionDay08(const char * inputFilePath)
{
    SolutionIntegers solution;
    solution.solutionPart1 = 0;
    solution.solutionPart2 = 0;

    char registerName[REGISTER_NAME_MAX_LENGTH], conditionalRegisterName[REGISTER_NAME_MAX_LENGTH];
    char operationString[STRING_LIMITED_LENGTH], conditionalString[STRING_LIMITED_LENGTH], operatorString[STRING_LIMITED_LENGTH];
    Register registers[MAX_REGISTERS];
    int indexAffectedRegister, indexConditionalRegister, size = 0, currentNumber = 0, currentConditionalNumber = 0, i;
    int keepReading = 1;
    int sign = 1;

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        while (keepReading)
        {
            fscanf(file, "%s %s %d %s %s %s %d", registerName, operationString, &currentNumber, conditionalString, conditionalRegisterName, operatorString, &currentConditionalNumber);

            indexAffectedRegister = findRegister(registers, size, registerName);
            if (indexAffectedRegister == NOT_FOUND)
            {
                indexAffectedRegister = size;
                size = createNewRegister(registers, size, registerName);
            }

            indexConditionalRegister = findRegister(registers, size, conditionalRegisterName);
            if (indexConditionalRegister == NOT_FOUND)
            {
                indexConditionalRegister = size;
                size = createNewRegister(registers, size, conditionalRegisterName);
            }

            if (
                (sameStrings(operatorString, ">") && registers[indexConditionalRegister].value > currentConditionalNumber) ||
                (sameStrings(operatorString, "<") && registers[indexConditionalRegister].value < currentConditionalNumber) ||
                (sameStrings(operatorString, ">=") && registers[indexConditionalRegister].value >= currentConditionalNumber) ||
                (sameStrings(operatorString, "<=") && registers[indexConditionalRegister].value <= currentConditionalNumber) ||
                (sameStrings(operatorString, "!=") && registers[indexConditionalRegister].value != currentConditionalNumber) ||
                (sameStrings(operatorString, "==") && registers[indexConditionalRegister].value == currentConditionalNumber)
            )
            {
                sign = sameStrings(operationString, "inc") ? 1 : -1;
                registers[indexAffectedRegister].value += sign * currentNumber;
                if (registers[indexAffectedRegister].value > solution.solutionPart2)
                    solution.solutionPart2 = registers[indexAffectedRegister].value;
            }

            if (fgetc(file) == EOF)
                keepReading = 0;
        }

        for (i = 0 ; i < size ; i++)
            if (i == 0 || registers[i].value > solution.solutionPart1)
                solution.solutionPart1 = registers[i].value;

        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

int findRegister(const Register * registers, int size, const char * name)
{
    int i = 0;
    for (i = 0 ; i < size ; i++)
        if (sameStrings(registers[i].name, name))
            return i;
    return NOT_FOUND;
}

int createNewRegister(Register * registers, int size, const char * name)
{
    Register newRegister;
    newRegister.value = 0;
    strcpy(newRegister.name, name);
    registers[size] = newRegister;
    return size + 1;
}

#include "day25.h"

int getSolutionDay25(const char * inputFilePath)
{
    int solution = 0;
    char string[SHORT_STRING_LENGTH];
    int currentNumber = 0, currentStateIndex, currentValueIndex, i, j, iteration, numberOfIterations, initialStateIndex, valuesArraySize;
    int numberOfStates = (numberOfNonEmptyLines(inputFilePath) - DAY_25_HEADER_INPUT_NUMBER_OF_LINES) / DAY_25_STATE_INPUT_NUMBER_OF_LINES;
    StateRule *stateRules;
    char * values;

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        stateRules = malloc(sizeof(StateRule) * numberOfStates);
        if (stateRules == NULL)
        {
            printf("An error occurred because of limited memory\n");
            exit(EXIT_FAILURE);
        }
        fscanf(file, "Begin in state %s.", string);
        initialStateIndex = string[0] - 'A';
        while (fgetc(file) != '\n');
        fscanf(file, "Perform a diagnostic checksum after %d steps.", &numberOfIterations);
        while (fgetc(file) != '\n');

        for (i = 0 ; i < numberOfStates ; i++)
        {
            while (fgetc(file) != '\n');
            fscanf(file, "In state %s:", string);
            currentStateIndex = string[0] - 'A';
            while (fgetc(file) != '\n');
            for (j = 0 ; j < 2 ; j++)
            {
                fscanf(file, "  If the current value is %d:", &currentNumber);
                while (fgetc(file) != '\n');
                fscanf(file, "    - Write the value %d.", &(stateRules[currentStateIndex].nextValueIf[currentNumber]));
                while (fgetc(file) != '\n');
                fscanf(file, "    - Move one slot to the %s", string);
                if (sameStrings(string, "left."))
                    stateRules[currentStateIndex].nextOffsetIf[currentNumber] = -1;
                else
                    stateRules[currentStateIndex].nextOffsetIf[currentNumber] = 1;
                while (fgetc(file) != '\n');
                fscanf(file, "    - Continue with state %s.", string);
                while (fgetc(file) != '\n' && fgetc(file) != EOF);
                stateRules[currentStateIndex].nextStateIf[currentNumber] = string[0] - 'A';
            }
        }

        valuesArraySize = 2 * numberOfIterations + 1;
        values = malloc(sizeof(char) * valuesArraySize);
        if (values == NULL)
        {
            printf("An error occurred because of limited memory\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0 ; i < valuesArraySize ; i++)
            values[i] = 0;

        currentStateIndex = initialStateIndex;
        currentValueIndex = numberOfIterations + 1;
        for (iteration = 0 ; iteration < numberOfIterations ; iteration++)
        {
            currentNumber = values[currentValueIndex];
            values[currentValueIndex] = stateRules[currentStateIndex].nextValueIf[currentNumber];
            currentValueIndex += stateRules[currentStateIndex].nextOffsetIf[currentNumber];
            currentStateIndex = stateRules[currentStateIndex].nextStateIf[currentNumber];
        }
        for (i = 0 ; i < valuesArraySize ; i++)
            solution += values[i];

        free(stateRules);
        free(values);

        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

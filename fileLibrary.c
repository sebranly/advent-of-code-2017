#include "fileLibrary.h"

int numberOfNonEmptyLines(const char * inputFilePath)
{
    int counterOfLines = 0;
    char currentChar;
    int keepReading = 1, freshNewLine = 1;

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (currentChar == '\n')
            {
                if (!freshNewLine)
                    counterOfLines++;
                freshNewLine = 1;
            }
            else if (currentChar == EOF)
            {
                if (!freshNewLine)
                    counterOfLines++;
                keepReading = 0;
            }
            else
                freshNewLine = 0;
        }
        fclose(file);
        return counterOfLines;
    }
    else
        return -1;
}

void readUniqueLine(const char * inputFilePath, char * inputContent, int stringLength)
{
    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        fgets(inputContent, stringLength, file);
        fclose(file);
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

int readUniqueNumber(const char * inputFilePath)
{
    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    int number = 0;
    char currentChar;

    if (file != NULL)
    {
        while (isADigit(currentChar = fgetc(file)))
            number = number * 10 + toInteger(currentChar);
        return number;

    }
    printf("The file with name %s could not be opened", inputFilePath);
    exit(EXIT_FAILURE);
}

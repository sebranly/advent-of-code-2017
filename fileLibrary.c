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
        return counterOfLines;
    }
    else
        return -1;
}

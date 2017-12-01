#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57

#define UNSET -1

#define ARBITRARY_ARRAY_LIMIT 3000

int isADigit(char c);
int toInteger(char digit);

int main()
{
    FILE* file = NULL;
    char currentChar = 0;
    int previousDigit = UNSET;
    int currentDigit = UNSET;
    int firstDigit = UNSET;
    int keepReading = 1;
    int i = 0, sum = 0, comparisonIndex = 0, inputLength = 0, halfInputLength = 0;
    int input[ARBITRARY_ARRAY_LIMIT] = {0};

    file = fopen("inputDay01.txt", "r");

    if (file != NULL)
    {
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (isADigit(currentChar))
                {
                    currentDigit = toInteger(currentChar);

                    input[inputLength] = currentDigit;
                    inputLength++;

                    if (firstDigit == UNSET)
                    {
                        firstDigit = currentDigit;
                    }
                    else if (currentDigit == previousDigit) {
                        sum += previousDigit;
                    }

                    previousDigit = currentDigit;
                }
                else
                {
                    keepReading = 0;
                }
            }

            if (previousDigit == firstDigit)
            {
                sum += previousDigit;
            }

            printf("Part 1 - Sum for the input is: %d\n", sum);

            sum = 0;
            halfInputLength = inputLength / 2;
            for (i = 0 ; i < inputLength ; i++)
            {
                if (i < halfInputLength)
                    comparisonIndex = i + halfInputLength;
                else {
                    comparisonIndex = i - halfInputLength;
                }

                if (input[comparisonIndex] == input[i])
                    sum += input[i];
            }
            printf("Part 2 - Sum for the input is: %d\n", sum);

            fclose(file);
    }
    else
    {
        printf("No file found");
    }

    return 0;
}

int isADigit(char c)
{
    return (c >= ZERO_ASCII_CODE && c <= NINE_ASCII_CODE);
}

int toInteger(char digit)
{
    return digit - ZERO_ASCII_CODE;
}

#include "../header/day04.h"

SolutionIntegers getSolutionDay04(const char * inputFilePath)
{
    SolutionIntegers solution;
    solution.solutionPart1 = 0;
    solution.solutionPart2 = 0;

    int currentIndex = 0, currentCharIndex = 0, i, j;
    char currentChar;
    char inlineInputAsText[MAX_ELEMENTS_PER_LINE][STRING_MAX_LENGTH];
    int keepReading = 1, skipLine = 0;
    int counterOfLetters1[NUMBER_OF_LOWER_CASE_LETTERS] = {0};
    int counterOfLetters2[NUMBER_OF_LOWER_CASE_LETTERS] = {0};

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        emptyInlineTextInput(inlineInputAsText);
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isALowerCaseLetter(currentChar))
            {
                inlineInputAsText[currentIndex][currentCharIndex] = currentChar;
                currentCharIndex++;
            }
            else if (currentChar == ' ' || currentChar == '\n' || currentChar == EOF)
            {
                inlineInputAsText[currentIndex][currentCharIndex] = '\0';
                currentCharIndex = 0;
                if (currentChar == ' ')
                    currentIndex++;
                else
                {
                    skipLine = 0;
                    i = 0;
                    while (i <= currentIndex && !skipLine)
                    {
                        j = 0;
                        while (j <= currentIndex && !skipLine)
                        {
                            if (i != j && sameStrings(inlineInputAsText[i], inlineInputAsText[j]))
                                skipLine = 1;
                            j++;
                        }
                        i++;
                    }
                    if (!skipLine)
                    {
                        solution.solutionPart1 += 1;
                        // The rule for part 2 (based on anagrams) is more strict than the rule for part 1 (based on string comparison)
                        skipLine = 0;
                        i = 0;
                        while (i <= currentIndex && !skipLine)
                        {
                            countLetters(inlineInputAsText[i], counterOfLetters1);
                            j = 0;
                            while (j <= currentIndex && !skipLine)
                            {
                                if (i != j)
                                {
                                    countLetters(inlineInputAsText[j], counterOfLetters2);
                                    if (!differentArrays(counterOfLetters1, counterOfLetters2, NUMBER_OF_LOWER_CASE_LETTERS))
                                        skipLine = 1;
                                }
                                j++;
                            }
                            i++;
                        }
                        if (!skipLine)
                            solution.solutionPart2 += 1;
                    }

                    currentIndex = 0;
                    emptyInlineTextInput(inlineInputAsText);

                    if (currentChar == EOF)
                        keepReading = 0;
                }
            }
            else
            {
                printf("An unexpected error occurred while reading the input file with name %s because of an unexpected character\n", inputFilePath);
                exit(EXIT_FAILURE);
            }
        }
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

void emptyInlineTextInput(char inlineInputAsText[MAX_ELEMENTS_PER_LINE][STRING_MAX_LENGTH])
{
    int i;
    for (i = 0 ; i < MAX_ELEMENTS_PER_LINE ; i++)
        inlineInputAsText[i][0] = '\0';
}

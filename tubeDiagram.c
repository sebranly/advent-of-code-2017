#include "tubeDiagram.h"

void initializeTubeDiagram(TubeDiagram * tubeDiagram)
{
    tubeDiagram->vectorNextMove.x = 0;
    tubeDiagram->vectorNextMove.y = 0;
    tubeDiagram->currentPosition.x = 0;
    tubeDiagram->currentPosition.y = 0;
    tubeDiagram->numberOfLetters = 0;
    tubeDiagram->counterOfPickedLetters = 0;
    tubeDiagram->numberOfSteps = 0;
    tubeDiagram->currentPathIndex = 0;
}

void fillTubeDiagram(TubeDiagram * tubeDiagram, const char * inputFilePath)
{
    FILE* file = NULL;
    file = fopen(inputFilePath, "r");
    char currentChar;
    int currentCharIndex = 0, currentLine = 0;

    if (file != NULL)
    {
        while (currentLine < tubeDiagram->heightDiagram)
        {
            currentChar = fgetc(file);
            if (currentChar == '\n' || currentChar == EOF)
            {
                currentLine++;
                currentCharIndex = 0;
            }
            else
            {
                tubeDiagram->diagram[currentLine][currentCharIndex] = currentChar;
                currentCharIndex++;
                if (isAnUpperCaseLetter(currentChar))
                    tubeDiagram->numberOfLetters++;
            }
        }
        tubeDiagram->path = malloc(sizeof(char) * (tubeDiagram->numberOfLetters + 1));
        if (tubeDiagram->path == NULL)
        {
            printf("An error occurred because of memory limitation\n");
            exit(EXIT_FAILURE);
        }
        tubeDiagram->path[0] = '\0';
        fclose(file);
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

void displayTubeDiagramDiagram(const TubeDiagram tubeDiagram)
{
    int i, j;
    for (j = 0 ; j < tubeDiagram.heightDiagram ; j++)
    {
        printf("\n");
        for (i = 0 ; i < tubeDiagram.widthDiagram ; i++)
        {
            printf("%c", tubeDiagram.diagram[j][i]);
        }
    }
    printf("\n");
}

void findTubeDiagramStartingPosition(TubeDiagram * tubeDiagram)
{
    int i = 0;
    while (i < tubeDiagram->widthDiagram && tubeDiagram->diagram[0][i] != '|')
        i++;
    tubeDiagram->currentPosition.x = i;
    tubeDiagram->currentPosition.y = 0;
    tubeDiagram->vectorNextMove.x = 0;
    tubeDiagram->vectorNextMove.y = 1;
    tubeDiagram->numberOfSteps = 1;
}

void moveOneStepInTubeDiagram(TubeDiagram * tubeDiagram)
{
    if (tubeDiagram->vectorNextMove.y != 0 && tubeDiagram->vectorNextMove.x == 0)
    {
        if (!(valueIsBetween(tubeDiagram->currentPosition.y + tubeDiagram->vectorNextMove.y, 0, tubeDiagram->heightDiagram - 1) && tubeDiagram->diagram[tubeDiagram->currentPosition.y + tubeDiagram->vectorNextMove.y][tubeDiagram->currentPosition.x] != ' '))
        {
            if (valueIsBetween(tubeDiagram->currentPosition.x + 1, 0, tubeDiagram->widthDiagram - 1) && tubeDiagram->diagram[tubeDiagram->currentPosition.y][tubeDiagram->currentPosition.x + 1] != ' ')
            {
                tubeDiagram->vectorNextMove.y = 0;
                tubeDiagram->vectorNextMove.x = 1;
            }
            else if (valueIsBetween(tubeDiagram->currentPosition.x - 1, 0, tubeDiagram->widthDiagram - 1) && tubeDiagram->diagram[tubeDiagram->currentPosition.y][tubeDiagram->currentPosition.x - 1] != ' ')
            {
                tubeDiagram->vectorNextMove.y = 0;
                tubeDiagram->vectorNextMove.x = -1;
            }
        }
    }
    else if (tubeDiagram->vectorNextMove.y == 0 && tubeDiagram->vectorNextMove.x != 0)
    {
        if (!(valueIsBetween(tubeDiagram->currentPosition.x + tubeDiagram->vectorNextMove.x, 0, tubeDiagram->widthDiagram - 1) && tubeDiagram->diagram[tubeDiagram->currentPosition.y][tubeDiagram->currentPosition.x + tubeDiagram->vectorNextMove.x] != ' '))
        {
            if (valueIsBetween(tubeDiagram->currentPosition.y + 1, 0, tubeDiagram->heightDiagram - 1) && tubeDiagram->diagram[tubeDiagram->currentPosition.y + 1][tubeDiagram->currentPosition.x] != ' ')
            {
                tubeDiagram->vectorNextMove.y = 1;
                tubeDiagram->vectorNextMove.x = 0;
            }
            else if (valueIsBetween(tubeDiagram->currentPosition.y - 1, 0, tubeDiagram->heightDiagram - 1) && tubeDiagram->diagram[tubeDiagram->currentPosition.y - 1][tubeDiagram->currentPosition.x] != ' ')
            {
                tubeDiagram->vectorNextMove.y = -1;
                tubeDiagram->vectorNextMove.x = 0;
            }
        }
    }
    tubeDiagram->currentPosition.x += tubeDiagram->vectorNextMove.x;
    tubeDiagram->currentPosition.y += tubeDiagram->vectorNextMove.y;
    (tubeDiagram->numberOfSteps)++;
    if (isAnUpperCaseLetter(tubeDiagram->diagram[tubeDiagram->currentPosition.y][tubeDiagram->currentPosition.x]))
    {
        (tubeDiagram->counterOfPickedLetters)++;
        tubeDiagram->path[tubeDiagram->currentPathIndex] = tubeDiagram->diagram[tubeDiagram->currentPosition.y][tubeDiagram->currentPosition.x];
        (tubeDiagram->currentPathIndex)++;
        tubeDiagram->path[tubeDiagram->currentPathIndex] = '\0';
    }
}

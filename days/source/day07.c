#include "../header/day07.h"

SolutionStringInteger getSolutionDay07(const char * inputFilePath)
{
    SolutionStringInteger solution;
    strcpy(solution.solutionPart1, "");
    solution.solutionPart2 = -1;

    char ancestorName[TREE_ELEMENT_NAME_MAX_LENGTH], elementName[TREE_ELEMENT_NAME_MAX_LENGTH];
    TreeElement treeElements[MAX_TREE_ELEMENTS], ancestor;
    int stillOnAncestorName = 1, keepReading = 1;
    int size = 0, currentCharIndex = 0, currentNumber = 0, i;
    char currentChar;

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        while(keepReading)
        {
            currentChar = fgetc(file);
            if (isALowerCaseLetter(currentChar) && stillOnAncestorName)
            {
                treeElements[size].name[currentCharIndex] = currentChar;
                currentCharIndex++;
            }
            else if (currentChar == ' ' && stillOnAncestorName)
            {
                treeElements[size].name[currentCharIndex] = '\0';
                stillOnAncestorName = 0;
            }
            else if (isADigit(currentChar))
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else if (currentChar == ')')
            {
                treeElements[size].valueOfAncestor = currentNumber;
                currentNumber = 0;
            }
            else if (currentChar == '\n')
            {
                size++;
                stillOnAncestorName = 1;
                currentCharIndex = 0;
            }
            else if (currentChar == EOF)
            {
                // Workaround in order not to count a new line plus EOF as a word regarding the size in case it was empty
                if (!stillOnAncestorName)
                    size++;
                keepReading = 0;
            }
        }
        removeTreeAncestors(treeElements, size);
        rewind(file);

        keepReading = 1;
        stillOnAncestorName = 1;
        currentCharIndex = 0;
        while (keepReading)
        {
            currentChar = fgetc(file);
            if (isALowerCaseLetter(currentChar))
            {
                if (stillOnAncestorName)
                {
                    ancestorName[currentCharIndex] = currentChar;
                }
                else
                {
                    elementName[currentCharIndex] = currentChar;
                }
                currentCharIndex++;
            }
            else if (currentChar == '>')
            {
                ancestorName[currentCharIndex] = '\0';
                currentCharIndex = 0;
                stillOnAncestorName = 0;
            }
            else if (currentChar == ',')
            {
                elementName[currentCharIndex] = '\0';
                addAncestor(treeElements, size, elementName, ancestorName);
                currentCharIndex = 0;
            }
            else if (currentChar == '\n')
            {
                if (!stillOnAncestorName)
                {
                    elementName[currentCharIndex] = '\0';
                    addAncestor(treeElements, size, elementName, ancestorName);
                }
                currentCharIndex = 0;
                ancestorName[0] = '\0';
                stillOnAncestorName = 1;
            }
            else if (currentChar == EOF)
            {
                if (!stillOnAncestorName)
                {
                    elementName[currentCharIndex] = '\0';
                    addAncestor(treeElements, size, elementName, ancestorName);
                }
                keepReading = 0;
            }
        }
        ancestor = firstElementWithoutAncestor(treeElements, size);
        strcpy(solution.solutionPart1, ancestor.name);
        setValueOfAncestorAndChildren(treeElements, size, &ancestor);

        // TBD: deserves a proper solution as it won't work for other inputs
        // For now, I got the solution by displaying the tree with a limited depth and going into the right branch
        for (i = 0 ; i < size ; i++)
            if (sameStrings(treeElements[i].name, "orflty"))
                ancestor = treeElements[i];
        displayChildren(treeElements, size, ancestor, 0);

        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

// Gets the first element in the tree that matches the element name and adds the specified ancestor to it
int addAncestor(TreeElement elements[], int size, const char elementName[], const char ancestorName[])
{
    int i = 0;
    for (i = 0 ; i < size ; i++)
        if (sameStrings(elementName, elements[i].name))
        {
            strcpy(elements[i].uniqueAncestorName, ancestorName);
            return 1;
        }
    return 0;
}

void removeTreeAncestors(TreeElement elements[], int size)
{
    int i = 0;
    for (i = 0 ; i < 0 ; i++)
        elements[i].uniqueAncestorName[0] = '\0';
}

TreeElement firstElementWithoutAncestor(TreeElement elements[], int size)
{
    TreeElement defaultElement;
    strcpy(defaultElement.name, "");
    int i = 0;
    for (i = 0 ; i < size ; i++)
        if (elements[i].uniqueAncestorName[0] == '\0')
            return elements[i];
    return defaultElement;
}

void displayChildren(TreeElement elements[], int size, const TreeElement ancestor, int depth)
{
    int i = 0;
    for (i = 0 ; i < depth ; i++)
        printf("\t");
    printf("%s (%d) (Total: %d)\n", ancestor.name, ancestor.valueOfAncestor, ancestor.valueOfAncestorAndChildren);
    if (depth >= MAX_DEPTH_TO_DISPLAY)
        return;
    for (i = 0 ; i < size ; i++)
        if (sameStrings(elements[i].uniqueAncestorName, ancestor.name))
            displayChildren(elements, size, elements[i], depth + 1);
}

int setValueOfAncestorAndChildren(TreeElement elements[], int size, TreeElement * pAncestor)
{
    int i = 0;
    pAncestor->valueOfAncestorAndChildren = pAncestor->valueOfAncestor;
    for (i = 0 ; i < size ; i++)
        if (sameStrings(elements[i].uniqueAncestorName, pAncestor->name))
            pAncestor->valueOfAncestorAndChildren += setValueOfAncestorAndChildren(elements, size, &(elements[i]));
    return pAncestor->valueOfAncestorAndChildren;
}

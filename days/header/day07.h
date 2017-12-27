#ifndef DAY07_H_INCLUDED
#define DAY07_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../../other/header/stringLibrary.h"
#include "../../other/header/solutionTypes.h"

#define MAX_TREE_ELEMENTS 1200
#define TREE_ELEMENT_NAME_MAX_LENGTH 20
#define MAX_DEPTH_TO_DISPLAY 2

typedef struct TreeElement TreeElement;
struct TreeElement
{
    char uniqueAncestorName[TREE_ELEMENT_NAME_MAX_LENGTH];
    char name[TREE_ELEMENT_NAME_MAX_LENGTH];
    int valueOfAncestor;
    int valueOfAncestorAndChildren;
};

SolutionStringInteger getSolutionDay07(const char * inputFilePath);
int addAncestor(TreeElement elements[], int size, const char elementName[], const char ancestorName[]);
void removeTreeAncestors(TreeElement elements[], int size);
TreeElement firstElementWithoutAncestor(TreeElement elements[], int size);
void displayChildren(TreeElement elements[], int size, const TreeElement ancestor, int depth);
int setValueOfAncestorAndChildren(TreeElement elements[], int size, TreeElement * ancestor);

#endif // DAY07_H_INCLUDED

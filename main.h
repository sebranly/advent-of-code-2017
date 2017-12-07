#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define MAX_TREE_ELEMENTS 1200
#define TREE_ELEMENT_NAME_MAX_LENGTH 20

typedef struct TreeElement TreeElement;
struct TreeElement
{
    char uniqueAncestorName[TREE_ELEMENT_NAME_MAX_LENGTH];
    char name[TREE_ELEMENT_NAME_MAX_LENGTH];
    int valueOfAncestor;
    int valueOfAncestorAndChildren;
};

#endif // MAIN_H_INCLUDED

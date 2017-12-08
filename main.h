#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define MAX_TREE_ELEMENTS 1200
#define MAX_REGISTERS 1200
#define TREE_ELEMENT_NAME_MAX_LENGTH 20
#define REGISTER_NAME_MAX_LENGTH 10

typedef struct TreeElement TreeElement;
struct TreeElement
{
    char uniqueAncestorName[TREE_ELEMENT_NAME_MAX_LENGTH];
    char name[TREE_ELEMENT_NAME_MAX_LENGTH];
    int valueOfAncestor;
    int valueOfAncestorAndChildren;
};

typedef struct Register Register;
struct Register
{
    char name[REGISTER_NAME_MAX_LENGTH];
    int value;
};

#endif // MAIN_H_INCLUDED

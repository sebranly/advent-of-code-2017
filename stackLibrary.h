#ifndef STACKLIBRARY_H_INCLUDED
#define STACKLIBRARY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct StackElement StackElement;
struct StackElement
{
    int number;
    StackElement *next;
};

typedef struct Stack Stack;
struct Stack
{
    StackElement *first;
};

void push(Stack *stack, int newNumber);
int pop(Stack *stack);
void displayStack(Stack *stack);
int getStackLength(Stack *stack);
Stack *initializeStack(void);

#endif // STACKLIBRARY_H_INCLUDED

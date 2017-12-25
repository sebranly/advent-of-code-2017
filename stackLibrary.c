#include "stackLibrary.h"

void push(Stack *stack, int newNumber)
{
    StackElement *newElement = malloc(sizeof(*newElement));
    if (stack == NULL || newElement == NULL)
        exit(EXIT_FAILURE);
    newElement->number = newNumber;
    newElement->next = stack->first;
    stack->first = newElement;
}

int pop(Stack *stack)
{
    if (stack == NULL)
        exit(EXIT_FAILURE);

    int numberToReturn = -1;
    StackElement *element = stack->first;

    if (stack->first != NULL)
    {
        numberToReturn = element->number;
        stack->first = element->next;
        free(element);
    }

    return numberToReturn;
}

void displayStack(Stack *stack)
{
    if (stack == NULL)
        exit(EXIT_FAILURE);
    StackElement *element = stack->first;

    while (element != NULL)
    {
        printf("%d -> ", element->number);
        element = element->next;
    }

    printf("[NULL]\n");
}

int getStackLength(Stack *stack)
{
    StackElement *currentElement;
    int length = 0;
    if (stack == NULL)
        exit(EXIT_FAILURE);
    if (stack->first == NULL)
        return 0;
    else
    {
        currentElement = stack->first;
        length = 1;
        while (currentElement->next != NULL)
        {
            currentElement = currentElement->next;
            length++;
        }
        return length;
    }
}

Stack *initializeStack(void)
{
    Stack *stack = malloc(sizeof(*stack));
    if (stack == NULL)
        exit(EXIT_FAILURE);
    stack->first = NULL;
    return stack;
}

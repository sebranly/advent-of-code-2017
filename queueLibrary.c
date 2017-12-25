#include "queueLibrary.h"

void addToQueue(Queue *queue, long long newNumber)
{
    QueueElement *currentElement;
    QueueElement *newElement = malloc(sizeof(*newElement));
    if (queue == NULL || newElement == NULL)
        exit(EXIT_FAILURE);
    newElement->number = newNumber;
    newElement->next = NULL;

    if (queue->first != NULL)
    {
        currentElement = queue->first;
        while (currentElement->next != NULL)
            currentElement = currentElement->next;
        currentElement->next = newElement;
    }
    else
        queue->first = newElement;
}

long long getFromQueue(Queue *queue)
{
    QueueElement *element;
    long long numberToReturn = 0;
    if (queue == NULL)
        exit(EXIT_FAILURE);
    if (queue->first != NULL)
    {
        element = queue->first;

        numberToReturn = element->number;
        queue->first = element->next;
        free(element);
    }
    return numberToReturn;
}

int getQueueLength(Queue *queue)
{
    QueueElement *currentElement;
    int length = 0;
    if (queue == NULL)
        exit(EXIT_FAILURE);
    if (queue->first == NULL)
        return 0;
    else
    {
        currentElement = queue->first;
        length = 1;
        while (currentElement->next != NULL)
        {
            currentElement = currentElement->next;
            length++;
        }
        return length;
    }
}

void displayQueue(Queue *queue)
{
    QueueElement *element;
    if (queue == NULL)
        exit(EXIT_FAILURE);
    if (queue->first != NULL)
    {
        element = queue->first;
        printf("%d <- ", element->number);
        while (element->next != NULL)
        {
            element = element->next;
            printf("%d <- ", element->number);
        }
    }
    printf("[NULL]\n");
}

Queue *initializeQueue(void)
{
    Queue *queue = malloc(sizeof(*queue));
    if (queue == NULL)
        exit(EXIT_FAILURE);
    queue->first = NULL;
    return queue;
}

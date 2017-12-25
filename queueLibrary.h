#ifndef QUEUELIBRARY_H_INCLUDED
#define QUEUELIBRARY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueElement QueueElement;
struct QueueElement
{
    long long number;
    QueueElement *next;
};

typedef struct Queue Queue;
struct Queue
{
    QueueElement *first;
};

void addToQueue(Queue *queue, long long newNumber);
long long getFromQueue(Queue *queue);
int getQueueLength(Queue *queue);
Queue *initializeQueue(void);
void displayQueue(Queue *queue);

#endif // QUEUELIBRARY_H_INCLUDED

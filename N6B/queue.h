#ifndef QUEUE_H
#define QUEUE_H
#include "utils.h"
typedef int T;
typedef struct queue
{
    pnode front;
    pnode rear;
}queue;
int createqueue(queue* q);
void push(queue* q,T data);
void pop(queue* q);
void destroyqueue(queue* q);
#endif // QUEUE_H

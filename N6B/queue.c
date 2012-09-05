#include "queue.h"
#include <stdlib.h>
int createqueue(queue* q)
{
    q->front=(pnode)malloc(sizeof(node));
    if(!q->front)return 1;
    q->rear=q->front;
    q->front->next=0;
    return 0;
}
void push(queue* q,T data)
{
    q->rear->next=malloc(sizeof(node));
    q->rear=q->rear->next;
    q->rear->data=data;
    q->rear->next=0;
}
void pop(queue* q)
{
    pnode tmp=q->front->next;
    q->front->next=tmp->next;
    free(tmp);
}
void destroyqueue(queue* q)
{
    pnode p=q->front->next;
    while(p)
    {
        free(q->front);
        q->front=p;
        p=p->next;
    }
    free(q->front);
}

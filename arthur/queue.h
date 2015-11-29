#ifndef QUEUE_H
#define QUEUE_H

struct queue;

void queue_init(struct queue*, int cap, int sz);
int queue_empty(struct queue*);
void dequeue(struct queue*, void *v);
void enqueue(struct queue*, void *v);
void queue_release(struct queue*);

#endif

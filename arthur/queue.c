#include <string.h>
#include <stdlib.h>

struct queue {
  void *ptr;
  int head;
  int tail;
  int cap;
  int elem_size;
};

void
queue_init(struct queue* q, int cap, int sz) {
  q->head = 0;
  q->tail = 0;
  q->elem_size = sz;
  q->cap = cap;
  q->ptr = malloc(cap * sz);
}

int
queue_empty(struct queue* q) {
  return q->head == q->tail;
}

void
enqueue(struct queue*q, void *v) {
  memcpy(q->ptr+q->tail*q->elem_size, v, q->elem_size);
  q->tail = (q->tail+1) % q->cap;
}

void
dequeue(struct queue*q, void *v) {
  memcpy(v, q->ptr+q->head*q->elem_size, q->elem_size);
  q->head = (q->head+1) % q->cap;
}

void
queue_release(struct queue* q) {
  free(q->ptr);
}

#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *LR;
};

struct list {
	struct node *head;
	struct node *tail;
};

struct node * xor(struct node *p, struct node *q) {
	return (struct node *)((unsigned long)p ^ (unsigned long)q);
}

void travel(struct list *l) {
	struct node *pre, *p, *q;

	pre = NULL;
	p = l->head;
	while(p != NULL) {
		printf("%d ", p->data);
		q = xor(pre, p->LR);
		pre = p;
		p = q;
	}
}

//将结点n插入到pre和next之间
void _insert(struct node *pre, struct node *next, struct node *p) {
	struct node *tmp;

	p->LR = xor(pre, next);

	if(pre != NULL) {
		tmp = xor(next, pre->LR); //tmp记录pre的前面的
		pre->LR = xor(p, tmp);
	}

	if(next != NULL) {
		tmp = xor(pre, next->LR); //tmp记录next的后面的
		next->LR = xor(p, tmp);
	}
}

void insert(struct list *l, int data) {
	struct node *tmp, *next;

	tmp = malloc(sizeof(struct node));
	tmp->data = data;
	
	if(l->head == NULL) {
		l->head = tmp;
		l->tail = tmp;
		tmp->LR = xor(NULL, NULL);
		return;
	}

	if(l->head == l->tail) {
		_insert(l->head, NULL, tmp);
		l->tail = tmp;
		return;
	}

	next = xor(l->head->LR, NULL);
	_insert(l->head, next, tmp);
}

int main() {
	struct list l;
	l.head = NULL;
	l.tail = NULL;

	insert(&l, 1);
	insert(&l, 2);
	insert(&l, 3);
	insert(&l, 4);
	insert(&l, 5);
	insert(&l, 6);
	insert(&l, 7);
	insert(&l, 8);
	travel(&l);
	return 0;
}

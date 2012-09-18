#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	struct node *next[0];
};
struct skiplist {
	struct node *head;
	int length;
	int level;
};
struct node* node_create(int key,int level) {
	struct node *ret;
	int i;
	ret = malloc(sizeof(struct node) + (level+1)*sizeof(struct node*));
	ret->key = key;
	for(i=0; i<level; i++) 
		ret->next[i] = NULL;
	return ret;
}
struct skiplist* skiplist_create() {
	struct skiplist *ret;

	srand(time(NULL));
	ret = malloc(sizeof(struct skiplist));
	ret->level = 0;
	ret->length = 0;
	ret->head = node_create(0,32);
	return ret;
}
int random_level() {
	int ret = 0;

	while(rand() & 1) {
		++ret;
	}
	return ret;
}
void skiplist_insert(struct skiplist* s, int key) {
	struct node *p,*q,*cur[32];
	int i;
	volatile int level;

	q = s->head;
	for(i=s->level; i>=0; i--) {
		p = q->next[i];
		while(p && p->key < key) {
			q = p;
			p = p->next[i];
		}
		cur[i] = q;
	}
	level = random_level();
	if(level > s->level) {
		s->level++;
		level = s->level;
		cur[level] = s->head;
	}
	p = node_create(key,level);
	for(i=level; i>=0; i--) {
		p->next[i] = cur[i]->next[i];
		cur[i]->next[i] = p;
	}
	s->length++;
}

void print(struct skiplist *s) {
	struct node *p;
	int i;
	for(i=0; i<=s->level; i++) {
		for(p=s->head->next[i]; p; p=p->next[i]) {
			printf("%d->",p->key);
		}
		printf("\n");
	}
}
int main() {
	struct skiplist *s;
	struct node *p;
	int i,level;

	s = skiplist_create();
	for(i=0; i<20; i++) {
		skiplist_insert(s,rand()%40);
	}
	print(s);
	return 0;
}

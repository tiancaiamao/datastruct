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
	srand(time(NULL));
	ret = malloc(sizeof(struct node) * level);
	ret->key = key;
	for(i=0; i<level; i++) 
		ret->next[i] = NULL;
	return ret;
}
struct skiplist* skiplist_create() {
	struct skiplist *ret;

	ret = malloc(sizeof(struct skiplist));
	ret->level = 0;
	ret->length = 0;
	ret->head = node_create(0,32);
	return ret;
}
int random_level() {
	int level = 1;
	while(rand() & 1)
		level++;
	return level;
}
void skiplist_insert(struct skiplist* s, int key) {
	struct node *p,*q,*cur[32];
	int level;

	q = s->head;
	for(level=s->level; level>=0; level--) {
		p = q->next[level];
		while(p && p->key < key) {
			q = p;
			p = p->next[level];
		}
		cur[level] = q;
	}
	level = random_level();
	if(level >= s->level) {
		s->level++;
		level = s->level;
		cur[level] = s->head;
	}
	p = node_create(key,level);
	for(level=s->level; level>=0; level--) {
		p->next[level] = cur[level]->next[level];
		cur[level]->next[level] = p;
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

	s = skiplist_create();
	skiplist_insert(s,5);
	skiplist_insert(s,3);
	print(s);
	skiplist_insert(s,4);
	skiplist_insert(s,1);
	skiplist_insert(s,8);
	skiplist_insert(s,7);
	skiplist_insert(s,6);
	skiplist_insert(s,2);
	print(s);
	return 0;
}

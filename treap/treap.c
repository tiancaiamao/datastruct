#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
	int priority;
	struct node *left,*right,*parent;
	char key;
};
struct treap {
	struct node *root;
};

struct node *node_new(char key,struct node *l,struct node *r,struct node *pare,int priority) {
	struct node *p;
	p = malloc(sizeof(struct node));
	if(p == NULL) return NULL;
	p->left = l;
	p->right = r;
	p->parent = pare;
	p->key = key;
	p->priority = priority;
	return p;
}
static void left_rotate(struct node *n,struct node **root) {
	struct node *p;

	p = n->right;
	n->right = p->left;
	if(p->left)
		p->left->parent = n;
	p->left = n;
	p->parent = n->parent;
	if(n->parent) {
		if(n->parent->left == n)
			n->parent->left = p;
		else
			n->parent->right = p;
	}
	n->parent = p;
	if(*root == n) {	//if the root is changed
		*root = p;
	}
}
static void right_rotate(struct node *n,struct node **root) {
	struct node *p;

	p = n->left;
	n->left = p->right;
	if(p->right)
		p->right->parent = n;
	p->right = n;
	p->parent = n->parent;
	if(n->parent) {
		if(n->parent->left == n)
			n->parent->left = p;
		else
			n->parent->right = p;
	}
	n->parent = p;
	if(*root == n) {	//if the root is changed
		*root = p;
	}
}
struct treap* treap_new() {
	struct treap *ret;
	ret = malloc(sizeof(struct treap));
	if(ret != NULL)
		ret->root = NULL;
	return ret;
}
void node_free(struct node *n) {
	if(n != NULL) {
		node_free(n->left);
		node_free(n->right);
		free(n);
	}
}
void treap_free(struct treap *t) {
	node_free(t->root);
	free(t);
}
static void _treap_insert(struct treap *t,char key,int priority) {
	struct node *p,*parent;

	if(t->root == NULL) {
		p = node_new(key,NULL,NULL,NULL,priority);
		t->root = p;
		return;
	} else {
		p = t->root;
		while(p) {
			parent = p;
			if(key < p->key) {
				p = p->left;
			} else {
				p = p->right;
			}
		}
		p = node_new(key,NULL,NULL,parent,priority);
		if(key < parent->key) {
			parent->left = p;
		} else {
			parent->right = p;
		}
		//rotate
		while(parent && p->priority < parent->priority) {
			if(parent->left == p) {
				right_rotate(parent,&t->root);
			} else {
				left_rotate(parent,&t->root);
			}
			parent = p->parent;
		}
		if(parent == NULL) {
			t->root = p;
		}
	}
}
void treap_insert(struct treap *t,char key) {
	if(t->root == NULL) {
		srand(time(NULL));
	}
	_treap_insert(t,key,rand()%300);
}
void treap_delete(struct treap *t,char key) {
	struct node *n,*p;

	n = t->root;
	while(n && n->key!=key) {
		if(key > n->key) 
			n = n->right;
		else
			n = n->left;
	}
	if(n == NULL) return;
	while(n->left && n->right) {
		if(n->left->priority < n->right->priority)
			right_rotate(n,&t->root);
		else 
			left_rotate(n,&t->root);
	}
	p = n->left? n->left:n->right;
	if(p)
		p->parent = n->parent;
	if(n->parent->left == n)
		n->parent->left = p;
	else
		n->parent->right = p;
	n->left = n->right = NULL;	//ATTENTION!
	node_free(n);
	return;
}
void node_print(struct node *n,int tabs) {
	if(n != NULL) {
		int i;
		node_print(n->right,tabs+1);
		for(i=0; i<tabs; i++) {
			printf("\t");
		}
		printf("%c(%d)\n",n->key,n->priority);
		node_print(n->left,tabs+1);
	}
}
void treap_print(struct treap *t) {
	node_print(t->root,0);
}

int main() {
	struct treap *t;
	char c;

	t = treap_new();	
	//_treap_insert(t,'A',187);
	//_treap_insert(t,'B',215);
	//_treap_insert(t,'C',238);
	//_treap_insert(t,'D',140);
	//_treap_insert(t,'E',239);
	//_treap_insert(t,'F',180);
	//_treap_insert(t,'G',101);
	//_treap_insert(t,'H',180);
	//_treap_insert(t,'I',104);
	//_treap_insert(t,'J',239);
	for(c='A'; c<'K'; c++) {
		treap_insert(t,c);
	}
	treap_print(t);
	printf("\n......................................................\n");
	treap_delete(t,'G');
	treap_delete(t,'F');
	treap_print(t);
	treap_free(t);
	return 0;
}

#include <stdio.h>

struct node {
	struct node *left;
	struct node *right;
};

typedef (*cmpfunc_t)(struct node*, struct node*);
struct bstree {
	struct node *root;
	cmpfunc_t cmp;
};

void insert(struct bstree *tree, struct node *n) {
	struct node *p,*q;
	int cmp;

	q = NULL;
	p = tree->root;
	while(p) {
		cmp = tree->cmp(n,p);
		if(cmp > 0) {
			q = p;
			p = p->right;
		} else if(cmp < 0) {
			q = p;
			p = p->left;
		} else {
			n->left = p->left;
			n->right = p->right;
			if(q->left == p)
				q->left = n;
			else
				q->right = n;
			//free(p);	//is it ok?
			return;
		}
	}
	if(q == NULL) {
		tree->root = n;
		return;
	}
	if(cmp > 0) {
		q->right = n;
	} else {
		q->left = n;
	}
}

#ifdef _BST_TEST
#include <stdlib.h>
struct int_t {
	struct node n;
	char key;
	int value;
};

int charcmp(struct node *n1,struct node *n2) {
	if( ((struct int_t*)n1)->key > ((struct int_t*)n2)->key)
		return 1;
	else if ( ((struct int_t*)n1)->key < ((struct int_t*)n2)->key)
		return -1;
	return 0;
}

void print(struct int_t *node, int tab) {
	int i;
	if(node == NULL) 
		return;
	print(node->n.right, tab+1);
	for(i=0; i<tab; i++)
		printf("\t");
	printf("(%c,%d)\n",node->key,node->value);
	print(node->n.left,tab+1);
}

int main() {
	struct int_t a,b,c,d,e,f,g;
	struct bstree tree;
	
	a.key = 'a';
	a.value = 1;
	a.n.left = 0;
	a.n.right = 0;

	b.key = 'b';
	b.value = 2;
	b.n.left = 0;
	b.n.right = 0;

	c.key = 'c';
	c.value = 3;
	c.n.left = 0;
	c.n.right = 0;

	d.key = 'd';
	d.value = 4;
	d.n.left = 0;
	d.n.right = 0;

	e.key = 'e';
	e.value = 5;
	e.n.left = 0;
	e.n.right = 0;

	f.key = 'f';
	f.value = 6;
	f.n.left = 0;
	f.n.right = 0;

	g.key = 'g';
	g.value = 7;
	g.n.left = 0;
	g.n.right = 0;

	tree.root = NULL;
	tree.cmp = charcmp;

	insert(&tree,&c.n);
	print(tree.root,0);
	insert(&tree,&e.n);
	print(tree.root,0);
	insert(&tree,&a.n);
	print(tree.root,0);
	insert(&tree,&f.n);
	print(tree.root,0);
	insert(&tree,&g.n);
	print(tree.root,0);
	insert(&tree,&b.n);
	print(tree.root,0);
	insert(&tree,&d.n);

	print(tree.root,0);
	return 0;
}
#endif

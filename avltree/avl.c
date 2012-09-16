#include <stdio.h>
#include <stdlib.h>

static inline int max(int a,int b) {
       return a>b ? a:b;
}
struct node {
	struct node *left;
	struct node *right;
	int height;
};
typedef int (*cmpfunc_t)(struct node*,struct node*);
typedef void (*setfunc_t)(struct node*,struct node*);
struct avltree {
	struct node *root;
	cmpfunc_t cmp;
	setfunc_t set;
	struct node ***stack;
	int use;
	int cap;
};

struct avltree* avltree_create(cmpfunc_t cmp, setfunc_t set) {
	struct avltree *ret;

	ret = malloc(sizeof(struct avltree));
	ret->root = NULL;
	ret->cmp = cmp;
	ret->set = set;
	ret->stack = malloc(20*sizeof(struct node **));
	ret->use = 0;
	ret->cap = 20;
}
static inline void push(struct avltree *tree,struct node **p) {
	tree->stack[tree->use] = p;
	tree->use++;
	if(tree->use == tree->cap) {
		tree->stack = (struct node ***)realloc(tree->stack,2*tree->cap*sizeof(struct node**));
		tree->cap *= 2;
	}
}
static inline struct node** pop(struct avltree *tree) {
	tree->use--;
	return tree->stack[tree->use];
}
static inline int empty(struct avltree *tree) {
	return tree->use == 0;
}
static inline void clear(struct avltree *tree) {
	tree->use = 0;
}
static inline int height(struct node *p) {
	return p==NULL ? -1 : p->height;
}
static void LL(struct node** rt)
{
/*
 *          p          lc
 *         /             \
 *        /               \
 *      lc                 p
 */
	struct node *p,*lc;
	p = *rt;
	lc = p->left;
	p->left=lc->right;
	lc->right=p;
	*rt = lc;

	p->height = max(height(p->left), height(p->right)) + 1;
	lc->height = max(height(lc->left), height(lc->right)) + 1;
}
static void RR(struct node **rt)
{
/*
 *      p                 p
 *       \               /
 *        \             /
 *         rc          rc
 */
	struct node *p = *rt;
	struct node *rc = p->right;
	p->right = rc->left;
	rc->left = p;
	p->height = max(height(p->left),height(p->right))+1;
	rc->height = max(height(rc->left),height(p->right))+1;
	*rt = rc;
}
static inline void LR(struct node** rt)
{
/*
 *        K3        K3        K2
 *       /         /         /  \
 *      /         /         /    \
 *     K1        K2        K1    K3
 *      \       /
 *       \     /
 *        K2  K1
 */
	RR(&((*rt)->left));
	LL(rt);
}
static inline void RL(struct node **rt)
{
/*
 *       K3       K3          K2
 *         \       \         /  \
 *          \       \       /    \
 *          K1      K2     K3    K1
 *          /         \
 *         /           \
 *        K2           K1
 */
	LL(&((*rt)->right));
	RR(rt);
}
void adjust(struct node **p) {
	int balance;

	balance = height((*p)->left) - height((*p)->right);
	if(balance == 2) {
		if(height((*p)->left->left) > height((*p)->left->right))
		       LL(p);	
		else
			LR(p);
	} else if(balance == -2) {
		if(height((*p)->right->right) > height((*p)->right->left))
			RR(p);
		else
			RL(p);
	}
}
//返回值指向空指针说明没有找到
//否则返回值指向一个非空指针
//这个函数用的时候要小心，有副作用,把tree的栈改写了
struct node** avltree_find(struct avltree *tree,struct node *n) {
	struct node **p;
	int cmp;

	p = &tree->root;
	while(*p) {
		push(tree,p);
		cmp = tree->cmp(n,*p);
		if(cmp > 0)
			p = &((*p)->right);
		else if(cmp < 0)
			p = &((*p)->left);
		else { 
			clear(tree);
			break;
		}
	}
	return p;
}
void avltree_adjust(struct avltree *tree) {
	struct node **p;

	while(!empty(tree)) {
		p = pop(tree);
		adjust(p);
	}
}
void avltree_insert(struct avltree *tree, struct node *n) {
	struct node **p;
	int cmp;

	//寻找插入位置
	clear(tree);
	p = avltree_find(tree,n);
	//插入结点
	n->left = NULL;
	n->right = NULL;
	n->height = 0;
	if(*p != NULL) {
		tree->set(*p,n);
		return;
	}
	*p = n;
	//调整
	avltree_adjust(tree);
}

#ifdef 0
#include <string.h>
struct kvnode {
	struct node avl;
	char *key;
	int val;
	struct kvnode *next;
};
int cmpf(struct node *n1,struct node *n2) {
	struct kvnode *kvn1, *kvn2;
	kvn1 = (struct kvnode*)n1;
	kvn2 = (struct kvnode*)n2;
	return strcmp(kvn1->key,kvn2->key);
}
void setf(struct node *n1,struct node *n2) {
	struct kvnode *kvn1,*kvn2;
	kvn1 = (struct kvnode*)n1;
	kvn2 = (struct kvnode*)n2;
	kvn1->key = kvn2->key;
	kvn1->val = kvn2->val;
	free(n2);
}
struct kvnode* node_create(char *key,int val) {
	struct kvnode *ret;
	ret = malloc(sizeof(struct kvnode));
	memset(&ret->avl,0,sizeof(struct node));
	ret->key = key;
	ret->val = val;
	return ret;
}
void print(struct kvnode *node, int tab) {
	int i;
	if(node == NULL) 
		return;
	print(node->avl.right, tab+1);
	for(i=0; i<tab; i++)
		printf("\t");
	printf("(%s,%d)\n",node->key,node->val);
	print(node->avl.left,tab+1);
}
int main() {
	struct avltree *tree;
	struct kvnode head;
	struct kvnode *tail;

	struct kvnode *p;
	char buf[200];
	int retval;
	char *str;
	struct node **ins;

	FILE *f = fopen("bible.txt","r");
	int start,end;

	tail = &head;
	tree = avltree_create(cmpf, setf);


	start = clock();
	while((retval = fscanf(f,"%s",buf)) != EOF) {
		str = malloc(strlen(buf)+1);
		strcpy(str,buf);
		p = node_create(str,1);
		ins = avltree_find(tree,p);
		if(*ins == NULL) {	//第一次
			*ins = p;
			avltree_adjust(tree);
			tail->next = p;
			tail = p;
		} else {	//直接插，不用平衡调整了
			((struct kvnode*)(*ins))->val ++;
		}
	}
	end = clock();
	printf("%d\n",end-start);
	/*
	for(p=head.next; p!=tail; p=p->next) {
		printf("%s,%d\n",p->key,p->val);
	}*/
	return 0;
}
#endif

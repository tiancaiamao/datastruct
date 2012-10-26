#include <stdio.h>

struct node {
	struct node *left;
	struct node *right;
	int value;
};

struct node *stack[200];
int _top = 0;
int empty() {
	return _top == 0;
}
void push(struct node *p) {
	stack[_top] = p;
	_top++;
}
struct node *pop() {
	--_top;
	return stack[_top];
}
struct node *top() {
	return stack[_top-1];
}
void in_order(struct node *root) {
	struct node *p = root;
	while(p || !empty()) {
		if(p) {
			push(p);
			p = p->left;
		} else {
			p = pop();
			printf("%d ",p->value);
			p = p->right;
		}
	}
}
void in_order_cur(struct node *root) {
	if(root == NULL)
		return;
	in_order_cur(root->left);
	printf("%d ",root->value);
	in_order_cur(root->right);
}
/* 只有从右树回来的时候才可以访问，第一次遇到的时候不能访问
 * 记一个lastvist用于做这个事情
 */
void post_order(struct node *root) {
	struct node *lastvisit, *p;

	lastvisit = NULL;
	p = root;
	while(p || !empty()) {
		if(p) {
			push(p);
			p = p->left;
		} else {
			p = top();
			if(!p->right || p->right==lastvisit) {
				p = pop();
				printf("%d ",p->value);
				lastvisit = p;
				p = NULL;
			} else {
				p = p->right;
			}
		}
	}
}
int main() {
	struct node root,a,b,c,d,e,f;

	root.value = 1;
	a.value = 2;
	b.value = 3;
	c.value = 4;
	d.value = 5;
	e.value = 6;
	f.value = 7;

	root.left = &a;
	root.right = &b;
	a.left = &c;
	a.right = &d;
	c.left = c.right = NULL;
	d.left = NULL;
	d.right = &e;
	e.left = e.right = NULL;
	b.left = NULL;
	b.right = &f;
	f.left = f.right = NULL;
	
	post_order(&root);
	return 0;
}

#ifndef AVLTREE_H
#define AVLTREE_H

#define Elemtype int
typedef struct node
{
    Elemtype data;
    int height;
    struct node* left,*right;
}node,*pnode;
typedef node* avltree;
avltree insert(avltree root,Elemtype data);
#endif // AVLTREE_H

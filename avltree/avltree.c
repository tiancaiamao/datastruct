#include "avltree.h"
static inline MAX(int a,int b)
{
    return a>b?a:b;
}
static inline HEIGHT(pnode p)
{
    if(!p)
        return -1;
    return p->height;
}
static pnode LL(pnode p)
{
/*
 *          p          lc
 *         /             \
 *        /               \
 *      lc                 p
 */
    pnode lc=p->left;
    p->left=lc->right;
    lc->right=p;
    p->height=MAX(HEIGHT(p->left),HEIGHT(p->right))+1;
    lc->height=MAX(HEIGHT(lc->left),HEIGHT(lc->right))+1;
    return lc;
}
static pnode RR(pnode p)
{
/*
 *      p                 p
 *       \               /
 *        \             /
 *         rc          rc
 */
    pnode rc=p->right;
    p->right=rc->left;
    rc->left=p;
    p->height=MAX(HEIGHT(p->left),HEIGHT(p->right))+1;
    rc->height=MAX(HEIGHT(rc->left),HEIGHT(p->right))+1;
    return rc;
}
static pnode LR(pnode K3)
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
    K3->left=RR(K3->left);
    return LL(K3);
}
static pnode RL(pnode K3)
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
    K3->right=LL(K3->left);
    return RR(K3);
}
avltree insert(avltree root,Elemtype data)
{
    if(!root)
    {
        root=(pnode)malloc(sizeof(node));
        root->data=data;
        root->left=root->right=0;
        root->height=0;
    }
    else if(data < root->data)    //插到左边
    {
        root->left=insert(root->left,data);
        if(HEIGHT(root->left)-HEIGHT(root->right)==2)   //失去平衡
        {
            if(data < root->left->data)
                root=LL(root);
            else
               root=LR(root);
        }
    }
    else if(data >root->data)   //插到右边
    {
        root->right=insert(root->right,data);
        if(HEIGHT(root->right)-HEIGHT(root->left)==2)   //失去平衡
        {
            if(data > root->right->data)
                root=RR(root);
            else
                root=RL(root);
        }
    }
    //data在树中已存在时什么事也不做
    root->height=MAX(HEIGHT(root->left),HEIGHT(root->right))+1;
    return root;
}


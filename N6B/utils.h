#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>

typedef int Elemtype;
//结点结构定义
typedef struct node
{
        Elemtype data;
        struct node* next;
}node,*pnode;
//创建结点
static inline pnode makenode(Elemtype data,pnode p)
{
    pnode tmp=(pnode)malloc(sizeof(node));
    if(tmp)
    {
        tmp->data=data;
        tmp->next=p;
    }
    return tmp;
}
//在给定结点后面插入
static inline pnode insert(pnode p,Elemtype data)
{
    pnode tmp=(pnode)malloc(sizeof(node));
    tmp->data=data;
    tmp->next=p->next;
    p->next=tmp;
    return tmp;
}
//结点指针前移
static inline void advance(pnode* p,int n)
{
    while((*p)&&n>0)
    {
        (*p)=(*p)->next;
        n--;
    }
}
#endif // UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

void show(pnode p,int w)
{
    if(p)
    {
        show(p->right,w+5);
        printf("%*d\n",w,p->data);
        show(p->left,w+5);
    }
}
int main()
{
        pnode root = NULL;

        root = insert(root,1);
        root = insert(root,2);
        root = insert(root,3);
        root = insert(root,4);
        root = insert(root,5);
        show(root,0);
        return 0;
}

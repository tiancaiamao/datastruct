#include "hash.h"
#include <stdio.h>
void printstat(hash h)
{
    printf("table表:\n");
    int i;
    for(i=0;i<h.totalsize;++i)
    {
        printf("%d\n",h.table[i]);
    }
    printf("buff表:\n");
    for(i=0;i<h.buffcurrent;++i)
    {
        printf("编号%d next值 %d,key值%d data值　%d\n",i,h.buff[i].next,h.buff[i].key,h.buff[i].data);
    }
    printf("buff表的size:%d\n",h.buffsize);
}
int main()
{
    hash h;
    createhash(&h,6,0);
    insert(&h,1,6);
    insert(&h,2,4);
    insert(&h,3,5);
    insert(&h,4,435);
    insert(&h,5,7);
    insert(&h,6,9);
    insert(&h,7,33);
    insert(&h,8,345);
    insert(&h,9,34);
    insert(&h,10,94);
    insert(&h,23,46);
    insert(&h,21,46);
    insert(&h,46,4);
    insert(&h,555,2);
    insert(&h,444,24);
    insert(&h,666,234);
    int result;
    if(search(&h,23,&result)==0)
        printf("找到%d",result);
    remove1(&h,10);
    if(search(&h,10,&result)==0)
        printf("找到%d",result);
    //printstat(h);
    destroyhash(&h);
    return 0;
}

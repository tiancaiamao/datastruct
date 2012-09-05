#include "heap.h"
//大根堆
//i的左右子树都已成堆，调整使i到n成堆
void adjust(T heap[],int i,int n)
{
    T tmp=heap[i];
    int j=2*i+1;
    while(j<n)
    {
        if(j+1<n&&heap[j]<heap[j+1])   //j是i左右子树中较大的一个
            ++j;
        if(heap[j]>tmp)     //如果heap[j]比tmp大,则heap[j]向上浮
        {
            heap[i]=heap[j];
            i=j;
            j=j*2+1;
        }
        else
            break;
    }
    heap[i]=tmp;        //最后把tmp放回
}
//建堆
void createheap(T heap[],int n)
{
    int i;
    for(i=(n-2)/2;i>=0;--i)
    {
        adjust(heap,i,n);
    }
}
//堆排序
void heapsort(T heap[],int n)
{
    createheap(heap,n);
    int i;
    for(i=n-1;i>0;--i)
    {   T tmp=heap[0];      //堆顶拿出去
        heap[0]=heap[i];
        heap[i]=tmp;
        adjust(heap,0,i);     //调整
    }
}

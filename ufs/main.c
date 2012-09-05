#include <stdio.h>
void createufs(int array[],int n)
{
    int i;
    for(i=0;i<n;++i)
        array[i]=-1;
}
void merge(int array[],int r1,int r2)
{
    array[r1]+=array[r2];
    array[r2]=r1;
}
int find(int array[],int r)
{
    while(array[r]>0)
    {
        r=array[r];
    }
    return r;
}
int main()
{
    int array[10];
    createufs(array,10);
    merge(array,0,6);
    merge(array,0,7);
    merge(array,0,8);
    merge(array,1,4);
    merge(array,1,9);
    merge(array,2,3);
    merge(array,2,5);
    merge(array,0,1);
    merge(array,1,find(array,5));
    int i;
    for(i=0;i<10;++i)
        printf("%d ",array[i]);
    return 0;
}

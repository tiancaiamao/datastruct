#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    void adjustHeap(int* array,int s,int m); //s是堆顶位置...s的子树都是堆了.调整使整个array成堆 
    void heapsort(int* array,int n);            //堆排序算法 
    int a[8]={49,38,65,97,76,13,27,49};
    heapsort(a,8);
    cout<<"排序后"<<endl;
    for(int i=0;i<8;i++)
        cout<<a[i]<<' ';
    system("PAUSE");
    return EXIT_SUCCESS;
}
void adjustHeap(int* array,int s,int m)     //最大堆 
{
    int temp=array[s];
    int pos=2*s+1;
    while(pos<=m)
    {
        if(pos+1<=m&&array[pos]<array[pos+1])
            pos=pos+1;
        if(temp<array[pos])
        {
            array[s]=array[pos];
            s=pos;
            pos=2*pos+1;
        }
        else 
            break;
    }
    array[s]=temp;
}
void heapsort(int* array,int n)     
{
    int i;
    for(i=n/2;i>=0;i--)      //建堆过程 
    {
        adjustHeap(array,i,n);
    }
    for(i=n-1;i>0;i--)
    {
        int temp=array[0];      //堆顶和最后一个元素交换 
        array[0]=array[i];
        array[i]=temp;
        adjustHeap(array,0,i-1);                        //重新调整堆 
    }
}

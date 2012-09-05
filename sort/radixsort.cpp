#include <cstdlib>
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

int main(int argc, char *argv[])
{
    void shellsort(int *a,int n,int d);       //对数组a的数基数排序,其中,数组内有n个数,每个
                                              //数字是d位数 
    int a[9]={91,6,85,15,92,35,30,22,39};
    cout<<"排序前..."<<endl;
    for(int i=0;i<9;i++)
        cout<<a[i]<<' '; 
    shellsort(a,9,2);
    cout<<'\n'<<"排序后"<<endl;
    for(int i=0;i<9;i++)
        cout<<a[i]<<' ';                                         
    system("PAUSE");
    return EXIT_SUCCESS;
}
void shellsort(int* a,int n,int d)        
{
    queue<int> l[10];    //10个队列用来装0到9
    int i,j,k;
    for(i=0;i<d;i++)        //对每一位
    {
        for(j=0;j<n;j++)        //的每一个数 
        {
            l[a[j]/int(pow(10.0,i))%10].push(a[j]);       //根据位的值把数放到相应的队列 
        }
        int m=0;
        for(k=0;k<10;k++)       //出队列,把值放回到数组a 
        {
            while(!l[k].empty())
            {
                a[m]=l[k].front();
                l[k].pop();
                m++;
            }
        }
    }
}

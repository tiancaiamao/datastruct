#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    void insertsort(int* array,int n);
    int a[10]={49,38,65,97,76,13,27,49,55,4};
    insertsort(a,10);
    for(int i=0;i<10;i++)
        cout<<a[i]<<' ';
    cout<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
void insertsort(int* array,int n)
{
    for(int i=1;i<n;i++)        //从第2个开始...每次插一个 
    {
        //从0到i-1找a[i]的插入位置,用二分查找方式实现 
        int low=0,high=i;       //注意这里high的上界...这么设是有目的的 
        while(low<high)
        {
            if(array[i]<array[(low+high)/2])
            {
                high=(low+high)/2-1;
            }
            else //if(array[i]<array[(low+high)/2])
            {
                low=(low+high)/2+1;
            }           
        } //做完这个之后low>=high了,做插入 
        cout<<"插入位置"<<low<<endl;
        cout<<high<<endl;
        int temp=array[i];
        for(int j=i;j>low;j--)
        {
            array[j]=array[j-1];
        }
        array[low]=temp;
    }
}

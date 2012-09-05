#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{    
    void quicksort(int* array,int n);
    int a[8]={49,38,65,97,76,13,27,49};
    quicksort(a,8);
    for(int m=0;m<8;m++)
        cout<<a[m]<<' ';
    system("PAUSE");
    return EXIT_SUCCESS;
}
void quick(int* array,int low,int high);
void quicksort(int* array,int n)
{   
    quick(array,0,n-1);
}
void quick(int* array,int low,int high)
{
    if(low>=high)
        return;
    int i=low,j=high;
    int temp=array[low];
    while(i<j)
    {
        while(i<j&&array[j]>=temp)
            j--;
        array[i]=array[j];
        while(i<j&&array[i]<=temp)
            i++;
        array[j]=array[i];
    }
    array[i]=temp;
    quick(array,low,i-1);
    quick(array,i+1,high);
}

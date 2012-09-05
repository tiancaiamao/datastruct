#include <iostream>
#include <list>
#include <iterator>
using namespace std;

template <class T>
void mergesort(list<T>& l)
{
    list<T> temp;
    list<T> container[64];
    int fill=0;
    while(!l.empty())
    {
        temp.splice(temp.begin(),l,l.begin());
        int i=0;
        while(i<fill&&!container[i].empty())
        {
            temp.merge(container[i++]);
        }
        temp.swap(container[i]);
        if(i==fill) ++fill;
    }
    for(int i=0;i<fill;++i)
    {
        container[i+1].merge(container[i]);
    }
    l.swap(container[fill]);
}
int main()
{
    int a[6]={5,86,98,42,1,54};
    list<int> l(a,a+6);
    mergesort(l);
    copy(l.begin(),l.end(),ostream_iterator<int>(cout," "));
    return 0;
}

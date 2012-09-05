#ifndef ALGORITHM_H
#define ALGORITHM_H
namespace N6B
{
    template <class InputIterator,class Function>
    Function for_each(InputIterator first,InputIterator last,Function f)
    {
        while(first!=last) 
            f(*first++);
        return f;
    }
    template <class InputIterator,class T>
    InputIterator find(InputIterator first,InputIterator last,const T& value)
    {
        while(!(*first==value)&&first!=last)
            ++first;
        return first;
    }
    template <class InputIterator,class Pred>
    InputIterator find_if(InputIterator first,InputIterator last,Pred p)
    {
        while(!p(*first)&&first!=last)
            ++first;
        return first;
    }
    template <class ForwardIterator>
    ForwardIterator adjacent_find(ForwardIterator first,ForwardIterator last)
    {
        if(first==last)
            return first;
        ForwardIterator temp=first;
        while((*first!=*++temp)&&temp!=last)
            ++first;
        return first;
    }
    template <class ForwardIterator,class BinaryPred>
    ForwardIterator adjacent_find(ForwardIterator first,ForwardIterator last,BinaryPred p)
    {
        if(first==last)
            return first;
        ForwardIterator temp=first;
        while(!p(*temp,*first)&&temp!=last)
            ++first;
        return first;
    }
    template <class InputIterator,class OutputIterator,class UinaryPred>
    InputIterator copy_if(InputIterator first1,InputIterator last1,OutputIterator first2,UinaryPred pred)
    {
        while(first1!=last1)
        {
            if(pred(*first1))
                *first2++=*first1;
            ++first1;
        }
    }
}
#endif // ALGORITHM_H

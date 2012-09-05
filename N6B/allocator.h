#ifndef ALLOCATOR_H
#define ALLOCATOR_H

//这个文件在stl中对应到SGI的allocator.SGI中的allocator继承自___glibcxx_base_allocator<_Tp>
//___glibcxx_base_allocator<_Tp>实质上是文件new_allocator.h

#include <new>      //为了调用placement new
#include <cstddef>  //包含size_t,ptrdiff_t定义

namespace N6B
{
    template <class T>
    inline T* _allocate(ptrdiff_t size,T*)
    {
        T* tmp=static_cast<T*>(::operator new(static_cast<size_t>(size*sizeof(T))));    //申请rawmemory
        return tmp;
    }
    template <class T>
    inline void _construct(T* p,const T& value)     //初始化内存
    {
        new(p) T(value);      //placement new
    }
    template <class T>
    inline void _deallocate(T* buff)       //销毁内存空间
    {
        ::operator delete(buff);
    }
    template <class T>
    inline void _destroy(T* p)              //析构
    {
        p->~T();
    }
    template <class T>
    class allocator
    {
    public:
        //定义类型名称
        typedef T                   value_type;
        typedef T*                  pointer;
        typedef const T*            const_pointer;
        typedef T&                  reference;
        typedef const T&            const_reference;
        typedef size_t              size_type;
        typedef ptrdiff_t           difference_type;

        //这个定义不知道是干什么用的
        template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };

        pointer allocate(size_t n,const void* = 0)  //第二个参数其实可以无视.但必须定义,为了匹配参数
        {
            return _allocate(difference_type(n),pointer(0));
        }
        void deallocate(pointer p,size_t n)
        {
            _deallocate(p);
        }
        void construct(pointer p,const T& value)
        {
            _construct(p,value);
        }
        void destroy(pointer p)
        {
            _destroy(p);
        }
        pointer address(reference x)
        {
            return static_cast<pointer>(&x);
        }
        const_pointer address(const_reference x)
        {
            return static_cast<const_pointer>(&x);
        }


    };
}
#endif // ALLOCATOR_H

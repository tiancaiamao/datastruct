// Allocators -*- C++ -*-

// Copyright (C) 2001, 2002, 2003, 2004 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

/*
 * Copyright (c) 1996-1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/** @file ext/pool_allocator.h
 *  This file is a GNU extension to the Standard C++ Library.
 *  You should only include this header if you are using GCC 3 or later.
 */
#ifndef _POOL_ALLOCATOR_H
#define _POOL_ALLOCATOR_H 1

#include <bits/c++config.h>
#include <cstdlib>
#include <new>
#include <bits/functexcept.h>
#include <bits/atomicity.h>
#include <bits/concurrence.h>

namespace __gnu_cxx
{
  /**
   *  @if maint
   *  Uses various allocators to fulfill underlying requests (and makes as
   *  few requests as possible when in default high-speed pool mode).
   *
   *  Important implementation properties:
   *  0. If globally mandated, then allocate objects from new
   *  1. If the clients request an object of size > _S_max_bytes, the resulting
   *     object will be obtained directly from new
   *  2. In all other cases, we allocate an object of size exactly
   *     _S_round_up(requested_size).  Thus the client has enough size
   *     information that we can return the object to the proper free list
   *     without permanently losing part of the object.
   *
   *  @endif
   *  (See @link Allocators allocators info @endlink for more.)
   */
    class __pool_alloc_base           //_pool_alloc的基类,这不是一个模板类
    {
    protected:

      enum { _S_align = 8 };          //不用const int而用enum
      enum { _S_max_bytes = 128 };       //大于_S_max_bytes就直接用new分配
      enum { _S_free_list_size = _S_max_bytes / _S_align };
      
      union _Obj
      {
	union _Obj* _M_free_list_link;
	char        _M_client_data[1];    // The client sees this.
      };
      
      static _Obj* volatile         _S_free_list[_S_free_list_size];

      // Chunk allocation state.
      static char*                  _S_start_free;        //内存池开始位置
      static char*                  _S_end_free;            //内存池结束位置
      static size_t                 _S_heap_size;     
      
      size_t
      _M_round_up(size_t __bytes)       //将_bytes上调到8的倍数...做法是加个7,再把低3位全变0
      { return ((__bytes + (size_t)_S_align - 1) & ~((size_t)_S_align - 1)); }
      
      _Obj* volatile*
      _M_get_free_list(size_t __bytes);
    
      mutex_type&
      _M_get_mutex();

      // Returns an object of size __n, and optionally adds to size __n
      // free list.
      void*
      _M_refill(size_t __n);
      
      // Allocates a chunk for nobjs of size size.  nobjs may be reduced
      // if it is inconvenient to allocate the requested number.
      char*
      _M_allocate_chunk(size_t __n, int& __nobjs);
    };


  template<typename _Tp>
    class __pool_alloc : private __pool_alloc_base   //_pool_alloc是一个提供标准接口的allocator
    {
    private:
      static _Atomic_word	    _S_force_new;    //typedef int  _Atomic_word._S_force_new是定义是否用到线程相关的,跟过不看

    public:
      typedef size_t     size_type;
      typedef ptrdiff_t  difference_type;
      typedef _Tp*       pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp&       reference;
      typedef const _Tp& const_reference;
      typedef _Tp        value_type;

      template<typename _Tp1>
        struct rebind
        { typedef __pool_alloc<_Tp1> other; };

      __pool_alloc() throw() { }

      __pool_alloc(const __pool_alloc&) throw() { }   //拷贝构造,定义这个是因为模板的构造函数在继承中不会被调用.

      template<typename _Tp1>
        __pool_alloc(const __pool_alloc<_Tp1>&) throw() { }  //模板的构造函数

      ~__pool_alloc() throw() { }

      pointer
      address(reference __x) const { return &__x; }

      const_pointer
      address(const_reference __x) const { return &__x; }

      size_type
      max_size() const throw() 
      { return size_t(-1) / sizeof(_Tp); }

      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 402. wrong new expression in [some_] allocator::construct
      void 
      construct(pointer __p, const _Tp& __val)     //构造
      { ::new(__p) _Tp(__val); }

      void 
      destroy(pointer __p) { __p->~_Tp(); }

      pointer                    //整个类中最重要的函数就是allocate和deallocate
      allocate(size_type __n, const void* = 0);

      void
      deallocate(pointer __p, size_type __n);      
    };

  template<typename _Tp>
    inline bool
    operator==(const __pool_alloc<_Tp>&, const __pool_alloc<_Tp>&)
    { return true; }

  template<typename _Tp>
    inline bool
    operator!=(const __pool_alloc<_Tp>&, const __pool_alloc<_Tp>&)
    { return false; }

  template<typename _Tp>
    _Atomic_word
    __pool_alloc<_Tp>::_S_force_new;

  template<typename _Tp>
    _Tp*
    __pool_alloc<_Tp>::allocate(size_type __n, const void*)  //注意第二个参数.这个参数没什么用,但不能省略.标准是这么定义的.
    {                                                        //分配的空间是n个_Tp的空间.而不是n个字节.
      pointer __ret = 0;
      if (__n)         //_n不等于0的情况
	{
          if (__n <= max_size())       //申请的大小没有超过最大允许范围时
	    {
	      // If there is a race through here, assume answer from getenv
	      // will resolve in same direction.  Inspired by techniques
	      // to efficiently support threading found in basic_string.h.
              if (_S_force_new == 0)      //跟线程有关的....跳过不看
		{
		  if (getenv("GLIBCXX_FORCE_NEW"))
		    __atomic_add(&_S_force_new, 1);
		  else
		    __atomic_add(&_S_force_new, -1);
		}

              const size_t __bytes = __n * sizeof(_Tp);	      //分配的空间是n个_Tp的空间.而不是n个字节._bytes就是字节大小
              if (__bytes > size_t(_S_max_bytes) || _S_force_new == 1)   //大于128字节时直接用operator new方式而不是内存池
                __ret = static_cast<_Tp*>(::operator new(__bytes));    //operator new
              else       //内存池分配方式
		{
		  _Obj* volatile* __free_list = _M_get_free_list(__bytes);

		  lock sentry(_M_get_mutex());
		  _Obj* __restrict__ __result = *__free_list;
		  if (__builtin_expect(__result == 0, 0))
		    __ret = static_cast<_Tp*>(_M_refill(_M_round_up(__bytes)));
		  else
		    {
		      *__free_list = __result->_M_free_list_link;
		      __ret = reinterpret_cast<_Tp*>(__result);
		    }
		  if (__builtin_expect(__ret == 0, 0))
		    std::__throw_bad_alloc();
		}
	    }
	  else
	    std::__throw_bad_alloc();
	}
      return __ret;
    }

  template<typename _Tp>
    void
    __pool_alloc<_Tp>::deallocate(pointer __p, size_type __n)   //注意第二个参数...不能省略,标准是这么定义的.要靠__n知道销毁多大内存,因为这里
    {                                                           //不能光靠类型来判断销毁多大空间.
      if (__n)
	{
	  const size_t __bytes = __n * sizeof(_Tp);
	  if (__bytes > static_cast<size_t>(_S_max_bytes) || _S_force_new == 1)
	    ::operator delete(__p);
	  else
	    {
	      _Obj* volatile* __free_list = _M_get_free_list(__bytes);
	      _Obj* __q = reinterpret_cast<_Obj*>(__p);

	      lock sentry(_M_get_mutex());
	      __q ->_M_free_list_link = *__free_list;
	      *__free_list = __q;
	    }
	}
    }
} // namespace __gnu_cxx

#endif

/********************************************************************
	Time:	  2015/10/22
	Filename: stlite_construct
	Author:	  dinglj
	
	Purpose:  ȫ�ֹ��졢��������
              SGI STL��������ڴ����͹����������ˡ�
              1.    construct(T1 *ptr, const T2 &value)
              2.    destroy_aux(ForwardIterator first, ForwardIterator last, xx_type)
              3.    destroy(ForwardIterator first, ForwardIterator last)

*********************************************************************/

#ifndef _STLITE_CONSTRUCT_H_
#define _STLITE_CONSTRUCT_H_

#include <new.h>    //  placement new
#include "stlite_type_traits.h"
#include "stlite_iterator.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

namespace STLite
{
    //  construct
    template<class T1, class T2>
    inline void construct(T1 *ptr, const T2 &value)
    {
        new(ptr) T1(value); //  placement new, ��ptr��ָ�ռ��Ϲ�������
    }
    //////////////////////////////////////////////////////////////////////

    //  deconstruct, ����Ϊdestroy������deconstruct?
    //  ��һ���汾
    template<class T>
    inline void destroy(T *ptr)
    {
        ptr->~T();
    }

    //  �ڶ����汾

    //////////////////////////////////////////////////////////////////////
    //  �Ȼ�ȡ��������ָ���ͣ����ݵ�������ָ���͵��ö�Ӧ��destroy����
    template<class ForwardIterator>
    inline void destroy_aux(ForwardIterator first, ForwardIterator last, __true_type)
    {
        //  if has_trivial_deconstructor, do nothing
        cout << "do nothing" << endl;
    }

    template<class ForwardIterator>
    inline void destroy_aux(ForwardIterator first, ForwardIterator last, __false_type)
    {
        //  if not has_trivial_deconstructor, call destroy(&*first)
        for (; first < last; first++)
        {
            destroy(&*first);
        }
    }

    template<class ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last)
    {
        //  note! �Ȼ�ȡ��������ָ���ͣ��ٸ��������ж��Ƿ�has trivial deconstructor
        typedef typename __type_traits<iterator_traits<ForwardIterator>::value_type>::has_trivial_deconstructor has_trivial_deconstructor;  
        destroy_aux(first, last, has_trivial_deconstructor());
    }

    /*
        Ϊʲôconstruct����destroy����һ�£�������
        construct(T *prt)
        construct(ForwardIterator first, ForwardIterator last, T value)

        ʵ���ϣ�SGI STL��ʹ����uninitialized.h�е�uninitialize_XX�����ȼ۴���construct(first, last, value)
    */
}

#endif
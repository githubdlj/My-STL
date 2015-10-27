/********************************************************************
	Time:	  2015/10/22
	Filename: stlite_alloc
	Author:	  dinglj
	
	Purpose:  �ڴ����������
              1��   ��򵥵��ڴ������� allocator(Ҳ��SGI��׼���ڴ�������)
              2��   һ�������� __malloc_alloc_template
              3��   ���������� __default_alloc_template

              4��   simple_alloc ���ڴ��������ķ�װ
*********************************************************************/

#ifndef _STLITE_ALLOC_H_
#define _STLITE_ALLOC_H_

#include "stlite_construct.h"    //  for construct, destroy
#include <new.h>    //  placement new, set_new_handler
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

namespace STLite
{
    //  allocate��deallocate
    template<class T>
    inline T* _allocate(ptrdiff_t size, T*)
    {
        set_new_handler(0);
        T *result = (T *) ::operator new((size_t) (size * sizeof(T)));
        if (0 == result)
        {
            std::cerr << "out of memory" << endl;
            exit(1);
        }
        else
        {
            cout << size * sizeof(T) << "byte memory has alloc" << endl;
        }

        return result;
    }

    template<class T>
    inline void _deallocate(T* buffer)
    {
        if (NULL != buffer)
        {
            cout << "free memory" << endl;
            ::operator delete(buffer);
        }
    }

    //////////////////////////////////////////////////////////////////////
    //  allocator
    //  allocator����VC�汾��STL��׼�ӿڣ�����ֱ��ʹ��
    template<class T>
    class allocator
    {
    public:
        //  �����SGI STL������Ϊ�������ڴ������������������µĽӿ�
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef ptrdiff_t   difference_type;
        typedef size_t      size_type;

        template<class U>
        struct rebind{
            typedef allocator<U> other;
        };

        static pointer allocate(size_type n)
        {
            return _allocate((difference_type)n, (pointer)0);
        }

        static void deallocate(pointer p, size_type n) //  VC��STL deallcate�ӿڴ�2������
        {
            _deallocate(p);
        }

        //////////////////////////////////////////////////////////////////////
        //  �����SGI STL,��Ϊ������������������Ҫ�ṩ����Ľӿڣ��������������ȫ�ֵ�construct������
        //  ���ڴ����ú͹����������ˡ�
        //  ���ǣ�vc�µ�STL�汾Ϊ��������������ṩ���½ӿڡ�
        static void construct(pointer p, const_reference value)
        {
            STLite::construct(p, value);  //  ����ȫ�ֵĹ��캯����λ��stlite_construct.h
                  
        }

        static void destroy(pointer p)
        {
            STLite::destroy(p);   //  ����ȫ�ֵ�����������λ��stlite.construct.h
        }
        
        //  Ч�ʸ��ߵ�destroy����
        static void destroy(pointer first, pointer last)
        {
            STLite::destroy(first, last);
        }
        //////////////////////////////////////////////////////////////////////
        size_type max_size()const
        {
            return size_type(-1) / sizeof(T);
        }
        
        //  constructor��Ϊ�˷���VC�汾STL�ӿڱ�׼
        allocator() {}
        allocator(const allocator &) {}
        
        template<class U>
        allocator(const allocator<U> &) {}
         
    };

    //  һ��������������SGI STL�汾�ӿ�
    //  �򵥵ķ�װ��malloc��free
    class __malloc_alloc
    {

    };

    //////////////////////////////////////////////////////////////////////
    //  ����������������SGI STL�汾�ӿ�
    //  ά���ڴ��������
    class __default_alloc
    {

    };

    //  ��һ���������������а�װ��ʹ���������Ӧ��STL�汾�ӿ�
    //  VC�汾��STL��SGI STL�ӿڲ�һ����
    template<class T, class Alloc>
    class simple_alloc
    {

    };
    //////////////////////////////////////////////////////////////////////

    //  
}

#endif
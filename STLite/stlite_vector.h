/********************************************************************
	Time:	  2015/10/26
	Filename: stlite_vector
	Author:	  dinglj
	
	Purpose:  vectorʵ��
*********************************************************************/
#ifndef _STLITE_VECTOR_H_
#define _STLITE_VECTOR_H_
#include "stlite_iterator.h"        //  iterator  
#include "stlite_alloc.h"           //  allocator
#include "stlite_uninitialized.h"   //  uninitialized_fill_n
#include "stlite_type_traits.h"
#include <crtdefs.h>                //  std::ptrdiff_t

#include <iostream>
using namespace STLite;

namespace STLite
{
    //////////////////////////////////////////////////////////////////////
    //  vectorIterator
    template<class T>
    class vectorIterator : public iterator<random_access_iterator<T, std::ptrdiff_t>, T>
    {
    private:
        T *m_ptr;
    
    //////////////////////////////////////////////////////////////////////
    //  construct, copy, assignment, destroy
    //  ע�⣬vectorIterator���������ڴ������ͷţ���������ԭʼָ���һ����װ
    //  ������Щ����������ʹ��Ĭ�ϵ�
    public:
        //  construct
        explicit vectorIterator(T *ptr = NULL) : m_ptr(ptr) {} 
        
        //  copy
        vectorIterator(const vectorIterator &vIter)
        {
            m_ptr = vIter.m_ptr;
        }

        // assignment
        vectorIterator & operator =(const vectorIterator &vIter)
        {
            if (this != &vIter)
            {
                m_ptr = vIter.m_ptr;
            }
            return *this;
        }

        //  destroy, do nothing,
        ~vectorIterator() { }
    //////////////////////////////////////////////////////////////////////
    //  defer
    public:
        reference operator *()      //    ������Ϊ��ֵ������ֵ
        {
            return *m_ptr;
        }
        pointer operator ->()
        {
            return m_ptr;
        }
    //////////////////////////////////////////////////////////////////////
    //  ++,--
    public:
        vectorIterator & operator ++()
        {
            m_ptr++;
            return *this;
        }
        vectorIterator operator ++(int)
        {
            vectorIterator temp = *this;
            ++(*this);
            return temp;
        }

        vectorIterator & operator --()
        {
            m_ptr--;
            return *this;
        }
        vectorIterator operator --(int)
        {
            vectorIterator temp = *this;
            --(*this);
            return temp;
        }
    //////////////////////////////////////////////////////////////////////
    //  �����ȡ����������
    public:
        vectorIterator & operator +=(difference_type n)
        {
            m_ptr += n;
            return *this;
        }

        vectorIterator operator +(difference_type n) const
        {
            vectorIterator temp = *this;    //  call operator +=(difference_type n)
            return temp += n;
        }

        difference_type operator +(const vectorIterator &lhs) const     //  �������ӷ�
        {
            return m_ptr + lhs.m_ptr;
        }
        //////////////////////////////////////////////////////////////////////
        vectorIterator & operator -=(difference_type n)
        {
            return *this += -n;    //  call operator +=(difference_type n)
        }

        vectorIterator operator -(difference_type n) const
        {
            vectorIterator temp = *this;    //  call operator -=(difference_type n)
            return temp -= n;
        }
        
        difference_type operator -(const vectorIterator &lhs) const     //  ����������
        {
            return m_ptr - lhs.m_ptr;
        }
        //////////////////////////////////////////////////////////////////////
        reference operator [](difference_type n) const
        {
            return *(*this + n);
        }
    //////////////////////////////////////////////////////////////////////
    //  operator ==, !=
    public:
        bool operator ==(const vectorIterator &lhs) const
        {
            return m_ptr == lhs.m_ptr;
        }

        bool operator !=(const vectorIterator &lhs) const
        {
            return !(*this == lhs);
        }
    };


    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //  vector
    template<class T, class Alloc = allocator<T>>
    class vector
    {
    //////////////////////////////////////////////////////////////////////
    //  Ƕ���ͱ���
    public:
        typedef T               value_type;
        typedef T*              pointer;
        typedef T&              reference;
        typedef size_t          size_type;
        typedef std::ptrdiff_t  difference_type;

    //////////////////////////////////////////////////////////////////////
    //   �ڲ�����,  Ϊ�˷�����ԣ�������Ϊpublic
    public:
        pointer start;
        pointer finish;
        pointer end_of_storage;     //  ָ��洢�ռ��ĩβ
    
    //////////////////////////////////////////////////////////////////////
    //  iterator
    public:
        typedef vectorIterator<T> iterator;
    
    //////////////////////////////////////////////////////////////////////
    //  allocator
    typedef allocator<T> data_allocator;

    //////////////////////////////////////////////////////////////////////
    //  private member function
    private:
        pointer allocate(size_type n)
        {
            return data_allocator::allocate(n);
        }
        
        void deallocate()
        {
            data_allocator::deallocate(start, end_of_storage - start);
        }
        //////////////////////////////////////////////////////////////////////
        
        void allocate_and_fill(size_type n, const value_type &value)
        {
            start = allocate(n);
            uninitialized_fill_n(start, n, value);
            
            finish = start + n;
            end_of_storage = finish;
        }
        
        template<class InputIterator>
        void allocate_and_copy(InputIterator first, InputIterator last)
        {
             start = allocate(last - first);     //  ���ص���������
             finish = uninitialized_copy(first, last, start);
             end_of_storage = finish;
        }
        
        void destroy_and_deallocate()
        {
            if (start != end_of_storage)
            {
                destroy(start, finish); 
                deallocate();
            }
        }
        //////////////////////////////////////////////////////////////////////
        //  override vector_aux
        template<class Integer>
        void vector_aux(Integer n, const value_type &value, __true_type)
        {
            allocate_and_fill(n, value);
        }
        
        template<class InputIterator>
        void vector_aux(InputIterator first, InputIterator last, __false_type)
        {
            allocate_and_copy(first, last);
        }   

    //////////////////////////////////////////////////////////////////////
    //  construct
    public: 
        vector(): start(0), finish(0), end_of_storage(0) { }
        explicit vector(size_type n)
        {
            vector_aux(n, value_type(), __true_type());
        }
        vector(size_type n, const value_type &value)
        {
            vector_aux(n, value, __true_type());
        }
        template<class InputIterator>
        vector(InputIterator first, InputIterator last)     
        {
            typedef typename _is_integer<InputIterator>::is_integer is_integer;    //  ע�⣬��vector<size_type n, const value_type &value>����һ����Ҫ�жϲ�������
            vector_aux(first, last, is_integer());
        }
        
        //  copy
        vector(const vector &lhs)
        {
            allocate_and_copy(lhs.start, lhs.finish);
        }
    
        //  assignment, ע�⣬��ֵ��ʱ��Ҫ�ͷ�ԭ����ָ����ڴ�ռ�
        const vector & operator =(const vector &lhs)
        {
            //  ��ʼ���¿ռ�
            pointer new_start = allocate(lhs.finish - lhs.start);
            pointer new_finish = uninitialized_copy(lhs.start, lhs.finish, new_start);
            pointer new_end_of_storage = new_finish;
        
            //  �ͷ�����ռ�
            destroy_and_deallocate();
    
            //  ��ʼ������ռ�
            start = new_start;
            finish = new_finish;
            end_of_storage = new_end_of_storage;

            return *this;
        }
        //  destroy
        ~vector()
        {
            destroy_and_deallocate();
        }
    //////////////////////////////////////////////////////////////////////
    //  iterators
    public:
        iterator begin()
        {
            return iterator(start);
        }
        
        iterator end()
        {
           return iterator(finish);
        }
    //////////////////////////////////////////////////////////////////////
    //  element access
    public:
        reference operator [](size_type n)
        {
            return *(start + n);
        }

        reference at(size_type n)
        {
            return operator [](n);  //  call operator [](n)
        }

        //  
        reference front()
        {
            return *begin();
        }

        reference back()
        {
            return *(end() - 1);
        }
    //////////////////////////////////////////////////////////////////////
    //  Capacity
    public:
        size_type size() const
        {
            return size_type(finish - start);
        }

        void resize(size_type n, const value_type &x)
        {
            if (n < size())
            {
                erase(begin() + n, end());
            }
            else
            {
                insert(end(), n - size(), x);
            }
        }

        void resize(size_type new_size)
        {
            resize(new_size, value_type());
        }
        //////////////////////////////////////////////////////////////////////
        size_type capacity() const
        {
            return size_type(end_of_storage - start);
        }

        void reserve(size_type n)
        {
            if (capacity() < n)     //  reserveֻ����������
            {
                //  allocate new space
                pointer new_start = allocate(n);
                pointer new_end_of_storage = new_start + n;
                
                //  copy
                pointer new_finish = uninitialized_copy(start, finish, new_start);
                
                //  free old space
                destroy_and_deallocate();
                
                //  init new space
                start = new_start;
                finish = new_finish;
                end_of_storage = new_end_of_storage;
            }
        }
    //////////////////////////////////////////////////////////////////////
    //  Modifiers
    //  insert_aux
    private:
        void insert_aux(iterator pos, size_type n, const T &value, __true_type)
        {
            size_type locationLeft = end_of_storage - finish;
            size_type locationNeed = n;

            if (locationNeed <= locationLeft)
            {
                iterator temp = pos;     //  [pos, finish) -> [pos + locationNeed, finish + locationNeed)
                while (temp != end())
                {
                    *(temp + locationNeed) = *(temp);
                    temp++;
                }
                uninitialized_fill_n(pos, locationNeed, value);

                finish = finish + locationNeed;
            }
            else
            {
                size_type old_size = size();
                size_type new_capacity = old_size + std::max(old_size, locationNeed);
                
                //  allocate new space
                pointer new_start = allocate(new_capacity);  
                pointer new_end_of_storage = new_start + new_capacity;
                
                //  copy and fill
                pointer new_finish = uninitialized_copy(begin(), pos, new_start);
                new_finish = uninitialized_fill_n(new_finish, n, value);
                new_finish = uninitialized_copy(pos, end(), new_finish);
                
                //  free old space
                destroy_and_deallocate();

                //  init new space
                start = new_start;
                finish = new_finish;
                end_of_storage = new_end_of_storage;
            }
        }

        template<class InputIterator>
        void insert_aux(iterator pos, InputIterator first, InputIterator last, __false_type)
        {
            size_type locationLeft  = end_of_storage - finish;
            size_type locationNeed = last - first;

            if (locationNeed <= locationLeft)
            {
                iterator temp = pos;
                while (temp != end())
                {
                    *(temp + locationNeed) = *(temp);
                    temp++;
                }
                uninitialized_copy(first, last, pos);
                finish = finish + locationNeed;
            }
            else
            {
                size_type old_size = size();
                size_type new_capacity = old_size + std::max(old_size, locationNeed);
                
                //  allocate new space
                pointer new_start = allocate(new_capacity);
                pointer new_end_of_storage = new_start + new_capacity;
                
                //  copy
                pointer new_finish = uninitialized_copy(begin(), pos, new_start);
                new_finish = uninitialized_copy(first, last, new_finish);
                new_finish = uninitialized_copy(pos, end(), new_finish);

                //  free old space
                destroy_and_deallocate();
                
                //  init new space;
                start = new_start;
                finish = new_finish;
                end_of_storage = new_end_of_storage;
            }
              
        }
    //  insert
    public:
        void insert(iterator pos, size_type n, const T &value)
        {
            insert_aux(pos, n, value, __true_type());
        }

        template<class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last)
        {
            typedef typename _is_integer<InputIterator>::is_integer is_integer;
            insert_aux(pos, first, last, is_integer());
        }

        iterator insert(iterator pos, const T &value)
        {
            insert(pos, 1, value);  //  call insert(pos, n, value)

            return pos;
        }
    //////////////////////////////////////////////////////////////////////
    //  erase
    public:
        iterator erase(iterator first, iterator last)
        {   
            //  copy and destroy
            iterator i = uninitialized_copy(last, end(), first);   
            destroy(i, end());
    
            finish = finish - (last - first);
            
            return first;
        }

        iterator erase(iterator pos)
        {
            return erase(pos, pos + 1);    //  call erase(first, last)
        }
    //////////////////////////////////////////////////////////////////////
    //  push_back, pop_back
    public:
        void push_back(const value_type &x)
        {
            insert(end(), x);
        }
        
        void pop_back()
        {
            erase(end() - 1);
        }
    };

}

#endif

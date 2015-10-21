/********************************************************************
	Time:	  2015/10/21
	Filename: iterator_test
	Author:	  dinglj
	
	Purpose:  ����iterator_traits
*********************************************************************/

#ifndef _ITERATOR_TEST_H_
#define _ITERATOR_TEST_H_

#include <iostream>
#include "../stlite_iterator.h"

using namespace STLite;

namespace iterator_unit
{

//  �Զ���ĵ��������̳���STLite::iterator
template<class T>
class MyIterator : public iterator<random_access_iterator_tag, T>
{
private:
    T *m_ptr;

public:
    MyIterator(T *p = 0) : m_ptr(p){}
    T& operator*()const {return *m_ptr;}

    ~MyIterator() {delete(m_ptr);}

};

template<class Iterator>
typename iterator_traits<Iterator>::value_type
func(Iterator iter)
{
    return *iter;
}

void test()
{
    std::cout << "iterator_test" << std::endl;

    //  ��ָͨ��
    int *p = new int(20);   
    std::cout << func(p) << std::endl;      //  20

    //  �Զ��������
    MyIterator<int> iter(new int(30));      //  30
    std::cout << func(iter) << std::endl;
   
    std::cout << typeid(iter).name() << std::endl;  //  class iterator_unit::MyIterator<int>
    std::cout << typeid(iterator_category(iter)).name() << std::endl;   //  struct STLite::random_access_iterator_tag
    std::cout << typeid(value_type(iter)).name() << std::endl;  //  int
}
}
#endif
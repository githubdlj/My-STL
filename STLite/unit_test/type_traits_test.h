/********************************************************************
	Time:	  2015/10/21
	Filename: type_traits_test
	Author:	  dinglj
	
	Purpose:  ����type_traits
*********************************************************************/
#ifndef _TYPE_TRAITS_TEST_H_
#define _TYPE_TRAITS_TEST_H_

#include <iostream>
#include "../type_traits.h"

using namespace std;
using namespace STLite;

//  ���������ռ�ԭ���ǿ����ڲ�ͬ�Ĳ����ļ���ӵ����ͬ�ĺ���������test��������ø��ļ��е�test��
//  �����type_traits_test::test()
namespace type_traites_test
{

//  ���غ���
void print_aux(__true_type)
{
    std::cout << "true" << endl;
}

void print_aux(__false_type)
{
    std::cout << "false" << endl;
}

template<class T>
void print(T)
{
    typedef typename __type_traits<T>::is_POD_type is_POD_type;
    print_aux(is_POD_type());
}

void test()
{
    int a = 0;
    print(a);

    bool b = true;
    print(b);

    class A{};
    A c;
    print(c);

    class B{};
    B d;
    print(d);
}

}
#endif
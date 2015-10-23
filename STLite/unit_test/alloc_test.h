/********************************************************************
	Time:	  2015/10/22
	Filename: alloc_test
	Author:	  dinglj
	
	Purpose:  ����alloc�ڴ�������
*********************************************************************/

#include "../stlite_alloc.h"
#include <vector>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

namespace alloc_unit
{
const int OBJECT_NUM = 10;

void testCase1()
{
    cout << "testCase1" << endl;

    allocator<int> alloc;

    //  alloc memory
    int *ptr = alloc.allocate(OBJECT_NUM);

    //  construct;
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        alloc.construct(ptr + i, i);    
    }

    //  print
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << ptr[i];
    }

    //  destroy, �����汾���汾һЧ�ʸ�
    alloc.destroy(ptr, ptr + OBJECT_NUM); 
//     for (int i = 0; i < OBJECT_NUM; i++)
//     {
//         alloc.destroy(ptr + i);     
//                                    
//     }
    //  deallocate
    alloc.deallocate(ptr, OBJECT_NUM);

    cout << endl;
}

void testCase2()
{
    cout << "testCase2" << endl;

    int arr[OBJECT_NUM];
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        arr[i] = i;
    }
   
    //  �����������ڴ����construct����
    //  ��һ�η���8Byte���ڶ��η���sizeof(int) * OBJECT_NUM byte
    //  ͨ�����ԣ����ֵ�һ�η����8byte�ڴ淵������Ϊstd::_Container_proxy *
    std::vector< int, STLite::allocator<int> > v(arr, arr + OBJECT_NUM);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << v[i];
    }
    cout << endl;
}

void test()
{
     testCase1();
     testCase2();
}
}
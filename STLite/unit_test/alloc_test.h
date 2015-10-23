/********************************************************************
	Time:	  2015/10/22
	Filename: alloc_test
	Author:	  dinglj
	
	Purpose:  ����alloc�ڴ�������
*********************************************************************/

#include "../stlite_alloc.h"
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using namespace STLite;

namespace alloc_unit
{
const int OBJECT_NUM = 10;

void test_alloc_on_container()
{
    int arr[OBJECT_NUM];
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        arr[i] = i;
    }
    NULL
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

void test_alloc_on_basedata()
{
    STLite::allocator<int> alloc;
    
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

    //  destroy
    alloc.destroy(ptr);

    //  deallocate
    alloc.deallocate(ptr, OBJECT_NUM);


}
void test()
{
       cout << "alloc test" << endl;
       //   test_alloc_on_basedata();
       cout << endl;
       test_alloc_on_container();
}
}
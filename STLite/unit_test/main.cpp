/********************************************************************
	Time:	  2015/10/21
	Filename: main
	Author:	  dinglj
	
	Purpose:  �����Ժ��������ڲ��Ը������Ե�Ԫ
*********************************************************************/

#include "type_traits_test.h"
#include "iterator_test.h"
#include "construct_test.h"
#include "alloc_test.h"
#include "other_test.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

int main()
{
    cout << "Hello STLite" << endl;
    
    //  �ֱ���ò�ͬ�ļ���test()
    //  type_traites_unit::test();  
    //  iterator_unit::test();
    //  construct_unit::test();
        alloc_unit::test();
    other_unit::test();
 
    system("pause");
    return true;
}


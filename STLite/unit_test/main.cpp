/********************************************************************
	Time:	  2015/10/21
	Filename: main
	Author:	  dinglj
	
	Purpose:  �����Ժ��������ڲ��Ը������Ե�Ԫ
*********************************************************************/

#include "type_traits_test.h"
#include "other_test.h"

#include <iostream>

using namespace STLite;
using namespace std;

int main()
{
    std::cout << "Hello STLite" << endl;
    
    //  �ֱ���ò�ͬ�ļ���test()
    type_traites_test::test();  
    other_test::test();

    system("pause");
    return true;
}


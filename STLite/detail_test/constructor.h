
/********************************************************************
	Time:	  2015/10/30
	Filename: constructor
	Author:	  dinglj
	
	Purpose:  ���Թ��캯���ĵ���
*********************************************************************/
#ifndef _CONSTRUCTOR_H_
#define _CONSTRUCTOR_H_

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

namespace constructor_detail
{
    struct structType
    {
        structType() 
        {
            cout << "constructor" << endl;
        }
        structType(const structType &)
        {
            cout << "copy" << endl;
        }
        structType operator =(const structType &)
        {
            cout << "assignment" << endl;
        }
        ~structType()
        {
            cout << "deconstructor" << endl;
        }
    };

    void fun1(structType)   //  ���ݲ����������һ��copy
    {
        
    }

    void fun2(const structType &)   //  ���ݲ���������copy
    {
        
    }

    //////////////////////////////////////////////////////////////////////
    structType fun3()   //  ����ֵ�����copy
    {
        structType s;
        return s;
    }

//     structType & fun4()
//     {
//         return *this;
//     }
    //////////////////////////////////////////////////////////////////////
    void test()
    {
//         structType s;
//         fun2(s);
        fun3();
    }
};

#endif


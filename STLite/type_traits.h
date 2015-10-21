/********************************************************************
	Time:	  2015/10/21
	Filename: type_traits
	Author:	  dinglj
	
	Purpose:  ʵ��type_traits,����ʶ�� type_traits������ȡ�����͵����ʣ��ж�
              �����Ƿ����trivial���ʵ�default_costructor��copy_constructor��
              assignment_operator��deconstructor�Լ��Ƿ���POD���������ʵ������Ӧ�ĺ�����
*********************************************************************/

#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_

namespace STLite
{
    struct __true_type{};
    struct __false_type{};

    template<class T>
    struct __type_traits
    {
        typedef __true_type this_dummy_must_be_first;
         /* Do not remove this member. It informs a compiler which
            automatically specializes __type_traits that this
            __type_traits template is special. It just makes sure that
            things work if an implementation is using a template
            called __type_traits for something unrelated. */
        
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type has_trivial_deconstructor;
        typedef __false_type is_POD_type;
    };
    //////////////////////////////////////////////////////////////////////

    //  ƫ�ػ�����������
    //  bool, char, signed char, unsigned char, short, unsigned short, int, unsigned int,
    //  long, unsigned long, float, double, pointer
    //  ������������ w_char, long long�Ȳ�����������ʱû��ƫ�ػ�����
    
    //  bool
    template<>
    struct __type_traits<bool>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  char
   
    template<>
    struct __type_traits<char>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<signed char>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned char>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };
    
    //////////////////////////////////////////////////////////////////////
    //  short
    template<>
    struct __type_traits<short>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned short>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };
    //////////////////////////////////////////////////////////////////////
    //  int
    template<>
    struct __type_traits<int>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned int>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  long
    template<>
    struct __type_traits<long>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned long>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  float
    template<>
    struct __type_traits<float>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  double
    template<>
    struct __type_traits<double>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  pointer
    template<class T>
    struct __type_traits<T*>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };
}

#endif
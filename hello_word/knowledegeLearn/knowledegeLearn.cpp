// knowledegeLearn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <functional>
using namespace std;
struct  RValue_ref
{
    RValue_ref(){
        std::cout << "RValue_ref default construct" << std::endl;
    }

    ~RValue_ref(){
        cout << "RValue_ref destruct" << endl;
    }

    RValue_ref(const RValue_ref& r){

        cout << "RValue_ref copy construct" << endl;
    }

    RValue_ref(RValue_ref&& r){
        cout << "RValue_ref rvalue refernce constrcut" << endl;

    }
private:
};
void knowledge1()
{
    char a;
    char b[10];
    char c[] = "www.baidu.com";
    char *d = new char[100];
    d[0] = '\0';
    memset(d, 'a', 99);

    int e;
    long f;
    unsigned long g;
    short h;
    unsigned short i;
    std::cout << sizeof(a) << std::endl;
    std::cout << sizeof(b) << std::endl;
    std::cout << sizeof(c) << std::endl;
    std::cout << sizeof(d) << std::endl;
    std::cout << sizeof(e) << std::endl;
    std::cout << sizeof(f) << std::endl;
    std::cout << sizeof(g) << std::endl;
    std::cout << sizeof(h) << std::endl;
    std::cout << sizeof(i) << std::endl;
}

int fun1(int a, int b)
{
    return a + b;
}

void knowledge2()
{

     auto lambda = [](int a, int b)->int{return a + b; };

    std::function<int(int, int)> test = fun1;

    int a = test(1, 2);
    std::cout << a << std::endl;
    std::function<int(int, int)> test2 = lambda;
    std::cout << test2(4,4) << std::endl;

}

void knowledge3()
{
    std::vector<int> a = { 1, 2, 3, 4, 5, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4 };

    std::cout << a.size() << std::endl;

    std::cout << "a size = " << &a << std::endl;

    std::vector<int> b = std::move(a);
    std::cout << "a size = " << a.size() << std::endl;
    std::cout << "a size = " << &a << std::endl;
    std::cout << "b size = " << b.size() << std::endl;
    std::cout << "b size = " << &b << std::endl;

}


void test1(RValue_ref r)
{
    cout << "in test1" << endl;
    RValue_ref a(r);
    cout << "out test1" << endl;
}
void test2(RValue_ref& r)
{
    cout << "in test2" << endl;
    RValue_ref a(r);
    cout << "out test2" << endl;

}

void test3(const RValue_ref& r)
{
    cout << "in test3" << endl;
    RValue_ref a(r);
    cout << "out test3" << endl;

}

void test4(RValue_ref&& r)
{
    cout << "in test4" << endl;

    RValue_ref a(r);
    cout << "out test4" << endl;


}

void knowledge4()
{
    cout << "-------------------------------------------------------------" << endl;
    RValue_ref r;
    cout << "-------------------------1-------------------------"<< endl;
    test1(r);
    cout << "-------------------------2-------------------------"<< endl;
    test2(r);
    cout << "-------------------------3-------------------------"<< endl;
    test3(r);
    cout << "-------------------------4-------------------------"<< endl;
    test4(std::move(r));
    cout << "-----------------end------------------" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    //knowledge1();
    //knowledge2();
    //knowledge3();
    knowledge4();
    system("pause");
	return 0;
}


// thread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <boost/thread/thread.hpp>

void thread_proc1(std::string param)
{
    int n = 0;
    while (n < 100)
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        std::cout << param << "   " <<n<< std::endl;
        n++;
    }
}

void start_thread1()
{
    boost::thread  t(boost::bind(thread_proc1,"proc 1"));
    boost::thread t2(boost::bind(thread_proc1, "prco 2"));
    t.join();
    t2.join();
    std::cout << "exit start_thread1" << std::endl;
    return;
}

int _tmain(int argc, _TCHAR* argv[])
{
    start_thread1();
    std::cout << "main exit" << std::endl;
	return 0;
}


// thread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <boost/thread/thread.hpp>
#include "SSThreadPool.h"
#include <chrono>

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

CSSThreadPool pool(4);
void custom( std::string str)
{
    while (true)
    {
        std::future<std::string> res;
        res = pool.enqueue(([=](int a){
            std::cout << str<<"   "<<a << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return str ;
        }),1);

        std::cout << str << "   begin" << std::endl;
        std::cout << res.get() << "    mid" << std::endl;
        std::cout << str << "   end" << std::endl;
    }


}



int _tmain(int argc, _TCHAR* argv[])
{
    boost::thread t(boost::bind(custom, std::string("t")));
    boost::thread t2(boost::bind(custom,std::string("t2")));
    boost::thread t3(boost::bind(custom, std::string("t3")));
    boost::thread t4(boost::bind(custom, std::string("t4")));

    t.join();
    t2.join();
    t3.join();
    t4.join();

    pool.stop();

    system("pause");
	return 0;
}


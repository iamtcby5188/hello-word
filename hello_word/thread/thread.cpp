// thread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <boost/thread/thread.hpp>
#include "SSThreadPool.h"
#include <chrono>
using namespace std;

void thread_proc1(std::string param)
{
    int n = 0;
    while (n < 100)
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        std::cout << param << "   " << n << std::endl;
        n++;
    }
}

void start_thread1()
{
    boost::thread  t(boost::bind(thread_proc1, "proc 1"));
    boost::thread t2(boost::bind(thread_proc1, "prco 2"));
    t.join();
    std::cout << "aaaaaaaaaaaaa" << std::endl;
    t2.join();
    std::cout << "exit start_thread1" << std::endl;
    return;
}

CSSThreadPool pool(4);
void custom(std::string str)
{
    while (true)
    {
        std::future<std::string> res;
        res = pool.enqueue(([=](int a){
            std::cout << str << "   " << a << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return str;
        }), 1);

        std::cout << str << "   begin" << std::endl;
        std::cout << res.get() << "    mid" << std::endl;
        std::cout << str << "   end" << std::endl;
    }


}

void threadpooltest()
{
    boost::thread t(boost::bind(custom, std::string("t")));
    boost::thread t2(boost::bind(custom, std::string("t2")));
    boost::thread t3(boost::bind(custom, std::string("t3")));
    boost::thread t4(boost::bind(custom, std::string("t4")));

    t.join();
    t2.join();
    t3.join();
    t4.join();

    pool.stop();

    system("pause");
}

void thread_proc(std::promise<int>& pr)
{
    cout << "in proc " << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //pr.set_value_at_thread_exit(9);
    pr.set_value(9);
    cout << "end proc " << endl;

}

void promise_test()
{
    std::promise<int> pr;
    std::thread t(std::bind(thread_proc, std::ref(pr)));
    std::future<int> f = pr.get_future();
    cout << "return is " << f.get() << endl;
    t.join();
    cout << "test end" << endl;
}

void test()
{

    cout<<__FILE__<<"     " <<__FUNCTION__<<"      "<< __LINE__ << endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
    cout << __FUNCTION__ <<"    "<< __LINE__ << endl;
    test();
    //start_thread1();
    //threadpooltest();

    //promise_test();

    system("pause");
    return 0;
}

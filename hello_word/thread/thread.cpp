// thread.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <iostream>
//#include <boost/thread/thread.hpp>
//#include "SSThreadPool.h"
#include <chrono>
#include <memory>
#include <thread>
//#include <boost/bind.hpp>
//#include <boost/function/function0.hpp>
//#include <io_service.hpp>

#include <time.h>
#include <ctime>
#include <chrono>
#include <stdio.h>


using namespace std;
//using namespace boost;
//void thread_proc1(std::string param)
//{
//    int n = 0;
//    while (n < 100)
//    {
//        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
//        std::cout << param << "   " << n << std::endl;
//        n++;
//    }
//}
//
//void start_thread1()
//{
//    boost::thread  t(boost::bind(thread_proc1, "proc 1"));
//    boost::thread t2(boost::bind(thread_proc1, "prco 2"));
//    t.join();
//    std::cout << "aaaaaaaaaaaaa" << std::endl;
//    t2.join();
//    std::cout << "exit start_thread1" << std::endl;
//    return;
//}
//
//CSSThreadPool pool(4);
//void custom(std::string str)
//{
//    while (true)
//    {
//        std::future<std::string> res;
//        res = pool.enqueue(([=](int a){
//            std::cout << str << "   " << a << std::endl;
//            std::this_thread::sleep_for(std::chrono::seconds(1));
//            return str;
//        }), 1);
//
//        std::cout << str << "   begin" << std::endl;
//        std::cout << res.get() << "    mid" << std::endl;
//        std::cout << str << "   end" << std::endl;
//    }
//
//
//}
//
//void threadpooltest()
//{
//    boost::thread t(boost::bind(custom, std::string("t")));
//    boost::thread t2(boost::bind(custom, std::string("t2")));
//    boost::thread t3(boost::bind(custom, std::string("t3")));
//    boost::thread t4(boost::bind(custom, std::string("t4")));
//
//    t.join();
//    t2.join();
//    t3.join();
//    t4.join();
//
//    pool.stop();
//
//    system("pause");
//}
//
//void thread_proc(std::promise<int>& pr)
//{
//    cout << "in proc " << endl;
//    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//    //pr.set_value_at_thread_exit(9);
//    pr.set_value(9);
//    cout << "end proc " << endl;
//
//}
//
//void promise_test()
//{
//    std::promise<int> pr;
//    std::thread t(std::bind(thread_proc, std::ref(pr)));
//    std::future<int> f = pr.get_future();
//    cout << "return is " << f.get() << endl;
//    t.join();
//    cout << "test end" << endl;
//}
//
//std::mutex mt;
//std::condition_variable std_con;
//void thread_test_proc()
//{
//    cout << "))))))))))))))))))))))))))" << endl;
//    while (std_con.wait_for(std::unique_lock<std::mutex>(mt),std::chrono::milliseconds(100)) == std::cv_status::timeout)
//    {
//        cout << "a" << endl;
//    }
//
//    cout << "-----------------------------------" << endl;
//}
//void start()
//{
//    std::thread t(std::bind(thread_test_proc));
//}
//
//void stop()
//{
//    std_con.notify_one();
//}
//
//
//std::unique_ptr<std::thread> t;
//void test()
//{
//     t.reset(new std::thread(std::bind([]{
//   
//        
//            cout << "test ----- start ----- "<<endl;
//       
//    })));
//
//
//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//    t->join();
//    cout << "---------------end" << endl;
//    if (t && t->joinable())
//    {
//        t->join();
//    }
//}
//
//
//void AsioRun(const boost::system::error_code& e ,boost::asio::basic_deadline_timer*ti)
//{
//    std::cout << "--------------------------------------" << std::endl;
//    boost::this_thread::sleep(boost::posix_time::second(2));
//    ti->expires_at(ti->expires_at() + boost::posix_time::second(1));
//    ti->async_wait(&AsioRun, boost::asio::placeholders::error, ti);
//    std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
//}
//
//void AsioTest()
//{
//    boost::asio::io_service io;
//    boost::asio::basic_deadline_timer t0(io, boost::posix_time::second(1));
//    t0.async_wait(boost::bind(&AsioRun,boost::asio::placeholders::error,&t0));
//    io.run();
//}

std::string GetTime_x_seconds_latter(const std::string& strTime, int sec)
{
    using std::chrono::system_clock;

    int year(0);
    int month(0);
    int day(0);
    int hour(0);
    int minute(0);
    int second(0);
    sscanf(strTime.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

    std::tm tm_;
    tm_.tm_year = year - 1900;
    tm_.tm_mon = month - 1;
    tm_.tm_mday = day;
    tm_.tm_hour = hour;
    tm_.tm_min = minute;
    tm_.tm_sec = second;

    char timeChars[50] = { 0 };
    std::time_t x_sec_latter = system_clock::to_time_t(std::chrono::system_clock::from_time_t(mktime(&tm_)) + std::chrono::seconds(sec));
    //system_clock::to_time_t(std::chrono::system_clock::from_time_t(mktime(&tm_)) - std::chrono::seconds(sec));
    strftime(timeChars, 50, "%Y-%m-%d %H:%M:%S", std::localtime(&x_sec_latter));
    return std::string(timeChars);
}

int _tmain(int argc, _TCHAR* argv[])
{
    //cout << __FUNCTION__ <<"    "<< __LINE__ << endl;
    //test();
    //start_thread1();
    //threadpooltest();

    //promise_test();
    std::string aa;

 /*   for (int n = 0; n < 7000; ++n)
    {
        aa.append("60bda83dd8ff425a80660a966066c45e");
        cout << n << endl;
    }*/
    cout << GetTime_x_seconds_latter("2018-01-18 00:00:59",1).c_str()<<endl;
    cout << GetTime_x_seconds_latter("2018-01-18 23:59:59",1).c_str()<<endl;
    cout << GetTime_x_seconds_latter("2018-01-31 23:59:59",1).c_str()<<endl;
    cout << GetTime_x_seconds_latter("2018-12-31 23:59:59",1).c_str()<<endl;
    cout << GetTime_x_seconds_latter("2018-02-28 23:59:59",1).c_str()<<endl;
    cout << GetTime_x_seconds_latter("2017-02-29 23:59:59",1).c_str()<<endl;
    system("pause");
    return 0;
}

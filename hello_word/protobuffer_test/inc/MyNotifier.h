#pragma once

//-------------------------------------------------------------------------------------
//--Copyright	:	Sumscope
//--FileName	:	MyNotifier.h 
//--Author		:	cheng.xu@sumscope.com
//--Date		:	2015.7.10
//--Desc		:	同步等待工具
//--History		:	Created by cheng.xu, 2015.07.10
//-------------------------------------------------------------------------------------

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class MyNotifier
{
public:
    MyNotifier(){}
    ~MyNotifier(){}

    bool Wait(int timeout)
    {
        boost::mutex::scoped_lock lock(m_mutex);

        if (timeout < 0)
        {
            m_condition.wait(lock);
            return true;
        }
        else
        {
            return m_condition.timed_wait(lock , boost::get_system_time() + boost::posix_time::millisec(timeout)) ;
        }
    }

    void Notify()
    {
        boost::mutex::scoped_lock lock(m_mutex);
        m_condition.notify_one();
    }

private:
    boost::mutex m_mutex;
    boost::condition m_condition;
};
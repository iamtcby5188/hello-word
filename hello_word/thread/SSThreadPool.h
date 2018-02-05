#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
class CSSThreadPool
{
public:
    CSSThreadPool(size_t nCount = 4);
    virtual ~CSSThreadPool();

    template<class F,class ...Args>
    auto enqueue(F&& f, Args&& ...args)->std::future<typename std::result_of<F(Args...)>::type>;

    void stop();
private:
    std::vector<std::thread> m_vThreads;
    std::queue<std::function<void()>> m_vTasks;

    std::mutex m_mutex;
    std::condition_variable m_cond;
    bool m_bStop;

};

inline CSSThreadPool::CSSThreadPool(size_t nCount)
    :m_bStop(false)
{
    //for (size_t n = 0; n < nCount; n++)
    //{
    //    m_vThreads.emplace_back(
    //        [this]{
    //            while (true)
    //            {
    //                std::function<void()> task;
    //                {
    //                    std::unique_lock<std::mutex> lock(this->m_mutex);
    //                    this->m_cond.wait(lock, [this]{return this->m_bStop || !this->m_vTasks.empty(); });
    //                    if (this->m_bStop && this->m_vTasks.empty()) return;
    //                    task = std::move(this->m_vTasks.front());
    //                    this->m_vTasks.pop();
    //                }

    //                task();                    
    //            }
    //        }
    //    );
    //}
}

CSSThreadPool::~CSSThreadPool()
{
    //{
    //    std::unique_lock<std::mutex> lock(m_mutex);
    //    
    //    m_bStop = true;
    //}
    //m_cond.notify_all();
    //for (std::thread &thread : m_vThreads)
    //{
    //    thread.join();
    //}
}

void CSSThreadPool::stop()
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_bStop = true;
    }
    m_cond.notify_all();
    for (std::thread &thread : m_vThreads)
    {
        thread.join();
    }

    m_vThreads.clear();
}

template<class F,class ...Args>
auto CSSThreadPool::enqueue( F&& f,  Args&& ...args)->std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f),std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_vTasks.emplace([task](){(*task)(); });
    }

    m_cond.notify_one();
    return res;
}
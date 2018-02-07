// read_write_buffer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <thread>
#include <iostream>
#include "circle_buffer.h"
#include <mutex>

std::string str[20] = {
    "test  1",
    "test  2",
    "test  3",
    "test  4",
    "test  5",
    "test  6",
    "test  7",
    "test  8",
    "test  9",
    "test  10",
    "test  11",
    "test  12",
    "test  13",
    "test  14",
    "test  15",
    "test  16",
    "test  17",
    "test  18",
    "test  19",
    "test  20"
};

std::mutex mt;
void read_thread_proc(circle_buffer buff)
{
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(mt);
            int size(0);
            void* pBuf = buff.read_buffer(size);
            if (pBuf != nullptr)
            {
                char* ch = new char[size + 1];
                memset(ch, 0, size + 1);
                memcpy(ch, pBuf, size);                
                std::cout << "read buff: " << ch << std::endl;
                char a[100] = { 0 };
                sprintf_s(a, "bianyu read thread : %s\r\n ", ch);
                printf(a);

            }
            else
            {
                printf("bianyu read thread : buf is null\r\n");
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 1000));
    }
}

void write_thread_proc(circle_buffer buff)
{
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(mt);
            int index = std::rand() % 20;
            std::string s_w = str[index];
            bool bRes = buff.write_buffer(s_w.length(), (long long)s_w.c_str());
            char a[100] = { 0 };
            sprintf_s(a, "bianyu write thread : %s res : %d\r\n",s_w.c_str(),bRes);
            printf(a);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 1000));
    }
}
int _tmain(int argc, _TCHAR* argv[])
{
    char* ptmp = new char[1024 * 1024];
    memset(ptmp, 0, 1024 * 1024);
    circle_buffer buffer(1024*1024,(long long)ptmp);

    std::thread read_thread(std::bind(read_thread_proc,buffer));
    std::thread write_thread(std::bind(write_thread_proc,buffer));
    read_thread.join();
    write_thread.join();
    return 0;
}


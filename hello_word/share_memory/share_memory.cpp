// share_memory.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#ifdef _WIN32
#include "sql_share_memory.h"
#else
#include "sql_share_memory_no_boost.h"
#endif
using namespace std;
struct test 
{
    void* p1;
    void* p2;
    
};

struct test2
{
    long long l1;
    long long l2;
};
int _tmain(int argc, _TCHAR* argv[])
{
    int a = sizeof(test);
    int b = sizeof(test2);
    int c = sizeof(long long);
    int d = sizeof(unsigned long);
    int e = sizeof(void*);
    char* char_a = "123567";
    char  char_b[20] = "1234";
    int f = strlen(char_a);
    int g = strlen(char_b);
    int h = sizeof(char_a);
    int i = sizeof(char_b);
#ifdef _WIN32
    sql_task task;
#else
    sql_task_no_boost task;
#endif
    task.sql.push_back("a");
    task.sql.push_back("b");

#ifdef _WIN32
    sql_share_memory::getInstance()->add_sql(task);
#else
    sql_share_memory_no_boost::getInstance()->add_sql(task);
#endif
    task.sql.clear();
    task.sql.push_back("c");
    task.sql.push_back("d");

#ifdef _WIN32
    sql_share_memory::getInstance()->add_sql(task);
#else
    sql_share_memory_no_boost::getInstance()->add_sql(task);
#endif

    task.sql.clear();

#ifdef _WIN32
    while (sql_share_memory::getInstance()->get_sql(task))
#else
    while (sql_share_memory_no_boost::getInstance()->get_sql(task))
#endif
    {
        for (auto iter = task.sql.begin(); iter != task.sql.end(); ++iter)
        {
            std::cout << *iter << std::endl;
        }

        std::cout << "-----------------------------" << std::endl;
    }
    system("pause");
	return 0;
}


#include "stdafx.h"
#include "sql_share_memory_no_boost.h"
#ifdef _WIN32

#else
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#define SHARED_MEMORY_SIZE (1024*1024)
sql_share_memory_no_boost* sql_share_memory_no_boost::instance = NULL;


sql_share_memory_no_boost* sql_share_memory_no_boost::getInstance()
{
    if (instance == NULL)
    {
        instance = new sql_share_memory_no_boost();
    }

    return instance;
}

sql_share_memory_no_boost::sql_share_memory_no_boost()
    :m_shmid(-1)
{

    key_t key = ftok("../", 2015);

    m_shmid = shmget(key, SHARED_MEMORY_SIZE,(IPC_CREAT | 0666));

}


sql_share_memory_no_boost::~sql_share_memory_no_boost()
{
     
}

void sql_share_memory_no_boost::add_sql(const sql_task_no_boost& task)
{
    if (this == NULL || m_shmid < 0)
    {
        return;
    }
    sql_task_no_boost_list lst_task;
    
    char* shmadd = (char*)shmat(m_shmid, NULL, 0);
    if(strlen(shmadd) > 0){
    std::istringstream is(shmadd);
    boost::archive::text_iarchive ia(is);
    ia >> lst_task;
    }
    lst_task.sql_list.push_back(task);

    std::ostringstream os;
    boost::archive::text_oarchive oa(os);
    oa << lst_task;

    bzero(shmadd,SHARED_MEMORY_SIZE);
    strcpy(shmadd, os.str().c_str());
}

bool sql_share_memory_no_boost::get_sql(sql_task_no_boost& task)
{   
    if (this == NULL || m_shmid < 0)
    {
        return false;
    }
    sql_task_list lst_task;
    char* shmadd = (char*)shmat(m_shmid, NULL, 0);
    if (strlen(shmadd) > 0)
    {
        std::istringstream is(shmadd);
        boost::archive::text_iarchive ia(is);

        ia >> lst_task;
    }
    if (lst_task.sql_list.empty())
    {
        return false;
    }

    bzero(shmadd, SHARED_MEMORY_SIZE);
    std::list<sql_task>::iterator iter = lst_task.sql_list.begin();
    task = *iter;
    lst_task.sql_list.erase(iter);
    if (!lst_task.sql_list.empty())
    {
        std::ostringstream os;
        boost::archive::text_oarchive oa(os);
        oa << lst_task;
        strcpy(shmadd, os.str().c_str());
    }
    return true;
}
#endif
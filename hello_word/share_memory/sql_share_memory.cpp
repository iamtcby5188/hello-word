#include "stdafx.h"
#include "sql_share_memory.h"
#include <boost\interprocess\creation_tags.hpp>
#include <boost\interprocess\mapped_region.hpp>

using namespace boost::interprocess;
sql_share_memory* sql_share_memory::instance = nullptr;


sql_share_memory* sql_share_memory::getInstance()
{
    if (instance == nullptr)
    {
        instance = new sql_share_memory();
    }

    return instance;
}

sql_share_memory::sql_share_memory()
    :shm_obj(open_or_create,SHARE_MEM_NAME,read_write)
{
    mapped_region region(shm_obj, read_write);
    int n = region.get_size();
    if (n <= 0)
    {
        shm_obj.truncate(1024 * 1024);
        std::memset(region.get_address(), 0, region.get_size());
    }
}


sql_share_memory::~sql_share_memory()
{
     
}

void sql_share_memory::add_sql(const sql_task& task)
{
    if (this == nullptr)
    {
        return;
    }
    sql_task_list lst_task;
    mapped_region region(shm_obj, read_write);
    char* mem = static_cast<char*>(region.get_address());
    std::istringstream is(mem);
    boost::archive::text_iarchive ia(is);
    ia >> lst_task;
    lst_task.sql_list.push_back(task);

    std::ostringstream os;
    boost::archive::text_oarchive oa(os);
    oa << lst_task;

    std::memset(region.get_address(), 0, region.get_size());
    std::memcpy(region.get_address(), os.str().c_str(), strlen(os.str().c_str()));
}

bool sql_share_memory::get_sql(sql_task& task)
{   
    if (this == nullptr)
    {
        return false;
    }
    mapped_region region(shm_obj, read_write);
    std::istringstream is(static_cast<char*>(region.get_address()));
    boost::archive::text_iarchive ia(is);
    sql_task_list lst_task;
    ia >> lst_task;
    if (lst_task.sql_list.empty())
    {
        return false;
    }

    
    auto iter = lst_task.sql_list.begin();
    task = *iter;
    lst_task.sql_list.erase(iter);
    std::ostringstream os;
    boost::archive::text_oarchive oa(os);
    oa << lst_task;

    std::memset(region.get_address(), 0, region.get_size());
    std::memcpy(region.get_address(), os.str().c_str(), strlen(os.str().c_str()));
    return true;
}

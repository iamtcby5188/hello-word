#pragma once
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/interprocess/shared_memory_object.hpp>  
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define  SHARE_MEM_NAME "IDB_SQL_SHARE_MEMORY"
struct sql_task
{
    std::list<std::string> sql;
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & sql;
    }
};

struct sql_task_list
{
    std::list<sql_task> sql_list;
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & sql_list;
    }
};

class sql_share_memory
{
public:
    static sql_share_memory* instance;
    static sql_share_memory* getInstance();

    void add_sql(const sql_task& task);
    bool get_sql(sql_task& task);
    
private:
    sql_share_memory();
    ~sql_share_memory();

private:
    boost::interprocess::shared_memory_object shm_obj;
};


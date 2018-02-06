#ifndef _SQL_SHARE_MEMORY_NO_BOOST_H
#define _SQL_SHARE_MEMORY_NO_BOOST_H

#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define  SHARE_MEM_NAME "IDB_SQL_SHARE_MEMORY"
struct sql_task_no_boost
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

struct sql_task_no_boost_list
{
    std::list<sql_task_no_boost> sql_list;
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & sql_list;
    }
};

#ifdef _WIN32
#else
class sql_share_memory_no_boost
{
public:
    static sql_share_memory_no_boost* instance;
    static sql_share_memory_no_boost* getInstance();

    void add_sql(const sql_task_no_boost& task);
    bool get_sql(sql_task_no_boost& task);
    
private:
    sql_share_memory_no_boost();
    ~sql_share_memory_no_boost();

private:
    int m_shmid;
};
#endif
#endif // _WIN32

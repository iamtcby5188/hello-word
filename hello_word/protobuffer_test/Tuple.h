#pragma once
#include "boost\smart_ptr\shared_ptr.hpp"
#include "google\protobuf\message.h"
#include <list>
#include "proto\proto_test.pb.h"
using namespace ::google::protobuf;

class Tuple
{
public:
    Tuple();
    ~Tuple();

    template<class T>
    void AddProto(T& args);

    template<class T>
    void InitProto();


    int GetInt32(int num);
    double GetDouble(int num);
    std::string GetString(int num);
    bool GetBool(int num);
    std::list<std::string> GetStringList(int num);
    std::list<double> GetDoubleList(int num);
    std::list<int> GetInt32List(int num);

    template<class T>
    list<T> GetListMessage(int num);
   
    void SetInt32(int num, int value);
    void SetDouble(int num, double value);
    void SetBool(int num, bool value);
    void SetString(int num, std::string value);

    void SetInt32List(int num, std::list<int> value);
    void SetDoubleList(int num, std::list<double> value);
    void SetStringList(int num, std::list<std::string> value);

    template<class T>
    T* SetMessage(int num);
private:
    boost::shared_ptr<::google::protobuf::Message> m_msg;

};

template<class T>
void Tuple::AddProto(T& args)
{
    m_msg = boost::shared_ptr<::google::protobuf::Message>(new T(args));
}


template<class T>
void Tuple::InitProto()
{
    m_msg = boost::shared_ptr<::google::protobuf::Message>();
}

template<class T>
list<T> Tuple::GetListMessage(int num)
{
    const FieldDescriptor* f = m_msg->GetDescriptor()->FindFieldByNumber(num);
    std::list<proto_test::course> lst;
    if (f != NULL && f->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE && f->is_repeated())
    {
        int size = m_msg->GetReflection()->FieldSize(*m_msg, f);
        for (int i = 0; i < size; ++i)
        {
            const T m = (const T&)m_msg->GetReflection()->GetRepeatedMessage(*m_msg, f, i);
            lst.push_back(m);
        }
    }

    return lst;
}


template<class T>
T* Tuple::SetMessage(int num)
{
    const FieldDescriptor* f = m_msg->GetDescriptor()->FindFieldByNumber(num);
    if (f != NULL && f->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) 
    {
        return (T*)m_msg->GetReflection()->AddMessage(m_msg.get(), f);
    }
    return NULL;
}

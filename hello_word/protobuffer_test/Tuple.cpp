#include "stdafx.h"
#include "Tuple.h"

#include "proto\proto_test.pb.h"

Tuple::Tuple()
{
}


Tuple::~Tuple()
{
}

int Tuple::GetInt32(int num)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_INT32 && !field->is_repeated())
        return m_msg->GetReflection()->GetInt32(*m_msg, field);

    return 0;
}

std::list<int> Tuple::GetInt32List(int num)
{
    std::list<int> lst;
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);
    if (field && field->type() == google::protobuf::FieldDescriptor::TYPE_INT32 && field->is_repeated())
    {
        int size = m_msg->GetReflection()->FieldSize(*m_msg, field);
        for (int i = 0; i < size; ++i)
        {
            int n = m_msg->GetReflection()->GetRepeatedInt32(*m_msg, field, i);
            lst.push_back(n);
        }
    }

    return lst;
}

double Tuple::GetDouble(int num)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_DOUBLE && !field->is_repeated())
        return m_msg->GetReflection()->GetDouble(*m_msg, field);

    return 0;
}

std::list<double> Tuple::GetDoubleList(int num)
{
    std::list<double> lst;
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);
    if (field && field->type() == google::protobuf::FieldDescriptor::TYPE_DOUBLE && field->is_repeated())
    {
        int size = m_msg->GetReflection()->FieldSize(*m_msg, field);
        for (int i = 0; i < size; ++i)
        {
            double d = m_msg->GetReflection()->GetRepeatedDouble(*m_msg, field, i);
            lst.push_back(d);
        }
    }

    return lst;
}

std::string Tuple::GetString(int num)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_STRING && !field->is_repeated())
        return m_msg->GetReflection()->GetString(*m_msg, field);

    return "";

}

std::list<std::string> Tuple::GetStringList(int num)
{
    std::list<std::string> lst;
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);
    if (field && field->type() == google::protobuf::FieldDescriptor::TYPE_STRING && field->is_repeated())
    {
        int size = m_msg->GetReflection()->FieldSize(*m_msg, field);
        for (int i = 0; i < size; ++i)
        {
            std::string s = m_msg->GetReflection()->GetRepeatedString(*m_msg, field, i);
            lst.push_back(s);
        }
    }

    return lst;
}

bool Tuple::GetBool(int num)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_BOOL&& field->is_repeated())
        return m_msg->GetReflection()->GetBool(*m_msg, field);

    return false;
}

void Tuple::SetInt32(int num, int value)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_INT32&& !field->is_repeated())
        m_msg->GetReflection()->SetInt32(m_msg.get(), field, value);
}

void Tuple::SetDouble(int num, double value)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    FieldDescriptor::Type type = field->type();
    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_DOUBLE&& !field->is_repeated())
        m_msg->GetReflection()->SetDouble(m_msg.get(), field, value);

}

void Tuple::SetBool(int num, bool value)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_BOOL && !field->is_repeated())
        m_msg->GetReflection()->SetBool(m_msg.get(), field, value);

}

void Tuple::SetString(int num, std::string value)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_STRING && !field->is_repeated())
        m_msg->GetReflection()->SetString(m_msg.get(), field, value);
}

void Tuple::SetInt32List(int num, std::list<int> value)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_INT32&& field->is_repeated())
    {
        int i = 0;
        for (auto iter = value.begin(); iter != value.end(); ++iter)
        {
            m_msg->GetReflection()->SetRepeatedInt32(m_msg.get(), field, i, *iter);
            ++i;
        }
    }
}

void Tuple::SetDoubleList(int num, std::list<double> value)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_DOUBLE&& field->is_repeated())
    {
        int i = 0;
        for (auto iter = value.begin(); iter != value.end(); ++iter)
        {
            m_msg->GetReflection()->SetRepeatedDouble(m_msg.get(), field, i, *iter);
            ++i;
        }
    }
}

void Tuple::SetStringList(int num, std::list<std::string> value)
{
    const FieldDescriptor* field = m_msg->GetDescriptor()->FindFieldByNumber(num);

    if (field != NULL && field->type() == google::protobuf::FieldDescriptor::TYPE_STRING && field->is_repeated())
    {
        int i = 0;
        for (auto iter = value.begin(); iter != value.end(); ++iter)
        {
            m_msg->GetReflection()->SetRepeatedString(m_msg.get(), field, i, *iter);
            ++i;
        }
    }

}


#include "stdafx.h"
#include "ProtoParseHelp.h"

bool ProtoParseHelp::GetBool(const Message* msg, int num)
{
    const FieldDescriptor* f = msg->GetDescriptor()->FindFieldByNumber(num);
    FieldDescriptor::Type type = f->type();
    if (type == FieldDescriptor::TYPE_BOOL)
        return msg->GetReflection()->GetBool(*msg, f);

    return false;
}

std::string ProtoParseHelp::GetString(const Message* msg, int num)
{

    const FieldDescriptor* f = msg->GetDescriptor()->FindFieldByNumber(num);
    FieldDescriptor::Type type = f->type();
    if (type == FieldDescriptor::TYPE_STRING)
        return msg->GetReflection()->GetString(*msg, f);

    return "";
}

double ProtoParseHelp::GetDouble(const Message* msg, int num)
{

    const FieldDescriptor* f = msg->GetDescriptor()->FindFieldByNumber(num);
    FieldDescriptor::Type type = f->type();
    if (type == FieldDescriptor::TYPE_DOUBLE)
        return msg->GetReflection()->GetDouble(*msg, f);

    return 0;
}

int ProtoParseHelp::GetInt32(const Message*msg, int num)
{
    const FieldDescriptor* f = msg->GetDescriptor()->FindFieldByNumber(num);
    FieldDescriptor::Type type = f->type();
    if (type == FieldDescriptor::TYPE_INT32)
        return msg->GetReflection()->GetInt32(*msg, f);

    return 0;
}
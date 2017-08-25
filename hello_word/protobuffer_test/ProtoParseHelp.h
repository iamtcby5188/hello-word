#pragma once
#include "google\protobuf\message.h"
using namespace ::google::protobuf;
class ProtoParseHelp{
public:
    static bool GetBool(const Message* msg, int num);
    static string GetString(const Message* msg, int num);
    static double GetDouble(const Message* msg, int num);
    static int    GetInt32(const Message*msg, int num);
};

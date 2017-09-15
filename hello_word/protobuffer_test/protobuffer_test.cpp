// protobuffer_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "proto\proto_test.pb.h"
#include "Tuple.h"
#include "ProtoParseHelp.h"
#pragma comment(lib,"libprotobuf32.lib")
using namespace ::google::protobuf;


int _tmain(int argc, _TCHAR* argv[])
{
    proto_test::student stu;
    const google::protobuf::FieldDescriptor* f = stu.GetDescriptor()->FindFieldByNumber(1);

    stu.set_age(20);
    stu.set_name("张三");


    //proto_test::course *c = stu.add_score();
    //c->set_name("高数");
    //c->set_score(90);

    //c = stu.add_score();
    //c->set_score(89);
    //c->set_name("政治");

    //c = stu.add_score();
    //c->set_score(88);
    //c->set_name("aa");


    Tuple t;
    t.AddProto(stu);
    int a = t.GetInt32(2);
    string ss = t.GetString(1);

    proto_test::course* ccc = t.SetMessage<proto_test::course>(3);
    ccc->set_name("aaa");
    ccc->set_score(343);

    ccc = t.SetMessage<proto_test::course>(3);
    ccc->set_name("bbb");
    ccc->set_score(667); 
    std::cout << ss << "      " << a << std::endl;
    std::list<proto_test::course> lst = t.GetListMessage<proto_test::course>(3);
    auto iter = lst.begin();

    for (; iter != lst.end(); ++iter)
    {
        std::string s = ProtoParseHelp::GetString(&*iter, 1);
        int n = ProtoParseHelp::GetInt32(&*iter, 2);

        std::cout << s << "     " << n << std::endl;
    }
    return 0;
}


// shared_ptr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <memory>
#include <unordered_map>

class implementation
{
public:
    implementation(){ std::cout << "construct implementation\n"; }
    ~implementation() { std::cout << "destroying implementation\n"; }
    void do_something() { std::cout << "did something\n"; }
};

void test()
{
    boost::shared_ptr<implementation> sp1(new implementation());
    std::cout << "The Sample now has " << sp1.use_count() << " references\n";

    boost::shared_ptr<implementation> sp2 = sp1;
    std::cout << "The Sample now has " << sp2.use_count() << " references\n";

    sp1.reset();
    std::cout << "After Reset sp1. The Sample now has " << sp2.use_count() << " references\n";

    sp2.reset();
    std::cout << "After Reset sp2.\n";
}

void test2()
{
    boost::shared_ptr<implementation> sp1(new implementation());

    boost::shared_ptr<std::vector<boost::shared_ptr<implementation>>> spVct = boost::shared_ptr<std::vector<boost::shared_ptr<implementation>>>(new std::vector<boost::shared_ptr<implementation>>);
    spVct->push_back(sp1);
    spVct->push_back(boost::shared_ptr<implementation>(new implementation));
    std::cout << "clear vector \n";
    spVct->clear();
    std::cout << "exit test2\n";
}

void test3()
{
    std::tr1::shared_ptr<implementation> sp1(new implementation());

    std::tr1::shared_ptr<std::vector<std::tr1::shared_ptr<implementation>>>  spVct = std::tr1::shared_ptr<std::vector<std::tr1::shared_ptr<implementation>>>(new std::vector<std::tr1::shared_ptr<implementation>>);
    spVct->push_back(sp1);
    spVct->push_back(std::tr1::shared_ptr<implementation>(new implementation()));
    std::cout << "clear vector \n" ;
    spVct->clear();
    std::cout << "exit test3 \n";
}

int _tmain(int argc, _TCHAR* argv[])
{   
    //test();
    test2();
    //test3();
	return 0;
}


// RegularExpression.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <..\..\boost_1_55_0\boost\regex\v4\regex.hpp>

char testString[15][32] = {
    "www.baidu.com",
    "www.csdn.cn",
    "c:\\aa.txt",
    "c:\\bb.txt",
    "c:\\cc.xls",
    "c:\\dd.xlsx",
    "c:\\ee.doc",
    "c:\\ff.docx",
    "15022938458",
    "321088198808225451",
    "321088198808225452",
    "456799837278349582",
    "1234abcd332122",
    "abcdefg",
    "12345566"
};

int _tmain(int argc, _TCHAR* argv[])
{
    std::cout << "a" << std::endl;
    boost::regex reg;
    system("pause");
	return 0;
}


#pragma once
#pragma warning(disable:4308)
#pragma warning(disable:4996)

//-------------------------------------------------------------------------------------
//--Copyright	:	Sumscope
//--FileName	:	BaseStringFunc.h
//--Author		:	cheng.xu@sumscope.com
//--Date		:	2015.03.20
//--Desc		:	序列化/反序列化工具
//--History		:	Created by cheng.xu, 2015.03.20
//-------------------------------------------------------------------------------------

/*
类或结构体要支持序列化,需按如下例子实现serialize方法
struct DemoItem
{
	std::string sID;
	std::string sContent;
	std::vector<std::string> vctDemo;

	private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & sID;
		ar & sContent;
		ar & vctDemo;
	}
};
支持stl中的容器,支持对象的嵌套
*/

#include <fstream>
#include <sstream>
#include <locale>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/list.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace ss_serialize
{
	template<class T>
	bool SaveData(const T& vValue, const std::string& sFilePath)
	{
		std::ofstream fout(sFilePath.c_str(), std::ios::binary);
		if(!fout.fail())
		{
			try
			{
				fout.imbue(std::locale("chs"));
				boost::archive::text_oarchive oa(fout);
				oa<<vValue;
			}
			catch(boost::archive::archive_exception& arexception)
			{
				arexception;
				return false;
			}

			return true;

		}
		return false;
	}

	template<class T>
	bool LoadData(T& vValue, const std::string& sFilePath)
	{
		std::ifstream fin(sFilePath.c_str(), std::ios::binary);
		if(!fin.fail())
		{
			try
			{
				fin.imbue(std::locale("chs"));
				boost::archive::text_iarchive ia(fin);
				ia >> vValue;
			}
			catch(boost::archive::archive_exception& arexception)
			{
				arexception;
				return false;
			}
			return true;
		}

		return false;
	}

	template<class T>
	bool Serialize(const T& vValue, std::string& sSer)
	{
		try
		{
			std::ostringstream os;  
			boost::archive::binary_oarchive oa(os); 
			oa << vValue;
			sSer = os.str();
		}
		catch(boost::archive::archive_exception& arexception)
		{
			arexception;
			return false;
		}

		return true;
	}

	template<class T>
	bool Deserialize(T& vValue, const std::string& sSer)
	{
		try
		{
			std::istringstream is(sSer);  
			boost::archive::binary_iarchive ia(is);  
			ia >> vValue;
		}
		catch(boost::archive::archive_exception& arexception)
		{
			arexception;
			return false;
		}

		return true;
	}
}
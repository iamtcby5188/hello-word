//-------------------------------------------------------------------------------------
//--Copyright	:	Sumscope
//--FileName	:	SSTool.h
//--Author		:	cheng.xu@sumscope.com
//--Date		:	2015.02.28
//--Desc		:	常用工具
//--History		:	Created by cheng.xu, 2015.02.28
//--				
//-------------------------------------------------------------------------------------


#ifndef __SS_TOOL_H
#define __SS_TOOL_H

#include <map>
#include <list>
#include <vector>
#include <set>

namespace ss_tool
{
	template<typename T>
	void ClearContainer(std::vector<T*>& items)
	{
		for(std::vector<T*>::iterator it = items.begin(); it != items.end(); it++)
		{
			if (NULL != (*it))
			{
				delete *it;
				*it = NULL;
			}
		}
		items.clear();
	}

	template<typename T>
	void ClearContainer(std::list<T*>& items)
	{
		for(std::list<T*>::iterator it = items.begin(); it != items.end(); it++)
		{
			if (NULL != (*it))
			{
				delete *it;
				*it = NULL;
			}
		}
		items.clear();
	}

	template<typename T>
	void ClearContainer(std::set<T*>& items)
	{
		for(std::set<T*>::iterator it = items.begin(); it != items.end(); it++)
		{
			if (NULL != (*it))
			{
				delete *it;
				*it = NULL;
			}
		}
		items.clear();
	}

	template<typename T1,typename T2>
	void ClearContainer(std::map<T1,T2*>& items)
	{
		for(std::map<T1,T2*>::iterator it = items.begin(); it != items.end(); it++)
		{
			if (NULL != it->second)
			{
				delete it->second;
				it->second = NULL;
			}
		}
		items.clear();
	}

	template<class T>
	class SingletonTmpl
	{
	public:
		static T * Instance()
		{
			return &m_Instance;
		}


		~SingletonTmpl(){}

	protected:
		SingletonTmpl(){}

	private:
		static T m_Instance;
	};

	template<class T>
	T SingletonTmpl<T>::m_Instance;
}


#endif /** __SS_TOOL_H */
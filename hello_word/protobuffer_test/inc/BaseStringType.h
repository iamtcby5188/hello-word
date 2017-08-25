//-------------------------------------------------------------------------------------
//--Copyright	:	Sumscope
//--FileName	:	BaseStringType.h
//--Author		:	cheng.xu@sumscope.com
//--Date		:	2015.01.29
//--Desc		:	Multi-Byte/Unicode÷ß≥÷
//--History		:	Created by cheng.xu, 2015.01.23
//--				
//-------------------------------------------------------------------------------------
#pragma once
#include <string>
#include <tchar.h>

#ifndef t_string
#ifdef UNICODE
#define t_string std::wstring
#else
#define t_string std::string
#endif
#endif


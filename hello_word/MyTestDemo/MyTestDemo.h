
// MyTestDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyTestDemoApp: 
// �йش����ʵ�֣������ MyTestDemo.cpp
//

class CMyTestDemoApp : public CWinApp
{
public:
	CMyTestDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyTestDemoApp theApp;
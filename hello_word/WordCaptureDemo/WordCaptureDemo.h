
// WordCaptureDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWordCaptureDemoApp: 
// �йش����ʵ�֣������ WordCaptureDemo.cpp
//

class CWordCaptureDemoApp : public CWinApp
{
public:
	CWordCaptureDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWordCaptureDemoApp theApp;
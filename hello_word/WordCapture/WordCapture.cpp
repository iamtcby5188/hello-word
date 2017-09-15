// WordCapture.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "WordCapture.h"
#include "WordCaptureSingleton.h"

WORD_CAPTURE_API int WC_Test(int a, int b)
{
    return a + b;
}

WORD_CAPTURE_API void WC_Init()
{
    CWordCaptureSingleton::instance();
}

WORD_CAPTURE_API void WC_Uninit()
{
    CWordCaptureSingleton::release();
}

WORD_CAPTURE_API void WC_StartCapture(std::function<void(char*, int)> cbf)
{
    CWordCaptureSingleton::instance()->StartCapture(cbf);
}

WORD_CAPTURE_API void WC_StopCapture()
{
    CWordCaptureSingleton::instance()->StopCapture();
}


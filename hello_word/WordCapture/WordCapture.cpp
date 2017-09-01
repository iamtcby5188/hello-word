// WordCapture.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "WordCapture.h"
#include "WordCaptureSingleton.h"


WORD_CAPTURE_API int WC_Test(int a, int b)
{
    return a + b;
}

WORD_CAPTURE_API void WC_Init(HINSTANCE hIns)
{
    CWordCaptureSingleton::instance().InitClass(hIns);
}

WORD_CAPTURE_API BOOL WINAPI NHBitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop)
{
    BitBlt(hdcDest, nXDest, nYDest, nWidth, nHeight,hdcSrc, nXSrc, nYSrc, dwRop);
    return TRUE;
}


WORD_CAPTURE_API BOOL WINAPI NHTextOutA(HDC hdc, int nXStart, int nYStart, LPCSTR lpString, int cbString)
{
    TextOutA(hdc, nXStart, nYStart, lpString, cbString);
    return TRUE;
}


WORD_CAPTURE_API BOOL WINAPI NHTextOutW(HDC hdc, int nXStart, int nYStart, LPCWSTR lpString, int cbString)
{
    TextOutW(hdc, nXStart, nYStart, lpString, cbString);
    return TRUE;
}


WORD_CAPTURE_API BOOL WINAPI WC_aaa(HDC hdc, int X, int Y, UINT fuOptions, CONST RECT *lprc, LPCSTR lpString, UINT cbCount, CONST INT *lpDx)
{
    ExtTextOutA(hdc, X, Y, fuOptions, lprc, lpString, cbCount, lpDx);
    return TRUE;
}


WORD_CAPTURE_API BOOL WINAPI NHExtTextOutW(HDC hdc, int X, int Y, UINT fuOptions, CONST RECT *lprc, LPCWSTR lpString, UINT cbCount, CONST INT *lpDx)
{
    ExtTextOutW(hdc, X, Y, fuOptions, lprc, lpString, cbCount, lpDx);

    return TRUE;
}

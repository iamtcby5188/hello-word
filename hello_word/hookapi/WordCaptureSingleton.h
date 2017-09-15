#pragma once
#include "struct_define.h"
WORD_CAPTURE_API     BOOL  NHBitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);
WORD_CAPTURE_API     BOOL  NHTextOutA(HDC hdc, int nXStart, int nYStart, LPCSTR lpString, int cbString);
WORD_CAPTURE_API     BOOL  NHTextOutW(HDC hdc, int nXStart, int nYStart, LPCWSTR lpString, int cbString);
WORD_CAPTURE_API     BOOL  NHExtTextOutA(HDC hdc, int X, int Y, UINT fuOptions, CONST RECT *lprc, LPCSTR lpString, UINT cbCount, CONST INT *lpDx);
WORD_CAPTURE_API     BOOL  NHExtTextOutW(HDC hdc, int X, int Y, UINT fuOptions, CONST RECT *lprc, LPCWSTR lpString, UINT cbCount, CONST INT *lpDx);

class CWordCaptureSingleton
{
public:
    static CWordCaptureSingleton& instance();
public:
    void InitClass(HINSTANCE curIns);

private:
    ~CWordCaptureSingleton(){}
    CWordCaptureSingleton();

    bool m_bInit;

    APIHOOKSTRUCT m_BitBltHook;
    APIHOOKSTRUCT m_TextOutAHook;
    APIHOOKSTRUCT m_TextOutWHook;
    APIHOOKSTRUCT m_ExtTextOutAHook;
    APIHOOKSTRUCT m_ExtTextOutWHook;
};


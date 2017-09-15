#include "stdafx.h"
#include "WordCaptureSingleton.h"
#include "HookApi.h"
#include "WordCapture.h"
WORD_CAPTURE_API BOOL  NHBitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop)
{
    //BitBlt(hdcDest, nXDest, nYDest, nWidth, nHeight,hdcSrc, nXSrc, nYSrc, dwRop);
    return TRUE;
}


WORD_CAPTURE_API BOOL  NHTextOutA(HDC hdc, int nXStart, int nYStart, LPCSTR lpString, int cbString)
{
    //TextOutA(hdc, nXStart, nYStart, lpString, cbString);
    return TRUE;
}


WORD_CAPTURE_API  BOOL  NHTextOutW(HDC hdc, int nXStart, int nYStart, LPCWSTR lpString, int cbString)
{
    TextOutW(hdc, nXStart, nYStart, lpString, cbString);
    return TRUE;
}


WORD_CAPTURE_API BOOL  NHExtTextOutA(HDC hdc, int X, int Y, UINT fuOptions, CONST RECT *lprc, LPCSTR lpString, UINT cbCount, CONST INT *lpDx)
{
    ExtTextOutA(hdc, X, Y, fuOptions, lprc, lpString, cbCount, lpDx);
    return TRUE;
}


WORD_CAPTURE_API BOOL  NHExtTextOutW(HDC hdc, int X, int Y, UINT fuOptions, CONST RECT *lprc, LPCWSTR lpString, UINT cbCount, CONST INT *lpDx)
{
    ExtTextOutW(hdc, X, Y, fuOptions, lprc, lpString, cbCount, lpDx);

    return TRUE;
}

CWordCaptureSingleton& CWordCaptureSingleton::instance()
{
    static CWordCaptureSingleton s_ins;
    return s_ins;
}

CWordCaptureSingleton::CWordCaptureSingleton()
    :m_BitBltHook("BitBlt", "NHBitBlt")
    , m_TextOutAHook("TextOutA", "NHTextOutA")
    , m_TextOutWHook("TextOutW", "NHTextOutW")
    , m_ExtTextOutAHook("ExtTextOutA", "NHExtTextOutA")
    , m_ExtTextOutWHook("ExtTextOutW", "WC_Test")
    , m_bInit(false)
{
}



void CWordCaptureSingleton::InitClass(HINSTANCE curIns)
{
    //if (!m_bInit)
    //{
    //    m_ExtTextOutWHook.hInst = curIns;
    //    m_ExtTextOutAHook.hInst = curIns;
        m_TextOutWHook.hInst = curIns;
        //m_TextOutAHook.hInst = curIns;
    //    m_BitBltHook.hInst = curIns;

    //    m_bInit = true;
    //}

    //HookApi(&m_ExtTextOutWHook, HOOK_CAN_WRITE);
    //HookApi(&m_ExtTextOutAHook, HOOK_CAN_WRITE);
    //HookApi(&m_TextOutWHook, HOOK_CAN_WRITE);
    //HookApi(&m_TextOutAHook, HOOK_CAN_WRITE);
    //HookApi(&m_BitBltHook, HOOK_CAN_WRITE);

    HOOKFUNCDESC hd;
    PROC pOrigFuns;
    //hd.szFunc = "BitBlt";
    //hd.pProc = (PROC)NHBitBlt;
    //HookImportFunction(curIns, "gdi32.dll", &hd, &pOrigFuns);

    //hd.szFunc = "TextOutA";
    //hd.pProc = (PROC)NHTextOutA;
    //HookImportFunction(curIns, "gdi32.dll", &hd, &pOrigFuns);

    hd.szFunc = "TextOutW";
    hd.pProc = (PROC)NHTextOutW;
    HookImportFunction(curIns,"gdi32.dll", &hd, &pOrigFuns);


    //hd.szFunc = "ExtTextOutA";
    //hd.pProc = (PROC)NHExtTextOutA;
    //HookImportFunction(curIns, "gdi32.dll", &hd, &pOrigFuns);

    //hd.szFunc = "ExtTextOutW";
    //hd.pProc = (PROC)NHExtTextOutW;
    //HookImportFunction(curIns, "gdi32.dll", &hd, &pOrigFuns);

}
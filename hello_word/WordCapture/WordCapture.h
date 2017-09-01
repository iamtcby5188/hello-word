#ifndef _WORD_CAPTURE_H_
#define _WORD_CAPTURE_H_

#ifdef __cplusplus
extern "C"{
#endif

#ifdef WORDCAPTURE_EXPORTS
#define WORD_CAPTURE_API __declspec(dllexport)
#else
#define WORD_CAPTURE_API __declspec(dllimport)
#endif

    WORD_CAPTURE_API  int WC_Test(int a, int b);
    WORD_CAPTURE_API void WC_Init(HINSTANCE hIns);

    WORD_CAPTURE_API BOOL WINAPI NHBitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);
    WORD_CAPTURE_API BOOL WINAPI NHTextOutA(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString);
    WORD_CAPTURE_API BOOL WINAPI NHTextOutW(HDC hdc, int nXStart, int nYStart, LPCWSTR lpString, int cbString);
    WORD_CAPTURE_API BOOL WINAPI WC_aaa(HDC hdc, int X, int Y, UINT fuOptions, CONST RECT *lprc, LPCTSTR lpString, UINT cbCount, CONST INT *lpDx);
    WORD_CAPTURE_API BOOL WINAPI NHExtTextOutW(HDC hdc, int X, int Y, UINT fuOptions, CONST RECT *lprc, LPCWSTR lpString, UINT cbCount, CONST INT *lpDx);

#ifdef __cplusplus
}
#endif

#endif
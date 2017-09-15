#include "stdafx.h"
#include "WordCaptureSingleton.h"
#include <vector>
#include <mmsystem.h>
#include <shellapi.h>
#include <shlobj.h>
#pragma comment(lib,"Winmm.lib")
CWordCaptureSingleton* CWordCaptureSingleton::s_ins = nullptr;
CWordCaptureSingleton* CWordCaptureSingleton::instance()
{
    if (s_ins == nullptr)
    {
        s_ins = new CWordCaptureSingleton();
    }

    return s_ins;
}

void CWordCaptureSingleton::release()
{
    if (s_ins != nullptr)
    {
        delete s_ins;
        s_ins = nullptr;
    }
}

CWordCaptureSingleton::CWordCaptureSingleton()
    :m_hMouseHook(nullptr)
    , m_hDllInstance(nullptr)
    , m_hCurWnd(nullptr)
    , m_bLButtonDown(false)
    , m_is_copy(false)
    , m_cbf(nullptr)
    , m_bHookStart(false)
    , m_bMouseMove(false)
{
    m_CFType[0] = CF_TEXT;
    m_CFType[1] = CF_BITMAP;
    m_CFType[2] = CF_METAFILEPICT;
    m_CFType[3] = CF_SYLK;
    m_CFType[4] = CF_DIF;
    m_CFType[5] = CF_TIFF;
    m_CFType[6] = CF_OEMTEXT;
    m_CFType[7] = CF_DIB;
    m_CFType[8] = CF_PALETTE;
    m_CFType[9] = CF_PENDATA;
    m_CFType[10] = CF_RIFF;
    m_CFType[11] = CF_WAVE;
    m_CFType[12] = CF_UNICODETEXT;
    m_CFType[13] = CF_ENHMETAFILE;
    m_CFType[14] = CF_HDROP;
    m_CFType[15] = CF_LOCALE;
    m_CFType[16] = CF_DIBV5;
}


CWordCaptureSingleton::~CWordCaptureSingleton()
{
}

LRESULT CALLBACK LowLevelMouseHook(int nCode, WPARAM wp, LPARAM lp)
{
    return CWordCaptureSingleton::instance()->LowLevelMouseProc(nCode, wp, lp);
}


void CWordCaptureSingleton::StartCapture(std::function<void(char*, int)> cbf)
{
    if (!m_bHookStart)
    {
        m_bHookStart = true;
        m_cbf = cbf;
        m_hMouseHook = ::SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseHook, m_hDllInstance, 0);
    }
}

void CWordCaptureSingleton::StopCapture()
{
    if (m_bHookStart && m_hMouseHook != nullptr)
    {
        ::UnhookWindowsHookEx(m_hMouseHook);
    }
    m_bHookStart = false;
    m_cbf = nullptr;
}

LRESULT CWordCaptureSingleton::LowLevelMouseProc(int nCode, WPARAM wp, LPARAM lp)
{
    switch (wp)
    {
    case WM_LBUTTONDOWN:
        Hook_LButtonDown();
        break;
    case WM_LBUTTONUP:
        Hook_LButtonUp();
        break;
    case WM_MOUSEMOVE:
        HooK_MouseMove();
        break;
    default:
        Hook_Default();
        break;
    }
    return CallNextHookEx(m_hMouseHook, nCode, wp, lp);
}

void CWordCaptureSingleton::TimerThreadProc(int nFlag)
{
    switch (nFlag)
    {
    case TIMER_POST_KEY_DOWN:
    {
        keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0);
        keybd_event('C', MapVirtualKey('C', 0), 0, 0);

        timeSetEvent(100, 1, [](UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2){
            timeKillEvent(uTimerID);
            CWordCaptureSingleton::instance()->TimerThreadProc(TIMER_POST_KEY_UP);
        }, NULL, TIME_ONESHOT);
    }
    break;
    case TIMER_POST_KEY_UP:
    {
        keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
        keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0);

        GetClipboardText();
        RestoreClipboardData();
        if (!m_clip_data.is_empty() && m_cbf != nullptr)
        {
            int size = m_clip_data.get_memsize();
            PVOID pb = m_clip_data.get_data();
            char* sz = new char[size];
            memset(sz, 0, size);
            memcpy(sz, pb, size);
            m_cbf(sz, size);
            delete[] sz;
        }
        m_is_copy = false;
        m_hCurWnd = nullptr;
    }
    break;
    default:
        break;
    }
}

void CWordCaptureSingleton::Hook_LButtonDown()
{
    HWND hWndCur = GetWindowFromPoint();
    if (hWndCur != nullptr && !m_is_copy)
    {
        m_bLButtonDown = true;
        m_hCurWnd = hWndCur;
    }
}

void CWordCaptureSingleton::Hook_LButtonUp()
{
    HWND hWndCur = GetWindowFromPoint();
    if (hWndCur != nullptr && !m_is_copy && m_bLButtonDown && m_bMouseMove)
    {
        if (hWndCur == m_hCurWnd)
        {
            m_is_copy = true;
            GetOrigClipboardData();

            timeSetEvent(100, 1, [](UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2){
                timeKillEvent(uTimerID);
                CWordCaptureSingleton::instance()->TimerThreadProc(TIMER_POST_KEY_DOWN);
            }, NULL, TIME_ONESHOT);
        }
    }

    m_bLButtonDown = false;
    m_bMouseMove = false;
}
void CWordCaptureSingleton::HooK_MouseMove()
{
    if (m_bLButtonDown){
        m_bMouseMove = true;
    }
}

void CWordCaptureSingleton::Hook_Default()
{
}

HWND CWordCaptureSingleton::GetWindowFromPoint()
{
    POINT ptCur = { 0, 0 };
    GetCursorPos(&ptCur);
    return WindowFromPoint(ptCur);
}

void CWordCaptureSingleton::GetOrigClipboardData()
{
    m_old_clip_data.release();
    UINT uFormat = CF_MAX;
    for (int i = 0; i < 20; ++i)
    {
        uFormat = m_CFType[i];
        if (IsClipboardFormatAvailable(uFormat))
        {
            break;
        }
    }
    if (uFormat <= 0 || uFormat >= CF_MAX)
    {
        return;
    }
    if (uFormat == CF_BITMAP || uFormat == CF_DIB)
    {
        OrigClipboardPicture();
    }
    //else if (uFormat == CF_HDROP)
    //{
    //    //OrigClipboardDrop();
    //}
    else
    {
        OrigClipboardData(uFormat);
    }
}

bool CWordCaptureSingleton::OrigClipboardData(UINT uFormat)
{
    bool bRet = false;
    if (OpenClipboard(m_hCurWnd) == TRUE)
    {
        HGLOBAL hGlobalMem = nullptr;
        PVOID   pMemByte = nullptr;

        hGlobalMem = ::GetClipboardData(uFormat);
        if (hGlobalMem != nullptr)
        {
            pMemByte = ::GlobalLock(hGlobalMem);
            DWORD dError = GetLastError();
            if (pMemByte != nullptr)
            {
                m_old_clip_data.release();
                m_old_clip_data.set_format(uFormat);
                m_old_clip_data.set_memsize(GlobalSize(hGlobalMem));
                m_old_clip_data.set_data(pMemByte);
                bRet = true;
            }

            ::GlobalUnlock(hGlobalMem);
        }

        CloseClipboard();
    }

    return bRet;
}
void CWordCaptureSingleton::OrigClipboardDrop()
{
    //文件列表格式和其他的格式其实是一样的，同样是文本
    //if (OpenClipboard(m_hCurWnd) == TRUE)
    //{
    //    HDROP   hGlobalMem = nullptr;

    //    hGlobalMem = (HDROP)::GetClipboardData(CF_HDROP);
    //    if (hGlobalMem != nullptr)
    //    {
    //        PVOID p = ::GlobalLock(hGlobalMem);
    //        int nsize = GlobalSize(hGlobalMem);
    //        int nCount = DragQueryFile(hGlobalMem, -1, NULL, 0);
    //        if (nCount <= 0)
    //        {
    //            return;
    //        }
    //        std::vector<std::string> vctFiles;
    //            int nMemeSize = sizeof(DROPFILES);
    //            for (int n = 0; n < nCount; ++n)
    //            {
    //                char szFile[MAX_PATH] = { 0 };
    //                DragQueryFileA(hGlobalMem, n, szFile, sizeof(szFile));
    //                vctFiles.push_back(std::string(szFile));
    //                
    //                nMemeSize += strlen(szFile) + 1;
    //            }

    //            nMemeSize += 1;

    //            HGLOBAL hTmp = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE, nMemeSize);
    //            LPDROPFILES pTmp = (LPDROPFILES)GlobalLock(hTmp);
    //            pTmp->pFiles = sizeof(DROPFILES);
    //            pTmp->fWide = FALSE;
    //            
    //            PBYTE pWrite = (PBYTE)pTmp + sizeof(DROPFILES); 
    //            for (int n = 0; n<vctFiles.size();++n)
    //            {
    //                std::string& f = vctFiles.at(0);
    //                memcpy(pWrite, f.c_str(), f.length() + 1);
    //                pWrite += (f.length() + 1);
    //            }

    //            m_old_clip_data.release();
    //            m_old_clip_data.set_format(CF_HDROP);
    //            m_old_clip_data.set_memsize(nMemeSize);
    //            m_old_clip_data.set_data(pTmp);
    //            GlobalUnlock(hTmp);

    //        ::GlobalUnlock(hGlobalMem);
    //    }

    //    CloseClipboard();
    //}

}
void CWordCaptureSingleton::OrigClipboardPicture()
{
    //这两个文件使用IsClipboardFormatAvailable 是，都是可用，但是可能取不出数据
    
    UINT uFormats[2] = { CF_BITMAP, CF_DIB };
    for (UINT i = 0; i < 2; ++i)
    {
        UINT uFormat = uFormats[i];
        if (OrigClipboardData(uFormat))
        {
            break;
        }
    }
}

void CWordCaptureSingleton::GetClipboardText()
{
    if (OpenClipboard(NULL) == TRUE)
    {
        m_clip_data.release();
        HGLOBAL hGlobalMem = GetClipboardData(CF_TEXT);
        PVOID   pMemByte = nullptr;
        if (hGlobalMem != NULL)
        {
            pMemByte = ::GlobalLock(hGlobalMem);
            if (pMemByte != nullptr)
            {
                m_clip_data.set_format(CF_TEXT);
                m_clip_data.set_memsize(GlobalSize(hGlobalMem));
                m_clip_data.set_data(pMemByte);
            }
            ::GlobalUnlock(hGlobalMem);
        }
        CloseClipboard();
    }
}

void CWordCaptureSingleton::RestoreClipboardData()
{
    if (m_old_clip_data.is_empty())
    {
        if (OpenClipboard(NULL) == TRUE)
        {
            EmptyClipboard();
            CloseClipboard();
        }
    }
    else
    {
        if (OpenClipboard(m_hCurWnd) == TRUE)
        {
            char a[2][32] = {
                "aaaa",
                "bbbbbb"
            };
            int asss = sizeof(a);
            EmptyClipboard();
            int memsize = m_old_clip_data.get_memsize();
            PVOID pdata = m_old_clip_data.get_data();
            UINT uFormat = m_old_clip_data.get_format();

            HANDLE hGlobalMeme = GlobalAlloc(GMEM_MOVEABLE, memsize);
            if (hGlobalMeme != nullptr)
            {
                LPVOID lp = GlobalLock(hGlobalMeme);
                memset(lp, 0, memsize);
                memcpy(lp, pdata, memsize);

                GlobalUnlock(hGlobalMeme);
                SetClipboardData(uFormat, lp);
                DWORD d = GetLastError();
            }
            CloseClipboard();
        }

        m_old_clip_data.release();
    }
}

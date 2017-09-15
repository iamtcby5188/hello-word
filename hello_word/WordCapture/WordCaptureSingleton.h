#pragma once
#include <functional>
struct clip_struct
{
private:
    UINT m_uFormat;
    PVOID m_hMem;
    int  m_nMemSize;
public:
    clip_struct()
        :m_uFormat(CF_TEXT)
        , m_hMem(nullptr)
        , m_nMemSize(0)
    {

    }

    ~clip_struct()
    {
        if (m_hMem != nullptr)
        {
            delete[] m_hMem;
            m_nMemSize = 0;
        }
    }

    void set_format(UINT uFormat){ m_uFormat = uFormat; }
    UINT get_format(){ return m_uFormat; }
    void set_memsize(int memSize){ m_nMemSize = memSize; }
    int  get_memsize(){ return m_nMemSize; }
    void set_data(PVOID data)
    {
        if (m_nMemSize > 0)
        {
            m_hMem = malloc(m_nMemSize );
            memset(m_hMem, 0, m_nMemSize );

            memcpy(m_hMem, data, m_nMemSize);
        }
    }

    PVOID get_data(){ return m_hMem; }
    void release()
    {
        if (m_hMem != nullptr)
        {
            free(m_hMem);
            m_hMem = nullptr;
            m_nMemSize = 0;
        }
    }

    bool is_empty()
    {
        return (m_nMemSize <= 0 || m_hMem == nullptr);
    }
};

const int TIMER_POST_KEY_DOWN = 1;
const int TIMER_POST_KEY_UP = 2;

class CWordCaptureSingleton
{
public: 
    static CWordCaptureSingleton* s_ins;
    static CWordCaptureSingleton* instance();
    static void release();
public:
    void   SetDllHandle(HMODULE hInstance){m_hDllInstance = hInstance;}
    void   StartCapture(std::function<void(char*, int)>  cbf);
    void   StopCapture();

    LRESULT LowLevelMouseProc(int nCode,WPARAM wp,LPARAM lp);
    void    TimerThreadProc(int nFlag);
private:
    void Hook_LButtonDown();
    void Hook_LButtonUp();
    void HooK_MouseMove();
    void Hook_Default();

    HWND GetWindowFromPoint();
    void GetOrigClipboardData();
    bool OrigClipboardData(UINT uFormat);
    void OrigClipboardDrop();
    void OrigClipboardPicture();


    void GetClipboardText();
    void RestoreClipboardData();

private:
    bool m_bHookStart;
    HINSTANCE m_hDllInstance;
    HHOOK m_hMouseHook;

    HWND m_hCurWnd;
    bool m_bLButtonDown;
    bool m_bMouseMove;

    clip_struct m_old_clip_data;
    clip_struct m_clip_data;

    bool m_is_copy;  //是否正在识别
    std::function<void(char*, int)>  m_cbf;
    int m_CFType[18];
private:
    CWordCaptureSingleton();
    ~CWordCaptureSingleton();
};
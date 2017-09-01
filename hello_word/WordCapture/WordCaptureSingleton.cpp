#include "stdafx.h"
#include "WordCaptureSingleton.h"
#include "HookApi.h"

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
    if (!m_bInit)
    {
        m_ExtTextOutWHook.hInst = curIns;
        m_ExtTextOutAHook.hInst = curIns;
        m_TextOutWHook.hInst = curIns;
        m_TextOutAHook.hInst = curIns;
        m_BitBltHook.hInst = curIns;

        m_bInit = true;
    }

    HookApi(&m_ExtTextOutWHook, HOOK_CAN_WRITE);
    HookApi(&m_ExtTextOutAHook, HOOK_CAN_WRITE);
    HookApi(&m_TextOutWHook, HOOK_CAN_WRITE);
    HookApi(&m_TextOutAHook, HOOK_CAN_WRITE);
    HookApi(&m_BitBltHook, HOOK_CAN_WRITE);
}
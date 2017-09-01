#pragma once
#include "struct_define.h"
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


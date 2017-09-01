#pragma once
#include <string>

#define HOOK_NEED_CHECK 0
#define HOOK_CAN_WRITE	1
#define HOOK_ONLY_READ	2

#define BUFFERLEN		7

typedef struct _tagApiHookStruct
{
    std::string  lpszApiModuleName;
    std::string  lpszApiName;
    DWORD  dwApiOffset;
    LPVOID lpWinApiProc;
    BYTE   WinApiFiveByte[7];

    std::string  lpszHookApiModuleName;
    std::string  lpszHookApiName;
    LPVOID lpHookApiProc;
    BYTE   HookApiFiveByte[7];

    HINSTANCE hInst;

    BYTE   WinApiBakByte[7];

    _tagApiHookStruct(const std::string& apiName, const std::string& hookApiName)
        :lpszApiModuleName("gdi32.dll")
        , lpszApiName(apiName)
        , dwApiOffset(0)
        , lpWinApiProc(NULL)
        , lpszHookApiModuleName("")
        , lpszHookApiName(hookApiName)
        , lpHookApiProc(NULL)
        , hInst(NULL)
    {
        for (int i = 0; i < 7; ++i)
        {
            WinApiFiveByte[i] = 0;
            HookApiFiveByte[i] = 0;
        }

        WinApiBakByte[0] = 0xFF;
        WinApiBakByte[1] = 0x15;
        WinApiBakByte[2] = 0xFA;
        WinApiBakByte[3] = 0x13;
        WinApiBakByte[4] = 0xF3;
        WinApiBakByte[5] = 0xBF;
        WinApiBakByte[6] = 0x33;
    }
}
APIHOOKSTRUCT, *LPAPIHOOKSTRUCT;

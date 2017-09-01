#include "stdafx.h"
#include "HookApi.h"

FARPROC WINAPI NHGetFuncAddress(HINSTANCE hInst, const std::string& lpMod, const std::string& lpFunc)
{
    HMODULE hMod;
    FARPROC procFunc;

    if (!lpMod.empty())
    {
        hMod = GetModuleHandleA(lpMod.c_str());
        procFunc = GetProcAddress(hMod, lpFunc.c_str());
    }
    else
    {
        procFunc = GetProcAddress(hInst, lpFunc.c_str());
        DWORD d = GetLastError();
        OutputDebugStringA("a");
    }

    return  procFunc;
}

void MakeJMPCode(LPBYTE lpJMPCode, LPVOID lpCodePoint)
{
    BYTE temp;
    WORD wHiWord = HIWORD(lpCodePoint);
    WORD wLoWord = LOWORD(lpCodePoint);
    WORD wCS;

    _asm						// ȡ��ǰ�x����q
    {
        push ax;
        push cs;
        pop  ax;
        mov  wCS, ax;
        pop  ax;
    };

    lpJMPCode[0] = 0xea;		// ���� JMP ָ��ęC���a�q

    temp = LOBYTE(wLoWord);		// -------------------------
    lpJMPCode[1] = temp;
    temp = HIBYTE(wLoWord);
    lpJMPCode[2] = temp;		// �����ַ�q�ڃȴ��е����飻
    temp = LOBYTE(wHiWord);		// Point: 0x1234
    lpJMPCode[3] = temp;		// �ȴ棺 4321
    temp = HIBYTE(wHiWord);
    lpJMPCode[4] = temp;		// -------------------------

    temp = LOBYTE(wCS);			// �����x����q
    lpJMPCode[5] = temp;
    temp = HIBYTE(wCS);
    lpJMPCode[6] = temp;

    return;
}

void HookApi(LPAPIHOOKSTRUCT lpApiHook, int nSysMemStatus)
{
    DWORD  dwReserved;
    DWORD  dwTemp;
    BYTE   bWin32Api[5];

    bWin32Api[0] = 0x00;

    // ȡ�ñ��r�غ�����ַ�q
    if (lpApiHook->lpWinApiProc == NULL)
    {
        lpApiHook->lpWinApiProc = (LPVOID)NHGetFuncAddress(lpApiHook->hInst, lpApiHook->lpszApiModuleName, lpApiHook->lpszApiName);
        if (lpApiHook->dwApiOffset != 0)
            lpApiHook->lpWinApiProc = (LPVOID)((DWORD)lpApiHook->lpWinApiProc + lpApiHook->dwApiOffset);
    }
    // ȡ�����������ַ�q
    if (lpApiHook->lpHookApiProc == NULL)
    {
        lpApiHook->lpHookApiProc = (LPVOID)NHGetFuncAddress(lpApiHook->hInst, lpApiHook->lpszHookApiModuleName, lpApiHook->lpszHookApiName);
    }
    // �γ� JMP ָ��q
    if (lpApiHook->HookApiFiveByte[0] == 0x00)
    {
        MakeJMPCode(lpApiHook->HookApiFiveByte, lpApiHook->lpHookApiProc);
    }

    if (!VirtualProtect(lpApiHook->lpWinApiProc, 16, PAGE_READWRITE, &dwReserved))
    {
        MessageBoxA(NULL, "VirtualProtect-READWRITE", NULL, MB_OK);
        return;
    }

    if (nSysMemStatus == HOOK_NEED_CHECK)
    {
        memcpy(lpApiHook->lpWinApiProc, (LPVOID)lpApiHook->HookApiFiveByte, BUFFERLEN);
    }
    else
    {
        if (lpApiHook->WinApiFiveByte[0] == 0x00)			// �Д��Ƿ��ѽ��r�ةq
        {
            // ��q
            // ��� API �����^�傀�ֹ��q
            memcpy(lpApiHook->WinApiFiveByte, (LPVOID)lpApiHook->lpWinApiProc, BUFFERLEN);
            // �Д��Ƿ����}�r�ةq(���Д���ݵ��^�傀�ֹ��Ƿ���γɵ�JMPָ��)
            if (strncmp((char*)lpApiHook->WinApiFiveByte, (char*)lpApiHook->HookApiFiveByte, BUFFERLEN) == 0)
            {
                // �֏͂�ݵ��ֹ��q
                memcpy(lpApiHook->WinApiFiveByte, (LPVOID)lpApiHook->WinApiBakByte, BUFFERLEN);
            }
        }
        else
        {
            // �ǩq
            memcpy(bWin32Api, (LPVOID)lpApiHook->lpWinApiProc, BUFFERLEN);
        }

        if (strncmp((char*)bWin32Api, (char*)lpApiHook->HookApiFiveByte, BUFFERLEN) != 0)
        {
            // �� JMP ָ������ API �������^�q
            memcpy(lpApiHook->lpWinApiProc, (LPVOID)lpApiHook->HookApiFiveByte, BUFFERLEN);
        }
    }

    if (!VirtualProtect(lpApiHook->lpWinApiProc, 16, dwReserved, &dwTemp))
    {
        MessageBoxA(NULL, "VirtualProtect-RESTORE", NULL, MB_OK);
        return;
    }
}

void RestoreWin32Api(LPAPIHOOKSTRUCT lpApiHook, int nSysMemStatus)
{
    DWORD dwReserved;
    DWORD dwTemp;

    if (lpApiHook->lpWinApiProc == NULL)
        return;

    if (!VirtualProtect(lpApiHook->lpWinApiProc, 16, PAGE_READWRITE, &dwReserved))
    {
        MessageBoxA(NULL, "VirtualProtect-READWRITE", NULL, MB_OK);
        return;
    }
    memcpy(lpApiHook->lpWinApiProc, (LPVOID)lpApiHook->WinApiFiveByte, BUFFERLEN);
    if (!VirtualProtect(lpApiHook->lpWinApiProc, 16, dwReserved, &dwTemp))
    {
        MessageBoxA(NULL, "VirtualProtect-RESTORE", NULL, MB_OK);
        return;
    }
}

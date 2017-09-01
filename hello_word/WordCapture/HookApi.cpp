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

    _asm						// 取當前選擇符﹒
    {
        push ax;
        push cs;
        pop  ax;
        mov  wCS, ax;
        pop  ax;
    };

    lpJMPCode[0] = 0xea;		// 填入 JMP 指令的機器碼﹒

    temp = LOBYTE(wLoWord);		// -------------------------
    lpJMPCode[1] = temp;
    temp = HIBYTE(wLoWord);
    lpJMPCode[2] = temp;		// 填入地址﹒在內存中的順序為；
    temp = LOBYTE(wHiWord);		// Point: 0x1234
    lpJMPCode[3] = temp;		// 內存： 4321
    temp = HIBYTE(wHiWord);
    lpJMPCode[4] = temp;		// -------------------------

    temp = LOBYTE(wCS);			// 填入選擇符﹒
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

    // 取得被攔截函數地址﹒
    if (lpApiHook->lpWinApiProc == NULL)
    {
        lpApiHook->lpWinApiProc = (LPVOID)NHGetFuncAddress(lpApiHook->hInst, lpApiHook->lpszApiModuleName, lpApiHook->lpszApiName);
        if (lpApiHook->dwApiOffset != 0)
            lpApiHook->lpWinApiProc = (LPVOID)((DWORD)lpApiHook->lpWinApiProc + lpApiHook->dwApiOffset);
    }
    // 取得替代函數地址﹒
    if (lpApiHook->lpHookApiProc == NULL)
    {
        lpApiHook->lpHookApiProc = (LPVOID)NHGetFuncAddress(lpApiHook->hInst, lpApiHook->lpszHookApiModuleName, lpApiHook->lpszHookApiName);
    }
    // 形成 JMP 指令﹒
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
        if (lpApiHook->WinApiFiveByte[0] == 0x00)			// 判斷是否已經攔截﹒
        {
            // 否﹒
            // 備份 API 函數頭五個字節﹒
            memcpy(lpApiHook->WinApiFiveByte, (LPVOID)lpApiHook->lpWinApiProc, BUFFERLEN);
            // 判斷是否重複攔截﹒(即判斷備份的頭五個字節是否為形成的JMP指令)
            if (strncmp((char*)lpApiHook->WinApiFiveByte, (char*)lpApiHook->HookApiFiveByte, BUFFERLEN) == 0)
            {
                // 恢復備份的字節﹒
                memcpy(lpApiHook->WinApiFiveByte, (LPVOID)lpApiHook->WinApiBakByte, BUFFERLEN);
            }
        }
        else
        {
            // 是﹒
            memcpy(bWin32Api, (LPVOID)lpApiHook->lpWinApiProc, BUFFERLEN);
        }

        if (strncmp((char*)bWin32Api, (char*)lpApiHook->HookApiFiveByte, BUFFERLEN) != 0)
        {
            // 將 JMP 指定填入 API 函數的頭﹒
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

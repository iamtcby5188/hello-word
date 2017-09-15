#include "stdafx.h"
#include "HookApi.h"

#pragma warning(disable:4996)
FARPROC NHGetFuncAddress(HINSTANCE hInst, const std::string& lpMod, const std::string& lpFunc)
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

    lpJMPCode[0] = 0xEA;		// ���� JMP ָ��ęC���a�q

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

///////////////////////////////////////////// Begin ///////////////////////////////////////////////////////////////
#include <crtdbg.h>


// ���ǵ�������
BOOL HookImportFunction(HMODULE hModule, LPCSTR szImportModule, LPHOOKFUNCDESC paHookFunc, PROC* paOrigFuncs)
{
    /////////////////////// ����Ĵ������������Ч�� ////////////////////////////
    _ASSERT(szImportModule);
    _ASSERT(!IsBadReadPtr(paHookFunc, sizeof(HOOKFUNCDESC)));
#ifdef _DEBUG
    if (paOrigFuncs) _ASSERT(!IsBadWritePtr(paOrigFuncs, sizeof(PROC)));
    _ASSERT(paHookFunc->szFunc);
    _ASSERT(*paHookFunc->szFunc != '/0');
    _ASSERT(!IsBadCodePtr(paHookFunc->pProc));
#endif
    if ((szImportModule == NULL) || (IsBadReadPtr(paHookFunc, sizeof(HOOKFUNCDESC))))
    {
        _ASSERT(FALSE);
        SetLastErrorEx(ERROR_INVALID_PARAMETER, SLE_ERROR);
        return FALSE;
    }
    //////////////////////////////////////////////////////////////////////////////

    // ��⵱ǰģ���Ƿ�����2GB�����ڴ�ռ�֮��
    // �ⲿ�ֵĵ�ַ�ڴ�������Win32���̹����
    if (!IsNT() && ((DWORD)hModule >= 0x80000000))
    {
        _ASSERT(FALSE);
        SetLastErrorEx(ERROR_INVALID_HANDLE, SLE_ERROR);
        return FALSE;
    }
    // ����
    if (paOrigFuncs) memset(paOrigFuncs, NULL, sizeof(PROC));

    // ����GetNamedImportDescriptor()����,���õ�hModule -- ��������Ҫ
    // �ػ�ĺ������ڵ�DLLģ�������������(import descriptor)
    PIMAGE_IMPORT_DESCRIPTOR pImportDesc = GetNamedImportDescriptor(hModule, szImportModule);
    if (pImportDesc == NULL)
        return FALSE; // ��Ϊ��,��ģ��δ����ǰ����������

    //  ��DLLģ���еõ�ԭʼ��THUNK��Ϣ,��ΪpImportDesc->FirstThunk�����е�ԭʼ��Ϣ�Ѿ�
    //  ��Ӧ�ó��������DLLʱ�����������е�������Ϣ,����������Ҫͨ��ȡ��pImportDesc->OriginalFirstThunk
    //  ָ�����������뺯��������Ϣ
    PIMAGE_THUNK_DATA pOrigThunk = MakePtr(PIMAGE_THUNK_DATA, hModule,pImportDesc->OriginalFirstThunk);

    //  ��pImportDesc->FirstThunk�õ�IMAGE_THUNK_DATA�����ָ��,����������DLL������ʱ�Ѿ������
    //  ���е�������Ϣ,���������Ľػ�ʵ����������������е�
    PIMAGE_THUNK_DATA pRealThunk = MakePtr(PIMAGE_THUNK_DATA, hModule, pImportDesc->FirstThunk);

    //  ���IMAGE_THUNK_DATA����,Ѱ��������Ҫ�ػ�ĺ���,������ؼ��Ĳ���!
    while (pOrigThunk->u1.Function)
    {
        // ֻѰ����Щ���������������������ĺ���
        if (IMAGE_ORDINAL_FLAG != (pOrigThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG))
        {
            // �õ����뺯���ĺ�����
            PIMAGE_IMPORT_BY_NAME pByName = MakePtr(PIMAGE_IMPORT_BY_NAME, hModule,pOrigThunk->u1.AddressOfData);

            // �����������NULL��ʼ,����,������һ������   
            if ('/0' == pByName->Name[0])
                continue;

            // bDoHook��������Ƿ�ػ�ɹ�
            BOOL bDoHook = FALSE;

            // ����Ƿ�ǰ������������Ҫ�ػ�ĺ���
            if (stricmp(paHookFunc->szFunc, (char*)pByName->Name) == 0)
            {
                // �ҵ���!
                if (paHookFunc->pProc) bDoHook = TRUE;
            }
            if (bDoHook)
            {
                // �����Ѿ��ҵ�����Ҫ�ػ�ĺ���,��ô�Ϳ�ʼ���ְ�
                // ����Ҫ�����Ǹı���һ�������ڴ���ڴ汣��״̬,�����ǿ������ɴ�ȡ
                MEMORY_BASIC_INFORMATION mbi_thunk;
                VirtualQuery(pRealThunk, &mbi_thunk, sizeof(MEMORY_BASIC_INFORMATION));
                _ASSERT(VirtualProtect(mbi_thunk.BaseAddress, mbi_thunk.RegionSize,PAGE_READWRITE, &mbi_thunk.Protect));

                // ����������Ҫ�ػ�ĺ�������ȷ��ת��ַ
                if (paOrigFuncs)
                    paOrigFuncs = (PROC*)pRealThunk->u1.Function;

                // ��IMAGE_THUNK_DATA�����еĺ�����ת��ַ��дΪ�����Լ��ĺ�����ַ!
                // �Ժ����н��̶����ϵͳ���������е��ö�����Ϊ�������Լ���д�ĺ����ĵ���
                pRealThunk->u1.Function = (DWORD)paHookFunc->pProc;

                // �������!����һ�������ڴ�Ļ�ԭ���ı���״̬
                DWORD dwOldProtect;
                _ASSERT(VirtualProtect(mbi_thunk.BaseAddress, mbi_thunk.RegionSize,mbi_thunk.Protect, &dwOldProtect));
                SetLastError(ERROR_SUCCESS);
                return TRUE;
            }
        }
        // ����IMAGE_THUNK_DATA�����е���һ��Ԫ��
        pOrigThunk++;
        pRealThunk++;
    }
    return TRUE;
}

// GetNamedImportDescriptor������ʵ��
PIMAGE_IMPORT_DESCRIPTOR GetNamedImportDescriptor(HMODULE hModule, LPCSTR szImportModule)
{
    // ������
    _ASSERT(szImportModule);
    _ASSERT(hModule);
    if ((szImportModule == NULL) || (hModule == NULL))
    {
        _ASSERT(FALSE);
        SetLastErrorEx(ERROR_INVALID_PARAMETER, SLE_ERROR);
        return NULL;
    }

    // �õ�Dos�ļ�ͷ
    PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule;

    // ����Ƿ�MZ�ļ�ͷ
    if (IsBadReadPtr(pDOSHeader, sizeof(IMAGE_DOS_HEADER)) ||
        (pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE))
    {
        _ASSERT(FALSE);
        SetLastErrorEx(ERROR_INVALID_PARAMETER, SLE_ERROR);
        return NULL;
    }

    // ȡ��PE�ļ�ͷ
    PIMAGE_NT_HEADERS pNTHeader = MakePtr(PIMAGE_NT_HEADERS, pDOSHeader, pDOSHeader->e_lfanew);

    // ����Ƿ�PEӳ���ļ�
    if (IsBadReadPtr(pNTHeader, sizeof(IMAGE_NT_HEADERS)) ||
        (pNTHeader->Signature != IMAGE_NT_SIGNATURE))
    {
        _ASSERT(FALSE);
        SetLastErrorEx(ERROR_INVALID_PARAMETER, SLE_ERROR);
        return NULL;
    }

    // ���PE�ļ��������(�� .idata section)
    if (pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress == 0)
        return NULL;

    // �õ������(�� .idata section)��ָ��
    PIMAGE_IMPORT_DESCRIPTOR pImportDesc = MakePtr(PIMAGE_IMPORT_DESCRIPTOR, pDOSHeader,pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    // ���PIMAGE_IMPORT_DESCRIPTOR����Ѱ��������Ҫ�ػ�ĺ������ڵ�ģ��
    while (pImportDesc->Name)
    {
        PSTR szCurrMod = MakePtr(PSTR, pDOSHeader, pImportDesc->Name);
        if (strcmpi(szCurrMod, szImportModule) == 0)
            break; // �ҵ�!�ж�ѭ��
        // ��һ��Ԫ��
        pImportDesc++;
    }

    // ���û���ҵ�,˵������Ѱ�ҵ�ģ��û�б���ǰ�Ľ���������!
    if (pImportDesc->Name == NULL)
        return NULL;

    // ���غ������ҵ���ģ��������(import descriptor)
    return pImportDesc;
}

// IsNT()������ʵ��
BOOL IsNT()
{
    OSVERSIONINFO stOSVI;
    memset(&stOSVI, NULL, sizeof(OSVERSIONINFO));
    stOSVI.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    BOOL bRet = TRUE;// GetVersionEx(&stOSVI);
    _ASSERT(TRUE == bRet);
    if (FALSE == bRet) return FALSE;
    return (VER_PLATFORM_WIN32_NT == stOSVI.dwPlatformId);
}
/////////////////////////////////////////////// End //////////////////////////////////////////////////////////////////////
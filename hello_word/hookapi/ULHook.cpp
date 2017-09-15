///////////////////////////////////////////   
// ULHook.cpp�ļ�         
#include "stdafx.h"
#include "ULHook.h"         
CULHook::CULHook(LPSTR pszModName, LPSTR pszFuncName, PROC pfnHook)
{
    // jmp eax == 0xFF, 0xE0       
    // �����µ�ִ�д���  
    BYTE btNewBytes[8] = { 0xB8, 0x00, 0x00, 0x40, 0x00, 0xFF, 0xE0, 0x00 };
    memcpy(m_btNewBytes, btNewBytes, 8);
    *(DWORD *)(m_btNewBytes + 1) = (DWORD)pfnHook;            // ����ָ��ģ�飬ȡ��API������ַ    
    m_hModule = ::LoadLibraryA(pszModName);
    if (m_hModule == NULL)
    {
        m_pfnOrig = NULL;
        return;
    }
    m_pfnOrig = ::GetProcAddress(m_hModule, pszFuncName);              // �޸�ԭAPI����ִ�д����ǰ���ֽڣ�ʹ���������ǵĺ���        
    if (m_pfnOrig != NULL)
    {
        DWORD dwOldProtect;
        MEMORY_BASIC_INFORMATION    mbi;
        ::VirtualQuery(m_pfnOrig, &mbi, sizeof(mbi));
        ::VirtualProtect(m_pfnOrig, 8, PAGE_READWRITE, &dwOldProtect);
        // ����ԭ����ִ�д���     
        memcpy(m_btOldBytes, m_pfnOrig, 8);            // д���µ�ִ�д���     
        ::WriteProcessMemory(::GetCurrentProcess(), (void *)m_pfnOrig, m_btNewBytes, sizeof(DWORD) * 2, NULL);
        ::VirtualProtect(m_pfnOrig, 8, mbi.Protect, 0);
    }
}
CULHook::~CULHook()
{
    Unhook();
    if (m_hModule != NULL)
        ::FreeLibrary(m_hModule);
}
void CULHook::Unhook()
{
    if (m_pfnOrig != NULL)
    {
        DWORD dwOldProtect;
        MEMORY_BASIC_INFORMATION    mbi;
        ::VirtualQuery(m_pfnOrig, &mbi, sizeof(mbi));
        ::VirtualProtect(m_pfnOrig, 8, PAGE_READWRITE, &dwOldProtect);// д��ԭ����ִ�д���            
        ::WriteProcessMemory(::GetCurrentProcess(), (void *)m_pfnOrig, m_btOldBytes, sizeof(DWORD) * 2, NULL);
        ::VirtualProtect(m_pfnOrig, 8, mbi.Protect, 0);
    }
}
void CULHook::Rehook()
{        // �޸�ԭAPI����ִ�д����ǰ���ֽڣ�ʹ���������ǵĺ���   
    if (m_pfnOrig != NULL)
    {
        DWORD dwOldProtect;
        MEMORY_BASIC_INFORMATION    mbi;
        ::VirtualQuery(m_pfnOrig, &mbi, sizeof(mbi));
        ::VirtualProtect(m_pfnOrig, 8, PAGE_READWRITE, &dwOldProtect);
        // д���µ�ִ�д���     
        ::WriteProcessMemory(::GetCurrentProcess(), (void *)m_pfnOrig, m_btNewBytes, sizeof(DWORD) * 2, NULL);
        ::VirtualProtect(m_pfnOrig, 8, mbi.Protect, 0);
    }
}


//BOOL ChangeFuncEntry(HMODULE hmodule)
//
//{
//    PIMAGE_DOS_HEADER pDOSHeader;
//
//    PIMAGE_NT_HEADERS pNTHeader;
//
//    PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
//
//    /*get system functions and my functions��entry�� */
//
//    DWORD pSysFunc1 = (DWORD)GetProcAddress(GetModuleHandleA("gdi32.dll"), "TextOutA");
//
//    DWORD pMyFunc1 = (DWORD)GetProcAddress(GetModuleHandleA("hookdll.dll"), "MyTextOutA");
//
//    pDOSHeader = (PIMAGE_DOS_HEADER)hmodule;
//
//    if (IsBadReadPtr(hmodule, sizeof(PIMAGE_NT_HEADERS)))
//
//        return FALSE;
//
//    if (pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE)
//
//        return FALSE;
//
//    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pDOSHeader + (DWORD)pDOSHeader->e_lfanew);
//
//    if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
//
//        return FALSE;
//
//    pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)hmodule + (DWORD)pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
//
//    if (pImportDesc == (PIMAGE_IMPORT_DESCRIPTOR)pNTHeader)
//        return FALSE;
//
//    while (pImportDesc->Name)
//    {
//        PIMAGE_THUNK_DATA pThunk;
//
//        strcpy(buffer, (char*)((DWORD)hmodule + (DWORD)pImportDesc->Name));
//
//        CharLower(buffer);
//
//        if (strcmp(buffer, "gdi32.dll"))
//
//        {
//            pImportDesc++;
//
//            continue;
//
//        }
//        else
//        {
//            pThunk = (PIMAGE_THUNK_DATA)((DWORD)hmodule + (DWORD)pImportDesc->FirstThunk);
//
//            while (pThunk->u1.Function)
//
//            {
//                if ((pThunk->u1.Function) == pSysFunc1)
//
//                {
//                    VirtualProtect((LPVOID)(&pThunk->u1.Function),sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwProtect);
//                    (pThunk->u1.Function) = pMyFunc1;
//                    VirtualProtect((LPVOID)(&pThunk->u1.Function), sizeof(DWORD), dwProtect, &temp);
//                }
//
//                pThunk++;
//            } 
//            return 1;
//        }
//    }
//}

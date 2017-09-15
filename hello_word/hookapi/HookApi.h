#pragma once
#include "struct_define.h"

FARPROC NHGetFuncAddress(HINSTANCE hInst, const std::string& lpMod, const std::string& lpFunc);
void MakeJMPCode(LPBYTE lpJMPCode, LPVOID lpCodePoint);
void HookApi(LPAPIHOOKSTRUCT lpApiHook, int nSysMemStatus);

// ���ﶨ����һ������ָ��ĺ�
#define MakePtr(cast, ptr, AddValue) (cast)((DWORD)(ptr)+(DWORD)(AddValue))

// ������HOOKFUNCDESC�ṹ,����������ṹ��Ϊ��������HookImportFunction����
typedef struct tag_HOOKFUNCDESC
{
    LPCSTR szFunc; // The name of the function to hook.
    PROC pProc;    // The procedure to blast in.
} HOOKFUNCDESC, *LPHOOKFUNCDESC;

// ���������⵱ǰϵͳ�Ƿ���WindowNT
BOOL IsNT();

// ��������õ�hModule -- ��������Ҫ�ػ�ĺ������ڵ�DLLģ�������������(import descriptor)
PIMAGE_IMPORT_DESCRIPTOR GetNamedImportDescriptor(HMODULE hModule, LPCSTR szImportModule);
BOOL HookImportFunction(HMODULE hModule, LPCSTR szImportModule, LPHOOKFUNCDESC paHookFunc, PROC* paOrigFuncs);

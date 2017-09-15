#pragma once
#include "struct_define.h"

FARPROC NHGetFuncAddress(HINSTANCE hInst, const std::string& lpMod, const std::string& lpFunc);
void MakeJMPCode(LPBYTE lpJMPCode, LPVOID lpCodePoint);
void HookApi(LPAPIHOOKSTRUCT lpApiHook, int nSysMemStatus);

// 这里定义了一个产生指针的宏
#define MakePtr(cast, ptr, AddValue) (cast)((DWORD)(ptr)+(DWORD)(AddValue))

// 定义了HOOKFUNCDESC结构,我们用这个结构作为参数传给HookImportFunction函数
typedef struct tag_HOOKFUNCDESC
{
    LPCSTR szFunc; // The name of the function to hook.
    PROC pProc;    // The procedure to blast in.
} HOOKFUNCDESC, *LPHOOKFUNCDESC;

// 这个函数监测当前系统是否是WindowNT
BOOL IsNT();

// 这个函数得到hModule -- 即我们需要截获的函数所在的DLL模块的引入描述符(import descriptor)
PIMAGE_IMPORT_DESCRIPTOR GetNamedImportDescriptor(HMODULE hModule, LPCSTR szImportModule);
BOOL HookImportFunction(HMODULE hModule, LPCSTR szImportModule, LPHOOKFUNCDESC paHookFunc, PROC* paOrigFuncs);

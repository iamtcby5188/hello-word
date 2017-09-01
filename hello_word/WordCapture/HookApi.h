#pragma once
#include "struct_define.h"

FARPROC WINAPI NHGetFuncAddress(HINSTANCE hInst, const std::string& lpMod, const std::string& lpFunc);
void MakeJMPCode(LPBYTE lpJMPCode, LPVOID lpCodePoint);
void HookApi(LPAPIHOOKSTRUCT lpApiHook, int nSysMemStatus);



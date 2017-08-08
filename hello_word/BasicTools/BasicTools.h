#ifndef _BASIC_TOOLS_H_
#define _BASIC_TOOLS_H_

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _BASIC_TOOLS_H_
#define BASIC_TOOLS_API __declspec(dllexport)
#else
#define BASIC_TOOLS_API __declspec(dllimport)
#endif

    BASIC_TOOLS_API int Test(int a, int b);

#undef _BASIC_TOOLS_H_
#ifdef __cplusplus
}
#endif

#endif

#ifndef __MSGBUS_COMPILE_H
#define __MSGBUS_COMPILE_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLATFORM_LINUX   0
#define PLATFORM_WINDOWS 1

#if defined(WIN32) ||defined(_WINDOWS) || defined(_WIN32)
    #ifndef _WIN32
        #define _WIN32
    #endif

    #ifndef WIN32
        #define WIN32
    #endif

    #ifndef _WINDOWS
        #define _WINDOWS
    #endif

    #define OSTYPE OSTYPE_WINDOWS
#else
    #if defined(LINUX)
        #define OSTYPE OSTYPE_LINUX
    #else
        #error "unknown platform"
    #endif    
#endif


#if (OSTYPE == OSTYPE_WINDOWS)
    #ifdef MSGBUS_EXPORTS
        #define MSGBUSAPI __declspec(dllexport)
    #else
        //默认使用动态库
        #ifdef MSGBUS_STATIC_LINK
            #define MSGBUSAPI
        #else
            #define MSGBUSAPI __declspec(dllimport)
        #endif
    #endif

    /*
        确定64位还是32位
    */
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>

    #if defined(_AMD64_) || defined(_IA64_) 
        #define WORDSIZE 64
    #else
        #define WORDSIZE 32
    #endif 

#else
    #define MSGBUSAPI

    #include <stdint.h>
    #define WORDSIZE __WORDSIZE
#endif

#endif  /** __MSGBUS_COMPILE_H */

#ifndef _WORD_CAPTURE_H_
#define _WORD_CAPTURE_H_

#include "struct_define.h"
#include <functional>
#ifdef __cplusplus
extern "C"{
#endif

#ifdef WORDCAPTURE_EXPORTS
#define WORD_CAPTURE_API __declspec(dllexport)
#else
#define WORD_CAPTURE_API __declspec(dllimport)
#endif

    WORD_CAPTURE_API  int WC_Test(int a, int b);
    WORD_CAPTURE_API  void WC_Init();
    WORD_CAPTURE_API  void WC_Uninit();

    WORD_CAPTURE_API  void WC_StartCapture(std::function<void(char* ,int)> cbf);
    WORD_CAPTURE_API  void WC_StopCapture();
#ifdef __cplusplus
}
#endif



#endif
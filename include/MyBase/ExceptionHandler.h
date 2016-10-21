#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

// 该模块用于捕获用户未处理的异常，并且打印出调用堆栈以及源代码位置。
#include "MyBase/Common.h"

MY_BASE_API void InstallExceptionHandler();


#endif//EXCEPTION_HANDLER_H
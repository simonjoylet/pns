#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

/**
* This is a class to handle unhandled exceptions in a Windowns application. 
* For more information on how to use it: https://github.com/Furkanzmc/ExceptionHandler/
*/
#include "MyBase/Common.h"
#include <windows.h>
#include <string>

MY_BASE_API std::string showStack(HANDLE hThread, CONTEXT &c);
MY_BASE_API std::string filterCrash(EXCEPTION_POINTERS *ep);
MY_BASE_API void *loadModulesSymbols(HANDLE hProcess, DWORD pid);

MY_BASE_API void AccessNull();

#endif//EXCEPTION_HANDLER_H
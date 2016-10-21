#define MY_BASE_API __declspec(dllexport)
#include "MyBase/ExceptionHandler.h"
#include <windows.h>
#include <DbgHelp.h>

static LONG WINAPI TopExceptionHandler(EXCEPTION_POINTERS * ep)
{
	HANDLE process = GetCurrentProcess();

	// 初始化符号加载选项
	SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
	SymInitialize(process, NULL, TRUE);

	// 获取模块句柄、名称等信息
	HMODULE module = NULL;
	if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		reinterpret_cast<LPCSTR>(ep->ExceptionRecord->ExceptionAddress),
		&module))
	{
		printf("Module not found.\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}
	char modulename[256];
	if (GetModuleFileName(module, modulename, sizeof(modulename)) != 0)
	{
		printf("Crashed at %s.\n", modulename); // todo 添加异常类型信息
	}

	STACKFRAME frame = { 0 };
	frame.AddrPC.Offset = ep->ContextRecord->Eip;
	frame.AddrPC.Mode = AddrModeFlat;
	frame.AddrStack.Offset = ep->ContextRecord->Esp;
	frame.AddrStack.Mode = AddrModeFlat;
	frame.AddrFrame.Offset = ep->ContextRecord->Ebp;
	frame.AddrFrame.Mode = AddrModeFlat;

	printf("Waling Stack.\n");
	int stackcount = 0;
	while (StackWalk(IMAGE_FILE_MACHINE_I386, process,
		GetCurrentThread(),
		&frame,
		ep->ContextRecord,
		NULL,
		SymFunctionTableAccess,
		SymGetModuleBase,
		NULL))
	{
		printf("%d: ", stackcount);
		++stackcount;

		static const int SYMBOL_NAME_LENGTH = 256;
		char sibuf[sizeof(SYMBOL_INFO)+SYMBOL_NAME_LENGTH] = { 0 };
		SYMBOL_INFO * si = (SYMBOL_INFO *)sibuf;
		si->SizeOfStruct = sizeof(SYMBOL_INFO);
		si->MaxNameLen = SYMBOL_NAME_LENGTH;

		if (SymFromAddr(process, frame.AddrPC.Offset, NULL, si))
		{
			printf("%s -> ", si->Name);
			IMAGEHLP_LINE64 line = { sizeof(IMAGEHLP_LINE64) };

			DWORD displacement = 0;
			if (SymGetLineFromAddr64(process, frame.AddrPC.Offset, &displacement, &line))
			{
				printf("%s(%d)\n", line.FileName, line.LineNumber);
			}
			else
			{
				printf("\n");
			}
		}
		else
		{
			printf("Symbol not found.\n");
			continue;
		}
	}
	
	SymCleanup(process);
	printf("End of Stack walk.\n");
	getchar();
	// exit(-1);//直接退出

	return EXCEPTION_EXECUTE_HANDLER;

}

void InstallExceptionHandler()
{
	if (IsDebuggerPresent())
	{
		AddVectoredExceptionHandler(1, TopExceptionHandler);
	}
	else
	{
		SetUnhandledExceptionFilter(TopExceptionHandler);
	}
}

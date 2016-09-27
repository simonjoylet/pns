#define MY_BASE_API __declspec(dllexport)
#include "MyBase/Log.h"
using namespace pns;

int32_t Log::LogPlain(const char * format, ...)
{
	int32_t rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);

	printf("\n");
	return rst;
}

int32_t Log::LogWarning(const char * format, ...)
{
	printf("[WARNING]: ");

	int32_t rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);

	printf("\n");
	return rst;
}

int32_t Log::LogError(const char * format, ...)
{
	printf("[ERROR]: ");

	int32_t rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);

	printf("\n");
	return rst;
}

int32_t Log::LogDebug(const char * format, ...)
{
	printf("[DEBUG]: ");

	int32_t rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);
	
	printf("\n");
	return rst;
}
#define MY_BASE_API __declspec(dllexport)
#include "MyBase/Logger.h"
using namespace pns;

int32_t Logger::LogPlain(const char * format, ...)
{
	int32_t rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);

	printf("\n");
	return rst;
}

int32_t Logger::LogWarning(const char * format, ...)
{
	printf("[WARNING]: ");

	int32_t rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);

	printf("\n");
	return rst;
}

int32_t Logger::LogError(const char * format, ...)
{
	printf("[ERROR]: ");

	int32_t rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);

	printf("\n");
	return rst;
}

int32_t Logger::LogDebug(const char * format, ...)
{
	printf("[DEBUG]: ");

	int32_t rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);
	
	printf("\n");
	return rst;
}
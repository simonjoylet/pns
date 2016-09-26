#define MY_BASE_API __declspec(dllexport)
#include "MyBase/Log.h"
using namespace pns;

pns::Int Log::LogPlain(const pns::Char * format, ...)
{
	Int rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);

	printf("\n");
	return rst;
}

pns::Int Log::LogWarning(const pns::Char * format, ...)
{
	printf("[WARNING]: ");

	Int rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);

	printf("\n");
	return rst;
}

pns::Int Log::LogError(const pns::Char * format, ...)
{
	printf("[ERROR]: ");

	Int rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);

	printf("\n");
	return rst;
}

pns::Int Log::LogDebug(const pns::Char * format, ...)
{
	printf("[DEBUG]: ");

	Int rst = 0;
	va_list arglist;
	va_start(arglist, format);
	rst = vprintf(format, arglist);
	
	printf("\n");
	return rst;
}
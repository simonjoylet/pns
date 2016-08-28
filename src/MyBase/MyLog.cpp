#define MY_BASE_API __declspec(dllexport)
#include "MyBase/MyBase.h"
using namespace pns;

pns::Int MyLog::LogPlain(const pns::Char * format, ...)
{
	Int rst = 0;
	va_list arglist;
	__crt_va_start(arglist, format);
	rst = vprintf(format, arglist);
	__crt_va_end(arglist);

	printf("\n");
	return rst;
}

pns::Int MyLog::LogError(const pns::Char * format, ...)
{
	printf("[ERROR]: ");

	Int rst = 0;
	va_list arglist;
	__crt_va_start(arglist, format);
	rst = vprintf(format, arglist);
	__crt_va_end(arglist);

	printf("\n");
	return rst;
}

pns::Int MyLog::LogDebug(const pns::Char * format, ...)
{
	printf("[DEBUG]: ");

	Int rst = 0;
	va_list arglist;
	__crt_va_start(arglist, format);
	rst = vprintf(format, arglist);
	__crt_va_end(arglist);
	
	printf("\n");
	return rst;
}

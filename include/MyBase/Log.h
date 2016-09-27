#ifndef MY_LOG_H
#define MY_LOG_H

#include "MyBase/Common.h"

namespace pns
{

/**
* 日志类，集中管理日志信息。
*/

class MY_BASE_API Log
{
public:
	static int32_t LogPlain(const char * format, ...);

	static int32_t LogWarning(const char * format, ...);

	static int32_t LogError(const char * format, ...);

	static int32_t LogDebug(const char * format, ...);
};

} // namesapce pns
#endif//MY_LOG_H

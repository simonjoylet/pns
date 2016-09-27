#ifndef MY_LOG_H
#define MY_LOG_H

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "MyBase/MyBaseAPI.h"
#include "MyBase/BasicType.h"

namespace pns
{

/**
* 日志类，集中管理日志信息。
*/

class MY_BASE_API Log
{
public:
	static int32_t LogPlain(const pns::Char * format, ...);

	static int32_t LogWarning(const pns::Char * format, ...);

	static int32_t LogError(const pns::Char * format, ...);

	static int32_t LogDebug(const pns::Char * format, ...);
};

} // namesapce pns
#endif//MY_LOG_H

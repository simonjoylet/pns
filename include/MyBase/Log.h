#ifndef MY_LOG_H
#define MY_LOG_H

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
	static pns::Int LogPlain(const pns::Char * format, ...);

	static pns::Int LogWarning(const pns::Char * format, ...);

	static pns::Int LogError(const pns::Char * format, ...);

	static pns::Int LogDebug(const pns::Char * format, ...);
};

} // namesapce pns
#endif//MY_LOG_H

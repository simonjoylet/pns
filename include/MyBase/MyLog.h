#ifndef MY_LOG_H
#define MY_LOG_H

/**
* 日志类，集中管理日志信息。
*/

class MY_BASE_API MyLog
{
public:
	static pns::Int LogPlain(const pns::Char * format, ...);

	static pns::Int LogError(const pns::Char * format, ...);

	static pns::Int LogDebug(const pns::Char * format, ...);
};

#endif//MY_LOG_H

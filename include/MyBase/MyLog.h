#ifndef MY_LOG_H
#define MY_LOG_H

/**
* ��־�࣬���й�����־��Ϣ��
*/

class MY_BASE_API MyLog
{
public:
	static pns::Int LogPlain(const pns::Char * format, ...);

	static pns::Int LogError(const pns::Char * format, ...);

	static pns::Int LogDebug(const pns::Char * format, ...);
};

#endif//MY_LOG_H

#ifndef MY_LOG_H
#define MY_LOG_H

#include "MyBase/Common.h"

namespace pns
{

/**
* ��־�࣬���й�����־��Ϣ��
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

#ifndef MY_BASE_H
#define MY_BASE_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#ifndef MY_BASE_API
#define MY_BASE_API __declspec(dllimport)
#endif

namespace pns
{
	class MyLog;

#include "MyBase/MyBasicType.h"
#include "MyBase/MyLog.h"

};

#endif//MY_BASE_H

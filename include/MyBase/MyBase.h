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
	class MyThreadBase;
	class MyDynamicArray;

#include "MyBase/MyBasicType.h"
#include "MyBase/MyLog.h"
#include "MyBase/MySynch.h"
#include "MyBase/MyThreadBase.h"
#include "MyBase/MyDynamicArray.h"

};

#endif//MY_BASE_H

#define MY_BASE_API __declspec(dllexport)
#include "MyBase/MyBase.h"
using namespace pns;

// 使用全局变量在CRT的初始化保证单例线程安全。使用匿名命名空间保证符号不重复。
namespace { MySingleton * instance = MySingleton::GetInstance(); }

MySingleton * MySingleton::GetInstance()
{
	static MySingleton instance;
	return &instance;
}

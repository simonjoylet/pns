#define MY_BASE_API __declspec(dllexport)
#include "MyBase/MyBase.h"
using namespace pns;

// ʹ��ȫ�ֱ�����CRT�ĳ�ʼ����֤�����̰߳�ȫ��ʹ�����������ռ䱣֤���Ų��ظ���
namespace { MySingleton * instance = MySingleton::GetInstance(); }

MySingleton * MySingleton::GetInstance()
{
	static MySingleton instance;
	return &instance;
}

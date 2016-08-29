#define MY_BASE_API __declspec(dllexport)
#include "MyBase/MyBase.h"
#include <process.h>
using namespace pns;

pns::Uint __stdcall ThreadStartAddr(pns::Void * param)
{
	MyThreadBase * thread = (MyThreadBase *)param;
	thread->m_isStoped = false;
	pns::Uint exitCode = thread->Run();
	thread->m_isStoped = true;
	return exitCode;
}

MyThreadBase::MyThreadBase()
{
	m_isStoped = true;
	m_isToStop = false;
	m_threadId = 0;
	m_threadHandle = NULL;
}

pns::Bool MyThreadBase::Start()
{
	m_threadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, this, 0, &m_threadId);

}


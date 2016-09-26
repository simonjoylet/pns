#define MY_BASE_API __declspec(dllexport)
#include "MyBase/ThreadBase.h"
#include "MyBase/Log.h"
#include <process.h>
using namespace pns;

pns::Uint __stdcall ThreadStartAddr(pns::Void * param)
{
	ThreadBase * theThread = (ThreadBase *)param;
	pns::Uint exitCode = theThread->Run();
	return exitCode;
}

ThreadBase::ThreadBase()
{
	m_isStoped = true;
	m_isSuspend = false;
	m_toStop = false;

	m_threadId = 0;
	m_threadHandle = NULL;
}

ThreadBase::~ThreadBase()
{
	if (!Join(1000))
	{
		Stop();
	}

	CloseHandle(m_threadHandle);
	m_threadHandle = NULL;
	m_threadId = 0;
}

pns::Bool ThreadBase::Start(pns::Bool isSuspend)
{
	// 如果已经启动过了，就不再启动。
	if (!m_isStoped)
	{
		return true;
	}

	// 创建进程
	m_toStop = false;
	if (isSuspend)
	{
		m_threadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, this, CREATE_SUSPENDED, &m_threadId);
		m_isSuspend = true;
	}
	else
	{
		m_threadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, this, 0, &m_threadId);
	}

	// 判断是否创建成功
	if (m_threadHandle == NULL)
	{
		// 重置线程状态
		m_isStoped = true;
		m_isSuspend = false;
		m_toStop = false;
		m_threadId = 0;

		Log::LogError("线程创建失败");

		return false;
	}
	else
	{
		// 设置线程状态
		m_isStoped = false;
		return true;
	}
}

pns::Bool ThreadBase::Join(pns::Int waitTime /*= -1*/)
{
	// 判断线程当前状态
	if (m_isStoped)
	{
		return true;
	}

	// 通知线程停止
	m_toStop = true;

	// 等待结果
	if (waitTime < 0)
	{
		waitTime = INFINITE;
	}
	if (WaitForSingleObject(m_threadHandle, waitTime) == WAIT_OBJECT_0)
	{
		// 重置线程状态
		CloseHandle(m_threadHandle);
		m_threadHandle = NULL;
		m_isStoped = true;
		m_isSuspend = false;
		m_toStop = false;
		m_threadId = 0;
		return true;
	}
	else
	{
		return false;
	}
}

pns::Bool ThreadBase::Stop()
{
	// 判断线程当前状态
	if (m_isStoped)
	{
		return true;
	}

	// 检查线程句柄
	if (!m_threadHandle)
	{
		Log::LogError("线程句柄为空");
		return false;
	}

	// 强行关闭线程
	m_isStoped = TerminateThread(m_threadHandle, -1) ? true : false;
	if (m_isStoped)
	{
		// 重置
		CloseHandle(m_threadHandle);
		m_threadHandle = NULL;
		m_isSuspend = false;
		m_toStop = false;
		m_threadId = 0;
	}
	return m_isStoped;
}

pns::Bool ThreadBase::Suspend()
{
	// 检查线程当前状态
	if (m_isStoped)
	{
		Log::LogWarning("线程尚未启动");
		return false;
	}
	if (m_isSuspend)
	{
		return true;
	}

	// 检查线程句柄
	if (!m_threadHandle)
	{
		Log::LogError("线程句柄为空");
		return false;
	}

	// 暂停线程
	DWORD rst = SuspendThread(m_threadHandle);
	m_isSuspend = (rst != 0xFFFFFFFF) ? true : false;

	return m_isSuspend;
}

pns::Bool ThreadBase::Resume()
{
	// 检查线程状态
	if (m_isStoped)
	{
		Log::LogWarning("线程尚未启动");
		return false;
	}

	if (!m_isSuspend)
	{
		Log::LogWarning("线程尚未暂停");
		return false;
	}

	// 检查句柄
	if (!m_threadHandle)
	{
		Log::LogError("线程句柄为空");
		return false;
	}

	// 恢复线程
	DWORD rst = ResumeThread(m_threadHandle);

	// 因为只会挂起一次，所以只有挂起计数为1时才是恢复线程成功的返回值
	m_isSuspend = (rst == 1) ? false : true;

	return !m_isSuspend;
}


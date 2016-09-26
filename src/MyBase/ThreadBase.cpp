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
	// ����Ѿ��������ˣ��Ͳ���������
	if (!m_isStoped)
	{
		return true;
	}

	// ��������
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

	// �ж��Ƿ񴴽��ɹ�
	if (m_threadHandle == NULL)
	{
		// �����߳�״̬
		m_isStoped = true;
		m_isSuspend = false;
		m_toStop = false;
		m_threadId = 0;

		Log::LogError("�̴߳���ʧ��");

		return false;
	}
	else
	{
		// �����߳�״̬
		m_isStoped = false;
		return true;
	}
}

pns::Bool ThreadBase::Join(pns::Int waitTime /*= -1*/)
{
	// �ж��̵߳�ǰ״̬
	if (m_isStoped)
	{
		return true;
	}

	// ֪ͨ�߳�ֹͣ
	m_toStop = true;

	// �ȴ����
	if (waitTime < 0)
	{
		waitTime = INFINITE;
	}
	if (WaitForSingleObject(m_threadHandle, waitTime) == WAIT_OBJECT_0)
	{
		// �����߳�״̬
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
	// �ж��̵߳�ǰ״̬
	if (m_isStoped)
	{
		return true;
	}

	// ����߳̾��
	if (!m_threadHandle)
	{
		Log::LogError("�߳̾��Ϊ��");
		return false;
	}

	// ǿ�йر��߳�
	m_isStoped = TerminateThread(m_threadHandle, -1) ? true : false;
	if (m_isStoped)
	{
		// ����
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
	// ����̵߳�ǰ״̬
	if (m_isStoped)
	{
		Log::LogWarning("�߳���δ����");
		return false;
	}
	if (m_isSuspend)
	{
		return true;
	}

	// ����߳̾��
	if (!m_threadHandle)
	{
		Log::LogError("�߳̾��Ϊ��");
		return false;
	}

	// ��ͣ�߳�
	DWORD rst = SuspendThread(m_threadHandle);
	m_isSuspend = (rst != 0xFFFFFFFF) ? true : false;

	return m_isSuspend;
}

pns::Bool ThreadBase::Resume()
{
	// ����߳�״̬
	if (m_isStoped)
	{
		Log::LogWarning("�߳���δ����");
		return false;
	}

	if (!m_isSuspend)
	{
		Log::LogWarning("�߳���δ��ͣ");
		return false;
	}

	// �����
	if (!m_threadHandle)
	{
		Log::LogError("�߳̾��Ϊ��");
		return false;
	}

	// �ָ��߳�
	DWORD rst = ResumeThread(m_threadHandle);

	// ��Ϊֻ�����һ�Σ�����ֻ�й������Ϊ1ʱ���ǻָ��̳߳ɹ��ķ���ֵ
	m_isSuspend = (rst == 1) ? false : true;

	return !m_isSuspend;
}


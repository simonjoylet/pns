#define MY_BASE_API __declspec(dllexport)
#include "MyBase/MyBase.h"
#include <process.h>
using namespace pns;

pns::Uint __stdcall ThreadStartAddr(pns::Void * param)
{
	MyThreadBase * theThread = (MyThreadBase *)param;
	pns::Uint exitCode = theThread->Run();
	return exitCode;
}

MyThreadBase::MyThreadBase()
{
	m_isStoped = true;
	m_isSuspend = false;
	m_toStop = false;

	m_threadId = 0;
	m_threadHandle = NULL;
}

MyThreadBase::~MyThreadBase()
{
	if (!Join(1000))
	{
		Stop();
	}

	CloseHandle(m_threadHandle);
	m_threadHandle = NULL;
	m_threadId = 0;
}

pns::Bool MyThreadBase::Start(pns::Bool isSuspend)
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

		MyLog::LogError("�̴߳���ʧ��");

		return false;
	}
	else
	{
		// �����߳�״̬
		m_isStoped = false;
		return true;
	}
}

pns::Bool MyThreadBase::Join(pns::Int waitTime /*= -1*/)
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

pns::Bool MyThreadBase::Stop()
{
	// �ж��̵߳�ǰ״̬
	if (m_isStoped)
	{
		return true;
	}

	// ����߳̾��
	if (!m_threadHandle)
	{
		MyLog::LogError("�߳̾��Ϊ��");
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

pns::Bool MyThreadBase::Suspend()
{
	// ����̵߳�ǰ״̬
	if (m_isStoped)
	{
		MyLog::LogWarning("�߳���δ����");
		return false;
	}
	if (m_isSuspend)
	{
		return true;
	}

	// ����߳̾��
	if (!m_threadHandle)
	{
		MyLog::LogError("�߳̾��Ϊ��");
		return false;
	}

	// ��ͣ�߳�
	DWORD rst = SuspendThread(m_threadHandle);
	m_isSuspend = (rst != 0xFFFFFFFF) ? true : false;

	return m_isSuspend;
}

pns::Bool MyThreadBase::Resume()
{
	// ����߳�״̬
	if (m_isStoped)
	{
		MyLog::LogWarning("�߳���δ����");
		return false;
	}

	if (!m_isSuspend)
	{
		MyLog::LogWarning("�߳���δ��ͣ");
		return false;
	}

	// �����
	if (!m_threadHandle)
	{
		MyLog::LogError("�߳̾��Ϊ��");
		return false;
	}

	// �ָ��߳�
	DWORD rst = ResumeThread(m_threadHandle);

	// ��Ϊֻ�����һ�Σ�����ֻ�й������Ϊ1ʱ���ǻָ��̳߳ɹ��ķ���ֵ
	m_isSuspend = (rst == 1) ? false : true;

	return !m_isSuspend;
}


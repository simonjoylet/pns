#define MY_BASE_API __declspec(dllexport)
#include "MyBase/MyBase.h"
#include <process.h>
using namespace pns;

pns::Uint __stdcall pns::ThreadStartAddr(pns::Void * param)
{
	MyThreadBase * theThread = (MyThreadBase *)param;
	theThread->m_isStoped = false;
	pns::Uint exitCode = theThread->Run();
	theThread->m_isStoped = true;
	return exitCode;
}

MyThreadBase::MyThreadBase()
{
	m_isStoped = true;
	m_isSuspend = false;
	m_isToStop = false;

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
	if (isSuspend)
	{
		m_threadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, this, CREATE_SUSPENDED, &m_threadId);
		m_isSuspend = true;
	}
	else
	{
		m_threadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, this, 0, &m_threadId);
	}
	return (m_threadHandle != 0); // �̴߳���ʧ��ʱ�᷵��0 
}

pns::Bool MyThreadBase::Join(pns::Int waitTime /*= -1*/)
{
	// �ж��̵߳�ǰ״̬
	if (m_isStoped)
	{
		return true;
	}

	// ֪ͨ�߳�ֹͣ
	SetToStop(true);

	// �ȴ����
	if (waitTime < 0)
	{
		waitTime = INFINITE;
	}
	if (WaitForSingleObject(m_threadHandle, waitTime) == WAIT_OBJECT_0)
	{
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
	//����߳̾��
	if (!m_threadHandle)
	{
		MyLog::LogError("�߳̾��Ϊ��");
		return false;
	}

	m_isStoped = TerminateThread(m_threadHandle, -1) ? true : false;

	return m_isStoped;
}

pns::Bool MyThreadBase::Suspend()
{
	// ����̵߳�ǰ״̬
	if (m_isStoped)
	{
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
	m_isSuspend = SuspendThread(m_threadHandle) ? true : false;
	return m_isSuspend;
}

pns::Bool MyThreadBase::Resume()
{
	// ����߳�״̬
	if (!m_isSuspend)
	{
		return false;
	}

	//�����
	if (!m_threadHandle)
	{
		return false;
	}

	m_isSuspend = !ResumeThread(m_threadHandle) ? true : false;

	return m_isSuspend;
}

pns::Void MyThreadBase::SetToStop(pns::Bool isToStop)
{
	m_isToStop = isToStop;
}

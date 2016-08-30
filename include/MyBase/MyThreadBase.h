#ifndef MY_THREAD_BASE_H
#define MY_THREAD_BASE_H

class MY_BASE_API MyThreadBase
{
	friend pns::Uint __stdcall ThreadStartAddr(pns::Void * param);
public:
	MyThreadBase();
	virtual ~MyThreadBase();

	// �����߳�
	virtual pns::Bool Start(pns::Bool isSuspend = false);

	// ֪ͨ�߳������˳����������޷��ɹ���ֹ�߳�
	virtual pns::Bool Join(pns::Int waitTime = -1);

	// ǿ��ֹͣ�߳�
	virtual pns::Bool Stop();
	
	// ����
	virtual pns::Bool Suspend();

	// �ָ�
	virtual pns::Bool Resume();

	// �߳����е���ڵ�
	virtual pns::Uint Run() = 0;
	
	pns::Bool IsToStop();
	pns::Bool IsStoped();
	pns::Bool IsRunning();

private:
	// ��������
	MyThreadBase(const MyThreadBase &);
	MyThreadBase & operator=(const MyThreadBase &);

protected:
	pns::Bool m_isToStop;
	pns::Bool m_isStoped;
	pns::Bool m_isSuspend;

	pns::Uint m_threadId;
	HANDLE m_threadHandle;
};


#endif//MY_THREAD_BASE_H
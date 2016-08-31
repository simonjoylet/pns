#ifndef MY_THREAD_BASE_H
#define MY_THREAD_BASE_H

class MY_BASE_API MyThreadBase
{
	// �߳�ִ�е���ں�����ע�⣺�ú�������pns�����ռ��������ġ�
	friend pns::Uint __stdcall ThreadStartAddr(pns::Void * param);
public:
	MyThreadBase();
	virtual ~MyThreadBase();

	// �����߳�
	virtual pns::Bool Start(pns::Bool isSuspend = false);

	// ֪ͨ�߳������˳����������޷��ɹ���ֹ�߳�
	// waitTime < 0ʱ��ȴ����޳�
	virtual pns::Bool Join(pns::Int waitTime = -1);

	// ǿ��ֹͣ�߳�
	virtual pns::Bool Stop();
	
	// ����
	virtual pns::Bool Suspend();

	// �ָ�
	virtual pns::Bool Resume();

	// �߳����е���ڵ�
	virtual pns::Uint Run() = 0;
	
	pns::Bool IsToStop() const { return m_isToStop; }
	pns::Bool IsStoped() const { return m_isStoped; }
	pns::Bool IsSuspend() const { return m_isSuspend; }
	pns::Bool IsRunning() const { return (!m_isStoped && !m_isSuspend); }

	pns::Void SetToStop(pns::Bool isToStop);

// 	pns::Void SetStopped(pns::Bool isStopped);
// 	pns::Void SetSuspend(pns::Bool isSuspend);

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
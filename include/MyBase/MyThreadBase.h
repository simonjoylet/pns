#ifndef MY_THREAD_BASE_H
#define MY_THREAD_BASE_H

class MY_BASE_API MyThreadBase
{
public:
	MyThreadBase();
	virtual ~MyThreadBase();

	// �����߳�
	virtual pns::Bool Start(pns::Bool isSuspend = false);

	// ֪ͨ�߳������˳��������޷��ɹ���ֹ�߳�
	// waitTimeΪ�ȴ�ʱ�䣬��λms��������ʾ�ȴ�ʱ�����޳�
	virtual pns::Bool Join(pns::Int waitTime = -1);

	// ǿ��ֹͣ�߳�
	virtual pns::Bool Stop();
	
	// ����
	virtual pns::Bool Suspend();

	// �ָ�
	virtual pns::Bool Resume();

	// �߳����е���ڵ�
	virtual pns::Uint Run() = 0;
	
	// �߳�״̬��ȡ����
	pns::Bool IsToStop() const { return m_toStop; }
	pns::Bool IsStoped() const { return m_isStoped; }
	pns::Bool IsSuspend() const { return m_isSuspend; }
	pns::Bool IsRunning() const { return (!m_isStoped && !m_isSuspend); }
	pns::Uint ThreadId() const { return m_threadId; }

private:
	// ��������
	MyThreadBase(const MyThreadBase &);
	MyThreadBase & operator=(const MyThreadBase &);

protected:
	pns::Bool m_toStop;
	pns::Bool m_isStoped;
	pns::Bool m_isSuspend;

	pns::Uint m_threadId;
	HANDLE m_threadHandle;
};


#endif//MY_THREAD_BASE_H
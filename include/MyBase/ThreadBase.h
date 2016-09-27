#ifndef MY_THREAD_BASE_H
#define MY_THREAD_BASE_H

#include "MyBase/Common.h"

namespace pns
{

class MY_BASE_API ThreadBase
{
public:
	ThreadBase();
	virtual ~ThreadBase();

	// �����߳�
	virtual bool Start(bool isSuspend = false);

	// ֪ͨ�߳������˳��������޷��ɹ���ֹ�߳�
	// waitTimeΪ�ȴ�ʱ�䣬��λms��������ʾ�ȴ�ʱ�����޳�
	virtual bool Join(int32_t waitTime = -1);

	// ǿ��ֹͣ�߳�
	virtual bool Stop();
	
	// ����
	virtual bool Suspend();

	// �ָ�
	virtual bool Resume();

	// �߳����е���ڵ�
	virtual uint32_t Run() = 0;
	
	// �߳�״̬��ȡ����
	bool IsToStop() const { return m_toStop; }
	bool IsStoped() const { return m_isStoped; }
	bool IsSuspend() const { return m_isSuspend; }
	bool IsRunning() const { return (!m_isStoped && !m_isSuspend); }
	uint32_t ThreadId() const { return m_threadId; }

private:
	// ��������
	ThreadBase(const ThreadBase &);
	ThreadBase & operator=(const ThreadBase &);

protected:
	bool m_toStop;
	bool m_isStoped;
	bool m_isSuspend;

	uint32_t m_threadId;
	void * m_threadHandle; // ʹ�ò�͸����void*��������windows.h
};

} // namespace pns

#endif//MY_THREAD_BASE_H
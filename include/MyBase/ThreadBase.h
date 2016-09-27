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

	// 启动线程
	virtual bool Start(bool isSuspend = false);

	// 通知线程自行退出，可能无法成功终止线程
	// waitTime为等待时间，单位ms，负数表示等待时间无限长
	virtual bool Join(int32_t waitTime = -1);

	// 强行停止线程
	virtual bool Stop();
	
	// 挂起
	virtual bool Suspend();

	// 恢复
	virtual bool Resume();

	// 线程运行的入口点
	virtual uint32_t Run() = 0;
	
	// 线程状态获取函数
	bool IsToStop() const { return m_toStop; }
	bool IsStoped() const { return m_isStoped; }
	bool IsSuspend() const { return m_isSuspend; }
	bool IsRunning() const { return (!m_isStoped && !m_isSuspend); }
	uint32_t ThreadId() const { return m_threadId; }

private:
	// 不允许拷贝
	ThreadBase(const ThreadBase &);
	ThreadBase & operator=(const ThreadBase &);

protected:
	bool m_toStop;
	bool m_isStoped;
	bool m_isSuspend;

	uint32_t m_threadId;
	void * m_threadHandle; // 使用不透明的void*避免引用windows.h
};

} // namespace pns

#endif//MY_THREAD_BASE_H
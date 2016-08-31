#ifndef MY_THREAD_BASE_H
#define MY_THREAD_BASE_H

class MY_BASE_API MyThreadBase
{
	// 线程执行的入口函数，注意：该函数是在pns命名空间里声明的。
	friend pns::Uint __stdcall ThreadStartAddr(pns::Void * param);
public:
	MyThreadBase();
	virtual ~MyThreadBase();

	// 启动线程
	virtual pns::Bool Start(pns::Bool isSuspend = false);

	// 通知线程自行退出，但可能无法成功终止线程
	// waitTime < 0时会等待无限长
	virtual pns::Bool Join(pns::Int waitTime = -1);

	// 强行停止线程
	virtual pns::Bool Stop();
	
	// 挂起
	virtual pns::Bool Suspend();

	// 恢复
	virtual pns::Bool Resume();

	// 线程运行的入口点
	virtual pns::Uint Run() = 0;
	
	pns::Bool IsToStop() const { return m_isToStop; }
	pns::Bool IsStoped() const { return m_isStoped; }
	pns::Bool IsSuspend() const { return m_isSuspend; }
	pns::Bool IsRunning() const { return (!m_isStoped && !m_isSuspend); }

	pns::Void SetToStop(pns::Bool isToStop);

// 	pns::Void SetStopped(pns::Bool isStopped);
// 	pns::Void SetSuspend(pns::Bool isSuspend);

private:
	// 不允许拷贝
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
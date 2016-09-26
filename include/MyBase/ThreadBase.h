#ifndef MY_THREAD_BASE_H
#define MY_THREAD_BASE_H

#include <windows.h>
#include "MyBase/MyBaseAPI.h"
#include "MyBase/BasicType.h"

namespace pns
{

class MY_BASE_API ThreadBase
{
public:
	ThreadBase();
	virtual ~ThreadBase();

	// 启动线程
	virtual pns::Bool Start(pns::Bool isSuspend = false);

	// 通知线程自行退出，可能无法成功终止线程
	// waitTime为等待时间，单位ms，负数表示等待时间无限长
	virtual pns::Bool Join(pns::Int waitTime = -1);

	// 强行停止线程
	virtual pns::Bool Stop();
	
	// 挂起
	virtual pns::Bool Suspend();

	// 恢复
	virtual pns::Bool Resume();

	// 线程运行的入口点
	virtual pns::Uint Run() = 0;
	
	// 线程状态获取函数
	pns::Bool IsToStop() const { return m_toStop; }
	pns::Bool IsStoped() const { return m_isStoped; }
	pns::Bool IsSuspend() const { return m_isSuspend; }
	pns::Bool IsRunning() const { return (!m_isStoped && !m_isSuspend); }
	pns::Uint ThreadId() const { return m_threadId; }

private:
	// 不允许拷贝
	ThreadBase(const ThreadBase &);
	ThreadBase & operator=(const ThreadBase &);

protected:
	pns::Bool m_toStop;
	pns::Bool m_isStoped;
	pns::Bool m_isSuspend;

	pns::Uint m_threadId;
	HANDLE m_threadHandle;
};

} // namespace pns

#endif//MY_THREAD_BASE_H
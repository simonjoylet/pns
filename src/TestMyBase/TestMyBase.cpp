#include "MyBase/MyBase.h"
using namespace pns;

void TestMyLog()
{
	// 测试MyLog
	Log::LogDebug("This is a debug info");
	Log::LogError("我去，又错了，咦，我为什么要说又呢");
	Log::LogPlain("人家只是一个普通的日志");
}

void TestMySynch()
{
	// todo, 还没使用多线程进行测试
	MUTEX mutex = NULL;
	MUTEX_INIT(mutex);
	MUTEX_LOCK(mutex);
	MUTEX_UNLOCK(mutex);
	MUTEX_DESTROY(mutex);
}

void TestMyThread()
{
	class TestThread : public ThreadBase
	{
	public:
		virtual pns::Uint Run()
		{
			int printCount = 0;
			while (!IsToStop())
			{
				++printCount;
				printf("Count: %d\n", printCount);
				Sleep(100);
			}
			return printCount;
		}
	};
	Log::LogPlain("开始线程测试");
	TestThread tt;
	if (tt.Start())
	{
		Log::LogPlain("线程ID: %d", tt.ThreadId());
	}

	getchar();
	if (tt.Suspend())
	{
		Log::LogPlain("线程暂停成功");
	}

	getchar();
	if (tt.Resume())
	{
		Log::LogPlain("线程恢复成功");
	}

	getchar();
	if (tt.Join())
	{
		Log::LogPlain("线程停止成功");
	}
	getchar();
	Log::LogPlain("停止线程测试");
}

int main()
{
	// todo, 使用GoogleTest
	TestMyLog();
	TestMySynch();
	TestMyThread();

	getchar();
	return 0;
}
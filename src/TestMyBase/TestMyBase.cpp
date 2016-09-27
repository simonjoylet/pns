#include "MyBase/MyBase.h"
#include "vld.h"
using namespace pns;

void Test_MyLog()
{
	// 测试MyLog
	Log::LogDebug("This is a debug info");
	Log::LogError("我去，又错了，咦，我为什么要说又呢");
	Log::LogPlain("人家只是一个普通的日志");
}

void Test_MySynch()
{
	// todo, 还没使用多线程进行测试
	MUTEX mutex = NULL;
	MUTEX_INIT(mutex);
	MUTEX_LOCK(mutex);
	MUTEX_UNLOCK(mutex);
	MUTEX_DESTROY(mutex);
}

void Test_MyThread()
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

void Test_SkipList()
{
	bool rst = false;
	SkipList<int> sl;
	rst = sl.Insert(1);
	rst = sl.Insert(9);
	rst = sl.Insert(5);
	rst = sl.Contain(5);
	rst = sl.Delete(5);
	rst = sl.Contain(5);
}

int main()
{
	// todo, 使用GoogleTest
// 	Test_MyLog();
// 	Test_MySynch();
// 	Test_MyThread();
	Test_SkipList();

	getchar();
	return 0;
}
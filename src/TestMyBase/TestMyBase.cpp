#include "MyBase/MyBase.h"
using namespace pns;

void TestMyLog()
{
	// 测试MyLog
	MyLog::LogDebug("This is a debug info");
	MyLog::LogError("我去，又错了，咦，我为什么要说又呢");
	MyLog::LogPlain("人家只是一个普通的日志");
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

int main()
{
	// todo, 使用GoogleTest
	TestMyLog();
	TestMySynch();

	getchar();
	return 0;
}
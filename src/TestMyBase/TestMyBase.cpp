#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__) 
#endif

#include "MyBase/MyBase.h"
#include <time.h>
#include <vector>
#include <set>

using namespace pns;

void Test_MyLog()
{
	// 测试MyLog
	Logger::LogDebug("This is a debug info");
	Logger::LogError("我去，又错了，咦，我为什么要说又呢");
	Logger::LogPlain("人家只是一个普通的日志");
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
	Logger::LogPlain("开始线程测试");
	TestThread tt;
	if (tt.Start())
	{
		Logger::LogPlain("线程ID: %d", tt.ThreadId());
	}

	getchar();
	if (tt.Suspend())
	{
		Logger::LogPlain("线程暂停成功");
	}

	getchar();
	if (tt.Resume())
	{
		Logger::LogPlain("线程恢复成功");
	}

	getchar();
	if (tt.Join())
	{
		Logger::LogPlain("线程停止成功");
	}
	getchar();
	Logger::LogPlain("停止线程测试");
}

void Test_SkipList()
{
	// 功能测试
	bool rst = false;
	SkipList<int> sl;
	rst = sl.Insert(1);
	rst = sl.Contain(0);
	rst = sl.Insert(0);
	rst = sl.Contain(0);
	rst = sl.Insert(-1);
	rst = sl.Insert(9);
	rst = sl.Insert(5);
	rst = sl.Contain(5);
	rst = sl.Delete(5);
	rst = sl.Contain(5);
	
	// 性能测试，与std::set和自己实现的List对比
	for (int round = 8; round <= 20; ++round)
	{
		clock_t start = 0;
		std::vector<uint32_t> data_set;

		// 构建数据集
		start = clock();
		Random myrand(start);
		for (int i = 0; i < 1 << round; ++i)
		{
			data_set.push_back(myrand.Next());
		}
		Logger::LogPlain("Round:%d, 构建数据集%dms\n", round, clock() - start);

		/*********** 测试写性能 ***********/
		Logger::LogPlain("测试写性能\n");

		// 使用std::set存储
		start = clock();
		std::set<uint32_t> myset;
		for (size_t i = 0; i < data_set.size(); ++i)
		{
			myset.insert(data_set[i]);
		}
		Logger::LogPlain("\t使用std::set存储：%d个元素，%dms\n", myset.size(), clock() - start);


		// 使用SkipList存储
		start = clock();
		SkipList<uint32_t> mysl;
		for (size_t i = 0; i < data_set.size(); ++i)
		{
			mysl.Insert(data_set[i]);
		}
		Logger::LogPlain("\t使用SkipList存储：%d个元素，%dms\n", mysl.Size(), clock() - start);

		// 使用普通List存储
		start = clock();
		List<uint32_t> mylist;
		if (data_set.size() < 20000) // 太大的数据集就不用测了，否则太慢
		{
			for (size_t i = 0; i < data_set.size(); ++i)
			{
				mylist.Insert(data_set[i]);
			}
			printf("\t使用普通List存储：%d个元素，%dms\n", mylist.Size(), clock() - start);
		}
		printf("\n");

		/*********** 测试读性能 ***********/
		Logger::LogPlain("测试读性能\n");

		// 使用std::set读取
		start = clock();
		for (size_t i = 0; i < data_set.size(); ++i)
		{
			myset.find(data_set[i]);
		}
		Logger::LogPlain("\t使用std::set读取：%d个元素，%dms\n", myset.size(), clock() - start);


		// 使用SkipList读取
		start = clock();
		for (size_t i = 0; i < data_set.size(); ++i)
		{
			mysl.Contain(data_set[i]);
		}
		Logger::LogPlain("\t使用SkipList读取：%d个元素，%dms\n", mysl.Size(), clock() - start);

		// 使用普通List读取
		start = clock();
		if (data_set.size() < 20000) // 太大的数据集就不用测了，否则太慢
		{
			for (size_t i = 0; i < data_set.size(); ++i)
			{
				mylist.Insert(data_set[i]);
			}
			Logger::LogPlain("\t使用普通List读取：%d个元素，%dms\n", mylist.Size(), clock() - start);
		}
		Logger::LogPlain("\n");

	}
	
}

int main()
{
	// todo, 使用GoogleTest
// 	Test_MyLog();
// 	Test_MySynch();
// 	Test_MyThread();
	Test_SkipList();

	getchar();
	_CrtDumpMemoryLeaks();
	return 0;
}
#include "MyBase/MyBase.h"
#include "vld.h"
using namespace pns;

void Test_MyLog()
{
	// ����MyLog
	Log::LogDebug("This is a debug info");
	Log::LogError("��ȥ���ִ��ˣ��ף���ΪʲôҪ˵����");
	Log::LogPlain("�˼�ֻ��һ����ͨ����־");
}

void Test_MySynch()
{
	// todo, ��ûʹ�ö��߳̽��в���
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
	Log::LogPlain("��ʼ�̲߳���");
	TestThread tt;
	if (tt.Start())
	{
		Log::LogPlain("�߳�ID: %d", tt.ThreadId());
	}

	getchar();
	if (tt.Suspend())
	{
		Log::LogPlain("�߳���ͣ�ɹ�");
	}

	getchar();
	if (tt.Resume())
	{
		Log::LogPlain("�ָ̻߳��ɹ�");
	}

	getchar();
	if (tt.Join())
	{
		Log::LogPlain("�߳�ֹͣ�ɹ�");
	}
	getchar();
	Log::LogPlain("ֹͣ�̲߳���");
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
	// todo, ʹ��GoogleTest
// 	Test_MyLog();
// 	Test_MySynch();
// 	Test_MyThread();
	Test_SkipList();

	getchar();
	return 0;
}
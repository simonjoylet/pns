#include "MyBase/MyBase.h"
using namespace pns;

void TestMyLog()
{
	// ����MyLog
	Log::LogDebug("This is a debug info");
	Log::LogError("��ȥ���ִ��ˣ��ף���ΪʲôҪ˵����");
	Log::LogPlain("�˼�ֻ��һ����ͨ����־");
}

void TestMySynch()
{
	// todo, ��ûʹ�ö��߳̽��в���
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

int main()
{
	// todo, ʹ��GoogleTest
	TestMyLog();
	TestMySynch();
	TestMyThread();

	getchar();
	return 0;
}
#include "MyBase/MyBase.h"
using namespace pns;

void TestMyLog()
{
	// ����MyLog
	MyLog::LogDebug("This is a debug info");
	MyLog::LogError("��ȥ���ִ��ˣ��ף���ΪʲôҪ˵����");
	MyLog::LogPlain("�˼�ֻ��һ����ͨ����־");
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
	class TestThread : public MyThreadBase
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
	MyLog::LogPlain("��ʼ�̲߳���");
	TestThread tt;
	if (tt.Start())
	{
		MyLog::LogPlain("�߳�ID: %d", tt.ThreadId());
	}

	getchar();
	if (tt.Suspend())
	{
		MyLog::LogPlain("�߳���ͣ�ɹ�");
	}

	getchar();
	if (tt.Resume())
	{
		MyLog::LogPlain("�ָ̻߳��ɹ�");
	}

	getchar();
	if (tt.Join())
	{
		MyLog::LogPlain("�߳�ֹͣ�ɹ�");
	}
	getchar();
	MyLog::LogPlain("ֹͣ�̲߳���");
}

void TestMySingleton()
{
	MySingleton * singleton = MySingleton::GetInstance();
}

int main()
{
	// todo, ʹ��GoogleTest
	TestMyLog();
	TestMySynch();
	TestMyThread();
	TestMySingleton();

	getchar();
	return 0;
}
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
	// ����MyLog
	Logger::LogDebug("This is a debug info");
	Logger::LogError("��ȥ���ִ��ˣ��ף���ΪʲôҪ˵����");
	Logger::LogPlain("�˼�ֻ��һ����ͨ����־");
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
	Logger::LogPlain("��ʼ�̲߳���");
	TestThread tt;
	if (tt.Start())
	{
		Logger::LogPlain("�߳�ID: %d", tt.ThreadId());
	}

	getchar();
	if (tt.Suspend())
	{
		Logger::LogPlain("�߳���ͣ�ɹ�");
	}

	getchar();
	if (tt.Resume())
	{
		Logger::LogPlain("�ָ̻߳��ɹ�");
	}

	getchar();
	if (tt.Join())
	{
		Logger::LogPlain("�߳�ֹͣ�ɹ�");
	}
	getchar();
	Logger::LogPlain("ֹͣ�̲߳���");
}

void Test_SkipList()
{
	// ���ܲ���
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
	
	// ���ܲ��ԣ���std::set���Լ�ʵ�ֵ�List�Ա�
	for (int round = 8; round <= 20; ++round)
	{
		clock_t start = 0;
		std::vector<uint32_t> data_set;

		// �������ݼ�
		start = clock();
		Random myrand(start);
		for (int i = 0; i < 1 << round; ++i)
		{
			data_set.push_back(myrand.Next());
		}
		Logger::LogPlain("Round:%d, �������ݼ�%dms\n", round, clock() - start);

		/*********** ����д���� ***********/
		Logger::LogPlain("����д����\n");

		// ʹ��std::set�洢
		start = clock();
		std::set<uint32_t> myset;
		for (size_t i = 0; i < data_set.size(); ++i)
		{
			myset.insert(data_set[i]);
		}
		Logger::LogPlain("\tʹ��std::set�洢��%d��Ԫ�أ�%dms\n", myset.size(), clock() - start);


		// ʹ��SkipList�洢
		start = clock();
		SkipList<uint32_t> mysl;
		for (size_t i = 0; i < data_set.size(); ++i)
		{
			mysl.Insert(data_set[i]);
		}
		Logger::LogPlain("\tʹ��SkipList�洢��%d��Ԫ�أ�%dms\n", mysl.Size(), clock() - start);

		// ʹ����ͨList�洢
		start = clock();
		List<uint32_t> mylist;
		if (data_set.size() < 20000) // ̫������ݼ��Ͳ��ò��ˣ�����̫��
		{
			for (size_t i = 0; i < data_set.size(); ++i)
			{
				mylist.Insert(data_set[i]);
			}
			printf("\tʹ����ͨList�洢��%d��Ԫ�أ�%dms\n", mylist.Size(), clock() - start);
		}
		printf("\n");

		/*********** ���Զ����� ***********/
		Logger::LogPlain("���Զ�����\n");

		// ʹ��std::set��ȡ
		start = clock();
		for (size_t i = 0; i < data_set.size(); ++i)
		{
			myset.find(data_set[i]);
		}
		Logger::LogPlain("\tʹ��std::set��ȡ��%d��Ԫ�أ�%dms\n", myset.size(), clock() - start);


		// ʹ��SkipList��ȡ
		start = clock();
		for (size_t i = 0; i < data_set.size(); ++i)
		{
			mysl.Contain(data_set[i]);
		}
		Logger::LogPlain("\tʹ��SkipList��ȡ��%d��Ԫ�أ�%dms\n", mysl.Size(), clock() - start);

		// ʹ����ͨList��ȡ
		start = clock();
		if (data_set.size() < 20000) // ̫������ݼ��Ͳ��ò��ˣ�����̫��
		{
			for (size_t i = 0; i < data_set.size(); ++i)
			{
				mylist.Insert(data_set[i]);
			}
			Logger::LogPlain("\tʹ����ͨList��ȡ��%d��Ԫ�أ�%dms\n", mylist.Size(), clock() - start);
		}
		Logger::LogPlain("\n");

	}
	
}

int main()
{
	// todo, ʹ��GoogleTest
// 	Test_MyLog();
// 	Test_MySynch();
// 	Test_MyThread();
	Test_SkipList();

	getchar();
	_CrtDumpMemoryLeaks();
	return 0;
}
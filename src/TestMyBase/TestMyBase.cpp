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

int main()
{
	// todo, ʹ��GoogleTest
	TestMyLog();
	TestMySynch();

	getchar();
	return 0;
}
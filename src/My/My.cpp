#include "MyBase/MyBase.h"
using namespace pns;

int main(int argc, char ** argv)
{
	// ����MyLog��todo������һ�����Թ���
	MyLog::LogDebug("This is a debug info");
	MyLog::LogError("��ȥ���ִ��ˣ��ף���ΪʲôҪ˵����");
	MyLog::LogPlain("�˼�ֻ��һ����ͨ����־");
	


	getchar();
	return 0;
}
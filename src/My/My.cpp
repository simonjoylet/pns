#include "MyBase/MyBase.h"
using namespace pns;

int main(int argc, char ** argv)
{
	// 测试MyLog，todo：建立一个测试工程
	MyLog::LogDebug("This is a debug info");
	MyLog::LogError("我去，又错了，咦，我为什么要说又呢");
	MyLog::LogPlain("人家只是一个普通的日志");
	


	getchar();
	return 0;
}